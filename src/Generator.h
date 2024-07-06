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
    const int MAX_Y = 101; // landscape max y value
    int numSettlements;
    int nextID=0;
    Graph* graph;
    PrefixTree* searchTree;
    NameGenerator* namer;
    Timer* timer;

    vector<Vertex*>* cities;
    vector<Vertex*>* citiesAndTowns;
    vector<Vertex*>* towns;
    vector<Vertex*>* townsAndVillages;
    vector<Vertex*>* villages;

    vector<pair<int,int>> ExistingCoords;
    
    pair<int, int> GetCoordinates(){
        //ensures that two settelments aren't in the same location
        int x = GetRandomNumber(MAX_X);
        int y = GetRandomNumber(MAX_Y);
        pair<int, int> coordinates = make_pair(x, y);
        if (find(ExistingCoords.begin(), ExistingCoords.end(),coordinates) != ExistingCoords.end()){
            //If coordinates already in ExistingCoords, try again
            GetCoordinates();
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
        if (ID->GetID() == 1) cout << name << endl;
        //cout << "Found name: " << name << endl;
        bool uniqueName = searchTree->Insert(name, ID);
        //cout << "Unique: " << uniqueName << endl;
        if (!uniqueName){
            name = GetName(namer, settlement, ID);
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
        if (ID < numSettlements * .2){ // 20% cities
            settlement = city;
        }else if (ID < numSettlements *.5){ // 30% towns
            settlement = town;
        }else{ // 50% villages
            settlement = village;
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
        friendName += " " + namer->GetName("surname");
        newPlace->SetFriend(friendName);
        //cout << "Set FriendName: " << friendName <<  endl;
        //Vertex* newPlace = new Vertex(ID, name, friendName, x, y, settlement);
         //Add Settlement to graph
        graph->AddVertex(newPlace);
        //cout << "Added to graph" << endl;
        // Append to location vectors for use in GenerateRoads();
        switch(settlement){
            case city:
          //      cout << "City identified" << endl;
                cities->push_back(newPlace);
            //    cout << "Added to cities" << endl;
                citiesAndTowns->push_back(newPlace);
              //  cout << "Added to c&T" << endl;
                break;
            case town:
                //cout << "Town identified" << endl;
                towns->push_back(newPlace);
                citiesAndTowns->push_back(newPlace);
                townsAndVillages->push_back(newPlace);
                break;
            case village:
                //cout << "Village identified" << endl;
                villages->push_back(newPlace);
                townsAndVillages->push_back(newPlace);
                break;
            default:
                throw runtime_error("Settlement Type not recognised");
        }
        //cout << "Appended to location vector" << endl;
        // ADD UTILITIES TOO
  //      cout << "UTILITIES NEED ADDING HERE" << endl;
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
        //Generates MST 5 times: cities, citiesAndTowns, towns, townsAndVillages, villages
        if (VERBOSE){
            cout << "... generating road network ..." << endl;
            cout << "... generating motorways ... " << endl;
        }
        timer->ReStart();
        Timer* t = new Timer("partial network");
        Prim* pMotorways = new Prim(cities);
        unordered_map<Vertex*, Vertex*> motorways = pMotorways->RunPrim();
        graph->AddEdges(motorways);
        t->End();
        if (VERBOSE){
            cout << "Generated motorways in " << t->Duration() << " seconds" << endl;
            cout << "... generating A Roads..." << endl;
        }
        t->ReStart();
        Prim* pARoads1 = new Prim(towns);
        unordered_map<Vertex*, Vertex*> aRoads1 = pARoads1->RunPrim();      
        Prim* pARoads2 = new Prim(citiesAndTowns);
        unordered_map<Vertex*, Vertex*> aRoads2 = pARoads2->RunPrim();
        aRoads1.insert(aRoads2.begin(), aRoads2.end());
        graph->AddEdges(aRoads1); // merged both sets incase there are duplicate roads
        t->End();
        if (VERBOSE){
            cout << "Generated A Roads in " << t->Duration() << " seconds" << endl;
            cout << "... generating B Roads ..." << endl;
        }
        t->ReStart();
        Prim* pBRoads1 = new Prim(villages);
        unordered_map<Vertex*, Vertex*> bRoads1 = pBRoads1->RunPrim();
        Prim* pBRoads2 = new Prim(townsAndVillages);
        unordered_map<Vertex*, Vertex*> bRoads2 = pBRoads2->RunPrim();
        bRoads1.insert(bRoads2.begin(), bRoads2.end());
        graph->AddEdges(bRoads1);
        t->End();
        if (VERBOSE){
            cout << "Generated B Roads in " << t->Duration() << " seconds" << endl;
            cout << "... generating extra roads ..." << endl;
        }
        
        t->ReStart();

        vector<Vertex*>* allSettlements = cities;
        allSettlements->insert(allSettlements->end(), townsAndVillages->begin(), townsAndVillages->end());
        Prim* extraRoads = new Prim(allSettlements);
        vector<EdgePair> newRoads = extraRoads->GetExtraEdges();
        graph->AddEdges(newRoads);
        t->End();
        if (VERBOSE){
            cout << "Generated Extra Roads in " << t->Duration() << " seconds" << endl;
        }
        
        timer->End();
        if (VERBOSE){
            cout << "all roads generated: " << timer->Duration() << " seconds" <<endl;
        }
    };



public:
    Generator(int numSettlements, Graph* graph, PrefixTree* searchTree, bool verbose){
        this->numSettlements = numSettlements;
        this->graph = graph;
        this->searchTree = searchTree;
        this->VERBOSE = verbose; 
        this->namer = new NameGenerator();
        this->timer = new Timer("Generator");
        this->cities = new vector<Vertex*>;
        this->citiesAndTowns = new vector<Vertex*>;
        this->towns = new vector<Vertex*>;
        this->townsAndVillages = new vector<Vertex*>;
        this->villages = new vector<Vertex*>;

    }

    Graph* Run(){
        GenerateSettlements();
        GenerateRoads();
        return graph;
    }

    int GetNumCities(){
        return static_cast<int>(cities->size());
    }
    int GetNumTowns(){
        return static_cast<int>(towns->size());
    }
    int GetNumVillages(){
        return static_cast<int>(villages->size());
    }
};
#endif