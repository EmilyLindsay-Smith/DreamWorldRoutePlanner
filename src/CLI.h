#include <iostream>
#include <optional>
using namespace std;

#include "Engine.h"
#include "RoutePlannerUtils.h" // for enum2str

using namespace RoutePlannerUtils;

class CLI{
private:
    Engine* engine;
    int size;
    vector<std::string>* standardAmenities; 
    vector<std::string>* specialAmenities; 
    vector<std::string>* amenities;
;
// Set UP function to generate amenities vectors for use in generator and in finding amenity
    void GenerateAmenities(){
        vector<std::string> stA = {"apothecary", "blacksmith", "glassworks", "tanner", "weaver", "carpenter", "tavern", "cobbler", "fishmonger"};
        vector<std::string> spA = {"market", "university", "barracks", "healer", "bookshop", "oracle"};
        amenities = new vector<string>;
        standardAmenities = new vector<string>;
        for (auto elem: stA){
            standardAmenities->push_back(elem);
            amenities->push_back(elem);
        }
        specialAmenities = new vector<string>;
        for (auto elem: spA){
            specialAmenities->push_back(elem);
            amenities->push_back(elem);
        }
        return;
    }

// User Help Functions
    void DisplayAllStarts(){
        vector<char> allStarts = engine->GetAllStarts();
        cout << "\tSettlements start with the following " <<allStarts.size() << " letters in this iteration of DreamWorld: \n"<< endl;
  
        for(int i = 1; i <= allStarts.size(); i++){
            cout << "\t";
            char c = allStarts[i-1] - 32;
            string s{c};
            cout << s;
            if (i % 7 == 0){
                cout << "\n";;
            }
        }
        cout << endl;
    }
    enum HelpType {binaryChoice, selectSettlement, chooseNumber};
    void Help(HelpType helper){
        if (helper == binaryChoice){
            cout << "\tI think you want help making a (y/n) decision" << endl;
            cout << "\tIf you want to say 'yes' to the question above, please type 'y' then press enter" << endl;
            cout << "\tIf you want to say 'no' to the question above, please type any other letter or number then press enter" << endl;
            cout << "\tLet's give it a go\n" <<endl;;
            return;
        }else if (helper == selectSettlement){
            cout << "\tI think you want help choosing a settlement" << endl;
            cout << "\tIn the DreamWorld Route Planner, you can search for settlements in two ways: " << endl;
            cout << "\t\tA:  typing the full settlement name then pressing enter" << endl;
            cout << "\t\tB:  typing the start of a settlement name then pressing enter" << endl;
            cout << "\n\tThis means if you don't know the name of a settlement, it will search for all the settlement names that start with what you've searched for"<<endl;
            cout << "\tIf only one settlement is available, it will choose that one; if multiple are available, it will ask you to choose between them" << endl;
            cout << "\tIf you type something that isn't available, it'll let you know and ask you to try again\n" << endl;
            DisplayAllStarts();
            cout << "\tLet's give it a go\n" <<endl ;
            return;
        }else if (helper == chooseNumber){
            cout << "\tI think you want help choosing from a list of options" << endl;
            cout << "\tIn front of each option listed above there is a number" << endl;
            cout << "\tTo choose that option, please type that number then press enter" << endl;
            cout << "\tLet's give it a go\n" <<endl ;
            return;
        }else{
            cout << "\tSorry, there are no help functions available :)" << endl;
            return;
        }
    }
// Input Sanitisation Functions
    int GetInt(int lowerBound, int upperBound){
        cout << "please type a whole number between " << lowerBound << " and " << upperBound << endl;
        cout << "\t(For help, please type ?)" << endl;
        string input;
        while (! (cin >> input)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Sorry, I didn't catch that. Please input a whole number between " << lowerBound << " and " << upperBound << endl;
        }
        if (input == "?"){
            Help(chooseNumber);
            return GetInt(lowerBound, upperBound); 
        }
        int output = stoi(input);
        if (!output){
            cout << "Sorry I couldn't understand that. Please try again" << endl;
            return GetInt(lowerBound, upperBound); 
        }
        if (output >= lowerBound && output <= upperBound){
            return output;    
        }else{
            cout << "Input needs to be between " << lowerBound << " and " << upperBound << ". Please try again" << endl;
            return GetInt(lowerBound, upperBound);
        }
        return output;
    }

    string GetString(){
        cout << "\t(For help, please type ?)" << endl;
        string input;
        while (!(cin >> input)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input not accepted. Please try again: " << endl;
        }     
        if (input == "?"){
            Help(selectSettlement);
            return GetString();
        }
        
        string output;
        for (auto chr : input){
            string s{chr};
            if (s == "?"){
                Help(selectSettlement);
                return GetString();
            }
            if (!ContainsNonAlpha(s)){
                output += chr;
            }
        }
        return output;
    };

    char GetDecision(){
        cout << "\t(For help, please type ?)" << endl;
        string input;
        while (!(cin >> input)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input not accepted. Please try again: " << endl;
        }     
        if (input == "?"){
            Help(binaryChoice);
            return GetDecision();
            }
        
        string output;
        for (auto chr : input){
            string s{chr};
            if (!ContainsNonAlpha(s)){
                output += chr;
            }
        }
        return tolower(output[0]);
    };

// Choose Settlement based on full string or partial match
    int ChoosePartialMatch(vector<RefPair>* searchOutput, std::string query){
        cout << "Settlement " << query << " could not be found. However, " << static_cast<int>(searchOutput->size()) << " partial matches have been identified." << endl;
            
        for (int i = 1; i <= static_cast<int>(searchOutput->size()); i++){
            std::string place = (*searchOutput)[i-1].queryString;
            place[0] = toupper(place[0]); // sentence case
            Vertex* location = (*searchOutput)[i-1].stringRef;
            cout << "\t" <<  i << "\t" << place << endl;
        }
        
        cout << "To choose a partial match settlement, "; 
        int choice = GetInt(1, static_cast<int>(searchOutput->size()));
        choice = choice -1;
        return choice; // as vector is 0 indexed
    }

    Vertex* FindSettlement(){
        std::string query = GetString();
        query[0] = toupper(query[0]); // sentence case
        vector<RefPair>* searchOutput = engine->RetrieveSettlement(query);
        if (searchOutput->empty()){
            cout << "Settlement " << query << " could not be found" << endl;
            delete searchOutput;
            return nullptr;
        }else if (static_cast<int>(searchOutput->size()) > 1){
            // If multiple partial matches found, user chooses one:
            int choice = ChoosePartialMatch(searchOutput, query);
            searchOutput = engine->ChooseBetweenSettlements(searchOutput, choice);
        }
        // Retrieve pointer to settlement and display info
        Vertex* place = engine->RetrieveSettlementPointer(searchOutput);
        cout << "Selected Location: " << place->GetName() << "\t" << enum2Str(place->GetSettlement()) << " at (" << place->GetCoordinates()->x << "," << place->GetCoordinates()->y << ")" <<endl;
        delete searchOutput;
        return place;
    }

// List information about all the settlements
    void ListAllSettlements(){
        // Get List of all Settlements
        set<std::string>* results = engine->ListAllSettlements();
        if (results->empty()){
            cout << "No results found" << endl;
        }else{
            if(static_cast<int>(results->size()) != this->size){
                throw runtime_error("Problem finding all strings in tree - incorrect number of strings returned");
            }
            cout << static_cast<int>(results->size()) << " settlements found: " << endl;
            for (auto it = results->begin(); it != results->end(); it++){
                std::string place = (*it);
                place[0] = toupper(place[0]); // sentence case
                cout << "\t" << place << endl;
            }
        }
        Continue();
        return;
    };
    
    void ListAllSettlementsVerbose(){
        // Get List of all Settlements
        vector<RefPair>* results = engine->ListAllSettlementsVerbose();
        if (results->empty()){
            cout << "No results found" << endl;
        }else{
            if(static_cast<int>(results->size()) != this->size){
                throw runtime_error("Problem finding all strings in tree - incorrect number of strings returned");
            }
            cout << static_cast<int>(results->size()) << " settlements found: " << endl;
            cout << "\t Settlement \t Type \t Coordinates "<< endl;
            for (auto it = results->begin(); it != results->end(); it++){
                std::string place = (*it).queryString ;
                place[0] = toupper(place[0]);
                cout << "\t" << place
                    << "\t" << enum2Str((*it).stringRef->GetSettlement())
                    << "\t(" << (*it).stringRef->GetCoordinates()->x << "," << (*it).stringRef->GetCoordinates()->y << ")"
                    << endl;
            }
        }
        Continue();
        return;
    };
// Display information about a specific settlement
    void DisplaySettlement(){
        // Search for query in prefix tree
        cout << "\nWhich settlement would you like to display information for?" << endl;
        Vertex* place = FindSettlement();
        if (place == nullptr){
            DisplaySettlement();
        }
        engine->DisplaySettlementInfo(place);
        Continue();
        return;
    }
// Display a route based on the parent stack

    void DisplayRoute(stack<Vertex*> route){
        if (route.empty()){
            cout << "There is no route available" << endl;
        }else if (static_cast<int>(route.size()) == 1){
            cout << "There is no route available" << endl;
        }

        Vertex* place1 = route.top();
        route.pop();
        cout << "Start at " << place1->GetName() << " (" << enum2Str(place1->GetSettlement()) << " at " << "(" + to_string(place1->GetCoordinates()->x) + ","+ to_string(place1->GetCoordinates()->y) + ")" << ")" << endl;
        int count = 1;
        while(!route.empty()){
            Vertex* place2 = route.top();
            route.pop();
            std::string roadType = engine->IdentifyRoadType(place1, place2);
            std::string compassDirection = engine->IdentifyRoadDirection(place1, place2);
            std::string settlement = enum2Str(place2->GetSettlement());
            std::string coordinates = "(" + to_string(place2->GetCoordinates()->x) + ","+ to_string(place2->GetCoordinates()->y) + ")";
            cout << count << ") Take the " << roadType << " going "<< compassDirection << ((compassDirection.length() > 0) ? " " : "")<< "to " << place2->GetName() << " (" << settlement << " at " << coordinates << ")" << endl;
            place1 = place2; 
            count++;
        }
        cout << "You have arrived at your destination" << endl;
        return;
    }

// Plan Journey Route Functions
    Vertex* GetOrigin(){
        cout << "Which settlement would you like to start from?" << endl;
        Vertex* origin = FindSettlement();
        if (origin == nullptr){
            return GetOrigin();
        }
        return origin;
    }
    
    Vertex* GetDest(){
        cout << "Which settlement would you like to go to?" << endl;
        Vertex* dest = FindSettlement();
        if (dest == nullptr){
            return GetDest();
        }
        return dest;
    }

    void PlanRoute(){
        cout << "Welcome to the Journey Planner!" << endl;
        Vertex* origin = GetOrigin();
        Vertex* destination = GetDest();

        if (origin == destination){
            cout << "Origin: " << origin->GetName();
            cout << "Destination: " << destination->GetName();
            cout << "Whoops - you have chosen the same origin and destination! Please try again: " << endl;
            PlanRoute();
        }

        cout << "Calculating routes between " << origin->GetName() << " and " << destination->GetName() << "...." << endl;
        float pathCostByTime = engine->FindPathCost(origin, destination, "Time");
        stack<Vertex*> pathByTime = engine->FindPath(origin, destination, "Time", pathCostByTime);
        
        float pathCostByDist = engine->FindPathCost(origin, destination, "Dist");
        stack<Vertex*> pathByDist = engine->FindPath(origin, destination, "Dist", pathCostByDist);
        if (pathByTime.top() == nullptr){
            cout << "\nUnfortunately there is no shortest distance route available between "<< origin->GetName() << " and " << destination->GetName() << endl;
        }else{
            cout <<"\nIf you want to travel the shortest distance between " << origin->GetName() << " and " << destination->GetName()
                << " your journey will be " << pathCostByDist<< " kilometers" << endl;
            cout << "\nPlease follow this route: " << endl;
            DisplayRoute(pathByDist);
        }
        if (pathByTime.top() == nullptr){
            cout << "\nUnfortunately there is no shortest time route available between "<< origin->GetName() << " and " << destination->GetName() << endl;
        }else{
            cout <<"\nIf you want to travel the fastest route between " << origin->GetName() << " and " << destination->GetName()
                << " your journey will take " << MinToHour(pathCostByTime) << endl;
            cout << "\nPlease follow this route: " << endl;
            DisplayRoute(pathByTime);
        }
        Continue();
        return;
    }

// Find nearest amenity functions
    std::string GetAmenity(){
        cout << "The available amenities are: " << endl;
        for (int i = 0; i < static_cast<int>(amenities->size()); i++){
            cout << "\t" << i+1 << ":\t" << (*amenities)[i] << endl;
        }

        cout << "To select an amenity, ";
        int choice = GetInt(1, static_cast<int>(amenities->size()));
        string amenity = (*amenities)[choice -1];
        
        return amenity;
    }

    void FindAmenity(){
        Vertex* origin = GetOrigin();
        std::string amenity = GetAmenity();
        cout << "Chosen amenity: " << amenity << endl;
        Vertex* destByTime = engine->FindNearestAmenity(origin, amenity, "Time");
        float pathCostByTime = engine->FindPathCost(origin, destByTime, "Time");
        stack<Vertex*> pathByTime = engine->FindPath(origin, destByTime, "Time", pathCostByTime);

        Vertex* destByDist = engine->FindNearestAmenity(origin, amenity, "Dist");
        float pathCostByDist = engine->FindPathCost(origin, destByDist, "Dist");
        stack<Vertex*> pathByDist = engine->FindPath(origin, destByDist, "Dist", pathCostByDist);

        cout << "The nearest " << amenity << "  with the shortest distance route is in " << destByDist->GetName() << " (" << pathCostByDist << "km)" << endl;
        cout << "The nearest " << amenity << " with the shortest time route is in " << destByTime->GetName() << " (" << MinToHour(pathCostByTime) << ")" << endl;

        cout << "\nDo you want to see the routes? y/n" << endl;
        char decision = GetDecision();

        if (decision == 'y'){
            if (pathByTime.top() == nullptr){
                cout << "Unfortunately there is no shortest distance route available between "<< origin->GetName() << " and " << destByDist->GetName() << endl;
            }else{
                cout <<"\nIf you want to travel the shortest distance between " << origin->GetName() << " and " << destByDist->GetName()
                    << "your journey will be " << pathCostByDist<< " kilometers" << endl;
                cout << "\nPlease follow this route: " << endl;
                DisplayRoute(pathByDist);
            }
            if (pathByTime.top() == nullptr){
                cout << "Unfortunately there is no shortest time route available between "<< origin->GetName() << " and " << destByTime->GetName() << endl;
            }else{
                cout <<"\nIf you want to travel the fastest route between " << origin->GetName() << " and " << destByTime->GetName()
                    << "your journey will take " << MinToHour(pathCostByTime) << endl;
                cout << "\nPlease follow this route: " << endl;
                DisplayRoute(pathByTime);
            }
        }
        Continue();
        return;
    }

// Regenerate DreamWorld   
    void Regenerate(){
        cout << "This will destroy the current DreamWorld and create a new one. Are you sure(y/n)?" << endl;
        char decision = GetDecision();
        if (decision == 'y'){
            SetUpLandscape(); 
        }
        SelectActivity();
    }

public:
    CLI(int size){
        this->size = size;        
    }

    void Introduce(){
        cout << "\nWelcome to the Official Route Planner of DreamWorld\n" << "\n-----------------------------------\n" << endl;
        cout << "DreamWorld is a bit like the world you already live in, but with quirky amenities, weirder place names and an meanderingly inefficient road network" << endl;
        cout << "DreamWorld has citadels, towns and hamlets, joined together by expressways (fastest), highways and lanes (slowest) " << endl;
        cout << "\nUsing this Route Planner, you can get information about the settlements in DreamWorld, plan routes between them and find the nearest amenities" << endl;
        cout << "Every time you use the Official Route Planner of DreamWorld, the landscape resets, with new settlements and new roads" << endl;
        cout << "\nLet's begin!" << endl;
    }
    void SetUpLandscape(){
        cout << "\n\n... Creating DreamWorld ..." << endl;
        GenerateAmenities();
        engine = new Engine(size, standardAmenities, specialAmenities);
        engine->GenerateLandscape();

        cout << "\n\nDreamWorld created with " << this->size << " settlements and " << engine->GetNumRoads() << " roads" << endl;   
        cout << engine->CheckPrefixTree() << " settlements included in searchTree" << endl;
        return;
    }

    void SelectActivity(){
        cout << "\n\nWith the DreamWorld Route Planner, you can do the following activities: \n" << endl;
        cout << "1: \t List all the settlements in DreamWorld" << endl;
        cout << "2: \t List all the settlements in DreamWorld with their settlement type and coordinates" << endl;
        cout << "3: \t Display more information about a particular settlement in DreamWorld" << endl;
        cout << "4: \t Search for routes between settlements in DreamWorld" << endl;
        cout << "5: \t Search for the nearest amenity to a settlement in DreamWorld" << endl;
        cout << "6: \t Regenerate DreamWorld to create new settlements and roads" << endl;
        cout << "\nTo select an activity, ";
        int choice = GetInt(1, 7);

        switch(choice){
            case 1 : ListAllSettlements(); break;
            case 2: ListAllSettlementsVerbose(); break;
            case 3: DisplaySettlement(); break;
            case 4: PlanRoute(); break;
            case 5: FindAmenity(); break;
            case 6: Regenerate(); break;
            default: cout << "Sorry, I didn't catch that. Let's try again" << endl; SelectActivity(); break;
        }
    }

    void Continue(){
        cout << "\nWould you like to select another activity (y/n)?" <<endl;
        char decision = GetDecision();
        if (decision == 'y'){
            return SelectActivity();
        }else{
            cout << "\nSorry to see you go! Visit DreamWorld again any time" << endl;
        }
        return;
    }
};
