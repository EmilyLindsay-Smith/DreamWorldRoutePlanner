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
    Engine(int size, vector<string>* standardAmenities, vector<string>* specialAmenities){
        this->numSettlements = size;
        this->searchTree = new PrefixTree();
        this->graph = new Graph(numSettlements);
        this->generator = new Generator(numSettlements, graph, searchTree, standardAmenities, specialAmenities, true);
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
        vector<RefPair>* results = new vector<RefPair>;
        results->push_back((*placeVector)[choice]);
        string chosenPlace= (*results)[0].queryString;
        chosenPlace = MakeSentenceCase(chosenPlace);
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
            // enums of SettlementType: placeBig:0, placeMedium:1, placeSmall:2
            case 0 : road = "expressway"; break; // two placeBigs -> motorway
            case 1 : road = "highway"; break; // one placeBig one placeMedium -> A Road
            case 2 : road = "highway"; break; // two placeMediums -> A Road
            case 3 : road = "lane"; break; // one placeMedium one placeSmall -> B Road
            case 4 : road = "lane"; break; // two placeSmalls -> B Road
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
        cout << "e150" << endl;
        int locationID = pathFinder->GetNearestAmenity(origin, TimeVsDist, amenity);
        cout << "e152" << endl;
        Vertex* location = graph->GetVertexPointer(locationID);
        cout << "e154" << endl;
        return location;
    };


};

#endif