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
    int numberEdges;
    int numberVertices;
    vector<Vertex*>* vertices;
    unordered_map<int, unordered_map<int, TravelCosts*>>* adjList; //decide on representation 

public:
    Graph(int size){
        this->numberVertices = 0;
        this->numberEdges = 0;
        this->vertices = new vector<Vertex*>(size);
        this->adjList = new unordered_map<int,unordered_map<int, TravelCosts* >>[size];
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
    
    float MotorwayCost(float distance){
        return distance / 10 ;
    }
    float ARoadCost(float distance){
        return distance / 5 ; 
    }
    float BRoadCost(float distance){
        return distance / 2 ; 
    }

    float CalculateTimeCost(Vertex* start, Vertex* end){
        float distance = CalculateDistCost(start, end);
        SettlementType startSett = start->GetSettlement();
        SettlementType endSett = end->GetSettlement();
        int roadType = startSett + endSett;
        float cost;
        switch(roadType){
            // enums of SettlementType: city:0, town:1, village:2
            case 0 : cost = MotorwayCost(distance); break; // two cities -> motorway
            case 1 : cost = ARoadCost(distance); break; // one city one town -> A Road
            case 2 : cost = ARoadCost(distance); break; // two towns -> A Road
            case 3 : cost = BRoadCost(distance); break; // one town one village -> B Road
            case 4 : cost = BRoadCost(distance); break; // two villages -> B Road
            default: throw runtime_error("Road combination not recognised to compute time cost");
        }
        return cost;
    };

    float CalculateTimeCost(int start, int end){
        Vertex* startVert = (*vertices)[start];
        Vertex* endVert = (*vertices)[end];
        return CalculateTimeCost(startVert, endVert);
    };

    float CalculateDistCost(Vertex* start, Vertex* end){
        int aX = start->GetCoordinates()->x;
        int aY = start->GetCoordinates()->y;
        int bX = end->GetCoordinates()->x;
        int bY = end->GetCoordinates()->y;
        float euclideanDistance = sqrt(pow((aX - bX),2) + pow((aY - bY),2));
        return euclideanDistance;
    };

    float CalculateDistCost(int start, int end){
        Vertex* startVert = (*vertices)[start];
        Vertex* endVert = (*vertices)[end];
        return CalculateDistCost(startVert, endVert);
    };

    
// Add vertices and Edges
    void AddVertex(Vertex* vertex){
        (*vertices)[vertex->GetID()] = vertex; // place into vector according to ID number
        numberVertices++;
        return;
    }
    
    void AddEdge(int start, int end){
        float TimeCost = CalculateTimeCost(start, end); // calc me
        float DistCost = CalculateDistCost(start, end); // calc me
        (*adjList)[start][end] = new TravelCosts(TimeCost, DistCost);
        (*adjList)[end][start] = new TravelCosts(TimeCost, DistCost); //assuming undirected graph
        this->numberEdges++;
        return;
    };
    
    void AddEdge(Vertex* start, Vertex* end){
        float TimeCost = CalculateTimeCost(start, end); // calc me
        float DistCost = CalculateDistCost(start, end); // calc me
        (*adjList)[start->GetID()][end->GetID()] = new TravelCosts(TimeCost, DistCost);
        (*adjList)[end->GetID()][start->GetID()] = new TravelCosts(TimeCost, DistCost);
        this->numberEdges++;
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
    int GetCost(int start, int end, string costType){
        if (costType == "Time"){
            return (*adjList)[start][end]->TimeCost;
        }else{
            return (*adjList)[start][end]->DistCost;
        }
    }
    int GetCost(Vertex* start, Vertex* end, string costType){
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