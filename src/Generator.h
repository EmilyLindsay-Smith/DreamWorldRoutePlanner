#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> // for pair
#include <algorithm> // for find

#include "Vertex.h"
#include "Graph.h"
#include "Prim.h"
#include "PrefixTree.h"
#include "NameGenerator.h"
#include "Timer.h"

#include "Enums.h"

#include "RoutePlannerUtils.h" // for GetRandomNumber, enum2Str

using namespace std;
using namespace RoutePlannerUtils;

class Generator{
private:
    bool VERBOSE;
    const int MAX_X = 100; // landscape max x value
    const int MAX_Y = 100; // landscape max y value
    
    Graph* graph;
    PrefixTree* searchTree;
    NameGenerator* namer;
    Timer* timer;
    vector<string>* specialAmenities; 
    vector<string>* standardAmenities;
    
    int numSettlements;
    int nextID=0;

    vector<Vertex*>* placeBigs;
    vector<Vertex*>* placeBigsAndPlaceMediums;
    vector<Vertex*>* placeMediums;
    vector<Vertex*>* placeMediumsAndPlaceSmalls;
    vector<Vertex*>* placeSmalls;

    vector<pair<int,int>> ExistingCoords;
    
    pair<int, int> GetCoordinates(){
        //ensures that two settelments aren't in the same location
        int x = GetRandomNumber(MAX_X);
        int y = GetRandomNumber(MAX_Y);
        pair<int, int> coordinates = make_pair(x, y);
        if (find(ExistingCoords.begin(), ExistingCoords.end(),coordinates) != ExistingCoords.end()){
            //If coordinates already in ExistingCoords, try again
            return GetCoordinates();
        }else{
            // Add coordinates to ExistingCoords
            ExistingCoords.push_back(coordinates);
        }
        return coordinates;
    };

    string GetName(NameGenerator* namer, SettlementType settlement, Vertex* ID){
        //cout << "Calling GetName" << endl;
        string sett = enum2Str(settlement);
        string name = namer->GetName(sett);
        //cout << "Found name: " << name << endl;
        bool uniqueName = searchTree->Insert(name, ID);
        //cout << "Unique: " << uniqueName << endl;
        if (!uniqueName){
            return GetName(namer, settlement, ID);
        }
        return name; 
    };

    void CreateSettlement(){
        Vertex* newPlace = new Vertex();
        //cout << "Made vertex pointer" << endl;
        // Get ID
        int ID = nextID;
        nextID++;
        newPlace->SetID(ID);
        //cout << "Set ID:" << ID << endl;
        // Choose Settlement Type
        SettlementType settlement;
        if (ID < numSettlements * .2){ // 20% placeBigs
            settlement = placeBig;
        }else if (ID < numSettlements *.5){ // 30% placeMediums
            settlement = placeMedium;
        }else{ // 50% placeSmalls
            settlement = placeSmall;
        }
        newPlace->SetSettlement(settlement);
        //cout << "Set Settlement: " << settlement << endl;
        // Choose Location Coordinates
        pair<int, int> coordinates = GetCoordinates(); 
        int x = coordinates.first;
        int y = coordinates.second;
        newPlace->SetCoordinates(x,y);
        //cout << "Set Coordinates: " << x << "," << y << endl;
        // Choose Settlement Name
        string name = GetName(namer, settlement, newPlace); // returns unique name and inserts into the searchTree
        newPlace->SetName(name);
        //cout << "Set Name: " << name <<  endl;
        // Choose Friend Name
        string friendName = namer->GetName("firstname");
        string friendSurname = namer->GetName("surname");
        newPlace->SetFriend(friendName);
        newPlace->SetFriendSurname(friendSurname);
        //cout << "Set FriendName: " << friendName <<  endl;
        //Vertex* newPlace = new Vertex(ID, name, friendName, x, y, settlement);

        // Append to location vectors for use in GenerateRoads();
        switch(settlement){
            case placeBig:
          //      cout << "City identified" << endl;
                placeBigs->push_back(newPlace);
            //    cout << "Added to placeBigs" << endl;
                placeBigsAndPlaceMediums->push_back(newPlace);
              //  cout << "Added to c&T" << endl;
                break;
            case placeMedium:
                //cout << "Town identified" << endl;
                placeMediums->push_back(newPlace);
                placeBigsAndPlaceMediums->push_back(newPlace);
                placeMediumsAndPlaceSmalls->push_back(newPlace);
                break;
            case placeSmall:
                //cout << "Village identified" << endl;
                placeSmalls->push_back(newPlace);
                placeMediumsAndPlaceSmalls->push_back(newPlace);
                break;
            default:
                throw runtime_error("Settlement Type not recognised");
        }
        //cout << "Appended to location vector" << endl;
        switch(settlement){
            case placeBig: 
                for (int i=0; i<3; i++){
                    string newAmenity = (*standardAmenities)[GetRandomNumber(static_cast<int>(standardAmenities->size()))];
                    newPlace->AddAmenities(newAmenity);
                };
                break;
            case placeMedium:
                for (int i=0; i<2; i++){
                    newPlace->AddAmenities((*standardAmenities)[GetRandomNumber(static_cast<int>(standardAmenities->size()))]);
                };
                break;
            case placeSmall: 
                for (int i=0; i<1; i++){
                    newPlace->AddAmenities((*standardAmenities)[GetRandomNumber(static_cast<int>(standardAmenities->size()))]);
                };
                break;
            default: throw runtime_error("Settlement Type not recognised");
        }
        newPlace->AddAmenities((*specialAmenities)[GetRandomNumber(static_cast<int>(specialAmenities->size()))]); // add random amenity
  
        if (newPlace->AllSet()){
            graph->AddVertex(newPlace);
        }else{
            CreateSettlement(); // if something has not between set, make a new settlemnt to avoid segmentation faults
        }
    }
    void GenerateSettlements(){
        if (VERBOSE){
            cout << "... creating settlements ..." << endl;
        }
        timer->ReStart();
        for (int i = 0; i<numSettlements; i++){
            //cout << "Settlement " << i << endl;
            CreateSettlement();
        }
        timer->End();
        if (VERBOSE){
            cout << "all settlements generated: " << timer->Duration() << " seconds" << endl;
        }
    };

    void GenerateRoads(){
        //Generates MST 5 times: placeBigs, placeBigsAndPlaceMediums, placeMediums, placeMediumsAndPlaceSmalls, placeSmalls
        if (VERBOSE){
            cout << "... generating road network ..." << endl;
            cout << "... generating fastRoads ... " << endl;
        }
        timer->ReStart();
        Timer* t = new Timer("partial network");
        Prim* pFastRoads = new Prim(placeBigs);
        unordered_map<Vertex*, Vertex*> fastRoads = pFastRoads->RunPrim();
        graph->AddEdges(fastRoads);
        t->End();
        if (VERBOSE){
            cout << "Generated fastRoads in " << t->Duration() << " seconds" << endl;
            cout << "... generating mediumRoads..." << endl;
        }
        t->ReStart();
        Prim* pMediumRoads1 = new Prim(placeMediums);
        unordered_map<Vertex*, Vertex*> mediumRoads1 = pMediumRoads1->RunPrim();      
        Prim* pMediumRoads2 = new Prim(placeBigsAndPlaceMediums);
        unordered_map<Vertex*, Vertex*> mediumRoads2 = pMediumRoads2->RunPrim();
        mediumRoads1.insert(mediumRoads2.begin(), mediumRoads2.end());
        graph->AddEdges(mediumRoads1); // merged both sets incase there are duplicate roads
        t->End();
        if (VERBOSE){
            cout << "Generated mediumRoads in " << t->Duration() << " seconds" << endl;
            cout << "... generating slowRoads ..." << endl;
        }
        t->ReStart();
        Prim* pSlowRoads1 = new Prim(placeSmalls);
        unordered_map<Vertex*, Vertex*> slowRoads1 = pSlowRoads1->RunPrim();
        Prim* pSlowRoads2 = new Prim(placeMediumsAndPlaceSmalls);
        unordered_map<Vertex*, Vertex*> slowRoads2 = pSlowRoads2->RunPrim();
        slowRoads1.insert(slowRoads2.begin(), slowRoads2.end());
        graph->AddEdges(slowRoads1);
        t->End();
        if (VERBOSE){
            cout << "Generated slowRoads in " << t->Duration() << " seconds" << endl;
        //    cout << "... generating extra roads ..." << endl;
        }
        
        /* Extra Roads can be added here if desired
        t->ReStart();

        vector<Vertex*>* allSettlements = placeBigs;
        allSettlements->insert(allSettlements->end(), placeMediumsAndPlaceSmalls->begin(), placeMediumsAndPlaceSmalls->end());
        Prim* extraRoads = new Prim(allSettlements);
        vector<EdgePair> newRoads = extraRoads->GetExtraEdges();
        graph->AddEdges(newRoads);
        t->End();
        if (VERBOSE){
            cout << "Generated Extra Roads in " << t->Duration() << " seconds" << endl;
        }
        */
        timer->End();
        if (VERBOSE){
            cout << "all roads generated: " << timer->Duration() << " seconds" <<endl;
        }
    };



public:
    Generator(int numSettlements, Graph* graph, PrefixTree* searchTree, vector<string>* standardAmenities, vector<string>* specialAmenities, bool verbose){
        this->numSettlements = numSettlements;
        this->graph = graph;
        this->searchTree = searchTree;
        this->standardAmenities = standardAmenities;
        this->specialAmenities = specialAmenities;
        this->VERBOSE = verbose; 
        this->namer = new NameGenerator();
        this->timer = new Timer("Generator");
        this->placeBigs = new vector<Vertex*>;
        this->placeBigsAndPlaceMediums = new vector<Vertex*>;
        this->placeMediums = new vector<Vertex*>;
        this->placeMediumsAndPlaceSmalls = new vector<Vertex*>;
        this->placeSmalls = new vector<Vertex*>;

    }
    ~Generator(){
        delete graph;
        delete searchTree;
        delete namer;
        delete timer;
        specialAmenities->clear();
        delete specialAmenities; 
        standardAmenities->clear();
        delete standardAmenities;
    
        placeBigs->clear();
        delete placeBigs;
        placeBigsAndPlaceMediums->clear();
        delete placeBigsAndPlaceMediums;
        
        placeMediums->clear();
        delete placeMediums;
        placeMediumsAndPlaceSmalls->clear();
        delete placeMediumsAndPlaceSmalls;
        
        placeSmalls->clear();
        delete placeSmalls;
    }

    Graph* Run(){
        GenerateSettlements();
        GenerateRoads();
        return graph;
    }


    int GetNumPlaceBigs(){
        return static_cast<int>(placeBigs->size());
    }
    int GetNumPlaceMediums(){
        return static_cast<int>(placeMediums->size());
    }
    int GetNumPlaceSmalls(){
        return static_cast<int>(placeSmalls->size());
    }
    int GetMaxX(){
        return MAX_X;
    }
    int GetMaxY(){
        return MAX_Y;
    }

    int GetNumAmenities(){
        return static_cast<int>(specialAmenities->size()) + static_cast<int>(standardAmenities->size());
    }
};
#endif