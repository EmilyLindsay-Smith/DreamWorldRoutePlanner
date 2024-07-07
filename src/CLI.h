#include <iostream>
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

    int ChoosePartialMatch(vector<RefPair>* searchOutput, std::string query){
        cout << "Settlement " << query << " could not be found. However, " << static_cast<int>(searchOutput->size()) << " partial matches have been identified." << endl;
            
            for (int i = 1; i <= static_cast<int>(searchOutput->size()); i++){
                std::string place = (*searchOutput)[i-1].queryString;
                place[0] = toupper(place[0]); // sentence case
                Vertex* location = (*searchOutput)[i-1].stringRef;
                cout << "\t" <<  i << "\t" << place << endl;
            }
            
            cout << "Please type an integer between 1 and " <<static_cast<int>(searchOutput->size()) << " to choose a partial match settlement" << endl;
            int choice;
            cin >> choice;
            if (choice < 1 && choice > searchOutput->size()){  // CHECK CHOICE IS INT??
                cout << "Sorry, I couldn't recognise that choice" << endl;
                choice = ChoosePartialMatch(searchOutput, query);
            }
            choice = choice -1;
            return choice; // as vector is 0 indexed
    }

    Vertex* FindSettlement(){
        std::string query;
        cin >> query; // VALIDATE/SANITISE ME!!!!
        query[0] = toupper(query[0]); // sentence case
        vector<RefPair>* searchOutput = engine->RetrieveSettlement(query);
        if (searchOutput->empty()){
            cout << "Settlement " << query << " could not be found" << endl;
            return nullptr;
        }else if (static_cast<int>(searchOutput->size()) > 1){
            // If multiple partial matches found, user chooses one:
            int choice = ChoosePartialMatch(searchOutput, query);
            searchOutput = engine->ChooseBetweenSettlements(searchOutput, choice);
        }
        // Retrieve pointer to settlement and display info
        Vertex* place = engine->RetrieveSettlementPointer(searchOutput);
        cout << "Selected Location: " << place->GetName() << "\t" << enum2Str(place->GetSettlement()) << " at (" << place->GetCoordinates()->x << "," << place->GetCoordinates()->y << ")" <<endl;
        return place;
    }

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

    void DisplaySettlement(){
        // Search for query in prefix tree
        cout << "Which settlement would you like to display information for?" << endl;
        Vertex* place = FindSettlement();
        if (place == nullptr){
            DisplaySettlement();
        }
        engine->DisplaySettlementInfo(place);
        Continue();
        return;
    }

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
    }

    Vertex* GetOrigin(){
        cout << "Which settlement would you like to start from?" << endl;
        Vertex* origin = FindSettlement();
        if (origin == nullptr){
            GetOrigin();
        }
        return origin;
    }
    
    Vertex* GetDest(){
        cout << "Which settlement would you like to go to?" << endl;
        Vertex* dest = FindSettlement();
        if (dest == nullptr){
            GetDest();
        }
        return dest;
    }

    void PlanRoute(){
        cout << "Welcome to the Journey Planner!" << endl;
        Vertex* origin = GetOrigin();
        Vertex* destination = GetDest();

        if (origin == destination){
            cout << "Whoops - you have chosen the same origin and destination! Please try again: " << endl;
            PlanRoute();
        }

        cout << "Calculating routes between " << origin->GetName() << " and " << destination->GetName() << "...." << endl;
        float pathCostByTime = engine->FindPathCost(origin, destination, "Time");
        stack<Vertex*> pathByTime = engine->FindPath(origin, destination, "Time", pathCostByTime);
        
        float pathCostByDist = engine->FindPathCost(origin, destination, "Dist");
        stack<Vertex*> pathByDist = engine->FindPath(origin, destination, "Dist", pathCostByDist);
        if (pathByTime.top() == nullptr){
            cout << "Unfortunately there is no shortest distance route available between "<< origin->GetName() << " and " << destination->GetName() << endl;
        }else{
            cout <<"\nIf you want to travel the shortest distance between " << origin->GetName() << " and " << destination->GetName()
                << " your journey will be " << pathCostByDist<< " kilometers" << endl;
            cout << "Please follow this route: " << endl;
            DisplayRoute(pathByDist);
        }
        if (pathByTime.top() == nullptr){
            cout << "Unfortunately there is no shortest time route available between "<< origin->GetName() << " and " << destination->GetName() << endl;
        }else{
            cout <<"\nIf you want to travel the fastest route between " << origin->GetName() << " and " << destination->GetName()
                << " your journey will take " << MinToHour(pathCostByTime) << endl;
            cout << "Please follow this route: " << endl;
            DisplayRoute(pathByTime);
        }
        Continue();
        return;
    }

    std::string GetAmenity(){
        cout << "The available amenities are: " << endl;
        for (int i = 0; i < static_cast<int>(amenities->size()); i++){
            cout << "\t" << i+1 << ":\t" << (*amenities)[i] << endl;
        }
        cout << "Please select an amenity by typing a number between 1 and " << static_cast<int>(amenities->size()) << endl;
        int choice;
        cin >> choice;
        std::string amenity;
        if (choice >= 1 && choice <= static_cast<int>(amenities->size())){
            amenity = (*amenities)[choice -1];
        }else{
            cout << "Sorry I didn't understand that. Please try again." << endl;
            amenity = GetAmenity();
        }
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

        cout << "Do you want to see the routes? y/n" << endl;
        char choice;
        cin >> choice;

        if (choice == 'y'){
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

    int GetCount(){
        cout << "How many results for this amenity do you want? Please type a whole number: " << endl;
        int count;
        cin >> count;
        if (count > 0){
            return count;
        }else{
            return GetCount();
        }
    }
   
    void Regenerate(){
        cout << "This will destroy the current DreamWorld and create a new one. Are you sure(y/n)?" << endl;
        char decision;
        cin >> decision;
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
        cout << "Welcome to the Official Route Planner of DreamWorld" << "\n-----------------------------------" << endl;
        cout << "DreamWorld is a bit like the world you already live in, but with quirky amenities, weirder place names and an meanderingly inefficient road network" << endl;
        cout << "DreamWorld has citadels, towns and hamlets, joined together by expressways (fastest), highways and lanes (slowest) " << endl;
        cout << "Using this Route Planner, you can get information about the settlements in DreamWorld, plan routes between them and find the nearest amenities" << endl;
        cout << "Every time you use the Official Route Planner of DreamWorld, the landscape resets, with new settlements and new roads" << endl;
        cout << "Let's begin!" << endl;
    }
    void SetUpLandscape(){
        cout << "... Creating DreamWorld ..." << endl;
        GenerateAmenities();
        engine = new Engine(size, standardAmenities, specialAmenities);
        engine->GenerateLandscape();

        cout << "DreamWorld created with " << this->size << " settlements and " << engine->GetNumRoads() << " roads" << endl;   
        cout << engine->CheckPrefixTree() << " settlements included in searchTree" << endl;
        return;
    }

    void SelectActivity(){
        cout << "With the DreamWorld Route Planner, you can do the following activities: \n" << endl;
        cout << "1: \t List all the settlements in DreamWorld" << endl;
        cout << "2: \t List all the settlements in DreamWorld with their settlement type and coordinates" << endl;
        cout << "3: \t Display more information about a particular settlement in DreamWorld" << endl;
        cout << "4: \t Search for routes between settlements in DreamWorld" << endl;
        cout << "5: \t Search for the nearest amenity to a settlement in DreamWorld" << endl;
        cout << "6: \t Regenerate DreamWorld to create new settlements and roads" << endl;
        cout << "Please type a number between 1 and 7 to select an activity or 'Ctrl-C' to exit the program" << endl;
        int choice;
        cin >> choice;

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
        cout << "Would you like to select another activity (y/n)?" <<endl;
        char decision;
        cin >> decision;
        if (decision == 'y'){
            SelectActivity();
        }else{
            cout << "Sorry to see you go! Visit DreamWorld again any time" << endl;
        }
        return;
    }
};
