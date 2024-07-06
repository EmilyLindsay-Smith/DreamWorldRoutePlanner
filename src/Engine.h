#ifndef ENGINE_H
#define ENGINE_H

#include <set>

#include "Vertex.h"
#include "PrefixTree.h"
#include "Graph.h"
#include "Generator.h"
#include "Dijkstra.h"


using namespace std;

// ENSURE TO JUST RETURN A CONTAINER OF INFORMATION - CLI/MAIN WILL DETERMINE HOW TO PORTRAY THE RESULTS

class Engine{
private:
    int numSettlements;
    PrefixTree* searchTree;
    Graph* graph;
    Generator* generator;
    Dijkstra* pathFinder; 

public:
    Engine(int size){
        this->numSettlements = size;
        this->searchTree = new PrefixTree();
        this->graph = new Graph(numSettlements);
        this->generator = new Generator(numSettlements, graph, searchTree, true);
        this->pathFinder = new Dijkstra(graph);
    }

// Set Up Landscape - run generator
    void GenerateLandscape(){
        generator->Run();
        return;
    }
    int GetNumRoads(){
        return graph->GetNumberRoads();
    }
  
    int CheckPrefixTree(){
        return searchTree->numStrings;
    }
// Retrieve ID/Pointer to Settlement
    vector<RefPair>* ChooseBetweenSettlements(vector<RefPair>* placeVector, int choice){
        //return a single RefPair from a vector of multiple RefPairs
        cout << "49" << endl;
        vector<RefPair>* results = new vector<RefPair>;
        results->push_back((*placeVector)[choice]);
        cout << "52" << endl;
        string chosenPlace= (*results)[0].queryString;
        cout << "54" << endl;
        chosenPlace[0] = toupper(chosenPlace[0]);
        cout << "56" << endl;
        return results;
    };
    
    int RetrieveSettlementID(vector<RefPair>*placeVector){
        // Get the ID for the settlement
        return (*placeVector)[0].stringRef->GetID(); 
    };

    Vertex* RetrieveSettlementPointer(vector<RefPair>* placeVector){
        // Extract stringRef from the RefPair of queryString and stringRef
        return (*placeVector)[0].stringRef; 
    };

    vector<RefPair>* RetrieveSettlement(string placeName){
        // Retrieve RefPair of queryString and stringRef from prefix tree
        vector<RefPair>* results = searchTree->Search(placeName);
        return results;
    }

// Get Settlement & Road Info
    set<string>* ListAllSettlements(){
        set<string>* placeNames = searchTree->FindAllLocations();
        return placeNames;
    };

    vector<RefPair>* ListAllSettlementsVerbose(){
        vector<RefPair>* placeNames= searchTree->FindAllLocationsVerbose();
        return placeNames;
    };

    void DisplaySettlementInfo(Vertex* place){
        place->Display();
        return;
    };

    void PrintAmenityTypes(){
        return;
    };

    string IdentifyRoadDirection(Vertex* origin, Vertex* dest){
        // Identify the compass direction of the road
        int origin_x = origin->GetCoordinates()->x;
        int origin_y = origin->GetCoordinates()->y;
        int destination_x = dest->GetCoordinates()->x;
        int destination_y = dest->GetCoordinates()->y;
        string direction;
        //North vs South
        if (origin_y > destination_y){
            direction += "south";
        }else if (origin_y < destination_y){
            direction += "north";
        }
        //East vs West
        if (origin_x > destination_x){
            direction += "east";
        }else if (origin_x < destination_x){
            direction += "west";
        }
        return direction;
    }

    string IdentifyRoadType(Vertex* origin, Vertex* dest){
        //Identify if road is a motorway/ A Road / B Road
        SettlementType startSett = origin->GetSettlement();
        SettlementType endSett = dest->GetSettlement();
        int roadType = startSett + endSett;
        string road;
        switch(roadType){
            // enums of SettlementType: city:0, town:1, village:2
            case 0 : road = "expressway"; break; // two cities -> motorway
            case 1 : road = "highway"; break; // one city one town -> A Road
            case 2 : road = "highway"; break; // two towns -> A Road
            case 3 : road = "lane"; break; // one town one village -> B Road
            case 4 : road = "lane"; break; // two villages -> B Road
            default: road = "unknown"; break;
        }
        return road;
    }
// Find Paths
    float FindPathCost(Vertex* origin, Vertex* destination, string TimeVsDist){
        vector<float>* allPathCosts = pathFinder->GetPaths(origin, TimeVsDist);
        float pathCost = (*allPathCosts)[destination->GetID()];
        return pathCost;
    }

    stack<Vertex*> FindPath(Vertex* origin, Vertex* destination, string TimeVsDist, float pathCost){
        stack<Vertex*> path;
        if (pathCost == pathFinder->INF){ // if there is no path
            path.push(nullptr);
        }else{
            path = pathFinder->ReconstructPath(origin, destination, TimeVsDist);
        }
        return path;
    };

    Vertex* FindNearestAmenity(Vertex* origin, string amenity, string TimeVsDist){
        int locationID = pathFinder->GetNearestAmenity(origin, TimeVsDist, amenity);
        Vertex* location = graph->GetVertexPointer(locationID);
        return location;
    };

    vector<AmenityCost> FindNearestAmenities(Vertex* origin, string amenity, int numberOfAmenities, string TimeVsDist){
        vector<AmenityCost> amenitiesByID = pathFinder->GetNearestXAmenities(origin, TimeVsDist, amenity, numberOfAmenities);
        return amenitiesByID;
    };

};

#endif