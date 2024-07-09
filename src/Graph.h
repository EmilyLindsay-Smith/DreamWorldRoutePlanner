#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <cmath>

#include "Vertex.h"
#include "Prim.h" // for EdgePair

using namespace std;

struct TravelCosts{
    float TimeCost;
    float DistCost;

    TravelCosts(float TimeCost, float DistCost){
        this->TimeCost = TimeCost;
        this->DistCost = DistCost;
    }
};

class Graph{
private:
    static const int INF=99999;
    int MAX_SIZE;
    int numberEdges;
    int numberVertices;
    vector<Vertex*>* vertices;
    unordered_map<int, unordered_map<int, TravelCosts*>>* adjList;

    // Calculate Road Costs
    float FastRoadCost(float distance){
        return distance / 20 ;
    }
    float MediumRoadCost(float distance){
        return distance / 10 ; 
    }
    float SlowRoadCost(float distance){
        return distance / 5 ; 
    }
// Calculate TimeCost
    float CalculateTimeCost(Vertex* start, Vertex* end){
        float distance = CalculateDistCost(start, end);
        SettlementType startSett = start->GetSettlement();
        SettlementType endSett = end->GetSettlement();
        int roadType = startSett + endSett;
        float cost;
        switch(roadType){
            // enums of SettlementType: placeBig:0, placeMedium:1, placeSmall:2
            case 0 : cost = FastRoadCost(distance); break; // two placeBig -> fastRoad
            case 1 : cost = MediumRoadCost(distance); break; // one placeBig one placeMedium -> mediumRoad
            case 2 : cost = MediumRoadCost(distance); break; // two placeMediums -> mediumRoad
            case 3 : cost = SlowRoadCost(distance); break; // one placeMedium one placeSmall -> slowRoad
            case 4 : cost = SlowRoadCost(distance); break; // two placeSmalls -> slowRoad
            default: throw runtime_error("Road combination not recognised to compute time cost");
        }
        return cost;
    };

    float CalculateTimeCost(int start, int end){
        Vertex* startVert = (*vertices)[start];
        Vertex* endVert = (*vertices)[end];
        return CalculateTimeCost(startVert, endVert);
    };

//Calculate Distance Cost
    float CalculateDistCost(Vertex* start, Vertex* end){
        int aX = start->GetCoordinates()->x;
        int aY = start->GetCoordinates()->y;
        int bX = end->GetCoordinates()->x;
        int bY = end->GetCoordinates()->y;
        float euclideanDistance = (float) sqrt(pow((aX - bX),2) + pow((aY - bY),2));
        return euclideanDistance;
    };

    float CalculateDistCost(int start, int end){
        Vertex* startVert = (*vertices)[start];
        Vertex* endVert = (*vertices)[end];
        return CalculateDistCost(startVert, endVert);
    };


public:
    Graph(int size){
        this->MAX_SIZE = size;
        this->numberVertices = 0;
        this->numberEdges = 0;
        this->vertices = new vector<Vertex*>(size);
        this->adjList = new unordered_map<int,unordered_map<int, TravelCosts* >>[size];
        }
    ~Graph(){
        vertices->clear();
        delete vertices;
        adjList->clear();
        delete adjList;
    }

// Basic Getters
    int GetNumberVertices(){
        return this->numberVertices;
    }
    vector<Vertex*>* GetVertices(){
        return this->vertices;
    }
    
    Vertex* GetVertexPointer(int ID){
        return (*vertices)[ID];
    }

    int GetNumberRoads(){
        return this->numberEdges;
    }

    
// Add vertices and Edges
    void AddVertex(Vertex* vertex){
        if (numberVertices != MAX_SIZE){
            (*vertices)[vertex->GetID()] = vertex; // place into vector according to ID number
            numberVertices++;
        }
        return;
    }
    
    void AddEdge(int start, int end){
        float TimeCost = CalculateTimeCost(start, end); 
        float DistCost = CalculateDistCost(start, end); 
        (*adjList)[start][end] = new TravelCosts(TimeCost, DistCost);
        (*adjList)[end][start] = new TravelCosts(TimeCost, DistCost); //assuming undirected graph
        this->numberEdges++;
        return;
    };
    
    void AddEdge(Vertex* start, Vertex* end){
        float TimeCost = CalculateTimeCost(start, end); 
        float DistCost = CalculateDistCost(start, end); 
        (*adjList)[start->GetID()][end->GetID()] = new TravelCosts(TimeCost, DistCost);
        (*adjList)[end->GetID()][start->GetID()] = new TravelCosts(TimeCost, DistCost);
        this->numberEdges++; //only incrementing by 1 as assuming undirected graph -> 2 edges needed in adjList but underlyingly 1 road added
        return;
    };

    void AddEdges(unordered_map<Vertex*, Vertex*> edgesMST){ 
        for (auto& [start, end] : edgesMST){
            AddEdge(start, end);
        }
        return;
    }

    void AddEdges(vector<EdgePair> edgesMST){ 
        for (auto element : edgesMST){
            AddEdge(element.origin, element.dest);
        }
        return;
    }
// Get Useful Info
    float GetCost(int start, int end, string costType){
        if (costType == "Time"){
            return (*adjList)[start][end]->TimeCost;
        }else{
            return (*adjList)[start][end]->DistCost;
        }
    }
    float GetCost(Vertex* start, Vertex* end, string costType){
        if (costType == "Time"){
            return (*adjList)[start->GetID()][end->GetID()]->TimeCost;
        }else{
            return (*adjList)[start->GetID()][end->GetID()]->DistCost;
        }
    }

    vector<Vertex*> GetAdjacentVertices(Vertex* source){
        vector<Vertex*> adjacentVertices;
        int sourceIndex = source->GetID();
        for (auto dest: (*adjList)[sourceIndex]){
            int destIndex = dest.first;
            adjacentVertices.push_back((*vertices)[destIndex]);
        }
        return adjacentVertices;
    }

    vector<int> GetAdjacentVerticesByID(Vertex* source){
        vector<int> adjacentVertices;
        int sourceIndex = source->GetID();
        for (auto dest: (*adjList)[sourceIndex]){
            int destIndex = dest.first;
            adjacentVertices.push_back(destIndex);
        }
        return adjacentVertices;
    }

    vector<int> GetAdjacentVerticesByID(int sourceIndex){
        vector<int> adjacentVertices;
        for (auto dest: (*adjList)[sourceIndex]){
            int destIndex = dest.first;
            adjacentVertices.push_back(destIndex);
        }
        return adjacentVertices;
    }
};

#endif