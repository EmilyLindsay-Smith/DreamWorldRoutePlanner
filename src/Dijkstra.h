#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <stack>
#include <queue> // for priority_queue
#include <algorithm> //for find
#include <functional> // for function

#include "Graph.h"

using namespace std;


struct AmenityCost{
    Vertex* location;
    float cost;
    AmenityCost(Vertex* location, float cost){
        this->location = location;
        this->cost = cost;
    }
};


class Dijkstra{
private:
    Graph* graph;
    int numVertices = 0;
    vector<Vertex*>* vertices;
    
    vector<float>* cost;
    vector<int>* parent;
    int latestSource = -1;
    string latestCostType = "";
    /*TODO: Route Cache for to avoid recalcuating already done routes*/
public:
    const float INF = 99999.0;
    Dijkstra(Graph* graph){
        this->graph = graph;
        this->vertices = graph->GetVertices();
        this->cost = new vector<float>(numVertices, INF);
    }
/*
    bool Compare(int lhs, int rhs){ //custom comparator for priority queue to sort by lowest cost
        return cost[lhs] < cost[rhs]; 
    }
*/
    int GetNearestAmenity(Vertex* source, string CostType, string amenity){
        cost = GetPaths(source, CostType);
        auto Compare = [this](int lhs, int rhs){ //custom comparator for priority queue to sort by lowest cost
            return (*cost)[lhs] < (*cost)[rhs]; 
        };

        priority_queue<int, vector<int>, decltype(Compare)> pq(Compare);
        for (int i = 0; i < numVertices; i++){
            pq.emplace(i);
        }
        bool foundAmenity = false;
        int currVertex = -1;
        while (!foundAmenity && !pq.empty()){
            currVertex = pq.top();
            pq.pop();
            vector<string> amenities = (*vertices)[currVertex]->GetAmenities();
            if ( std::find(amenities.begin(), amenities.end(), amenity) != amenities.end() ){
                foundAmenity = true;
            }
        }
        if (foundAmenity){
            return currVertex; 
        }else{
            return -1;
        }
    };

    vector<AmenityCost> GetNearestXAmenities(Vertex* source, string CostType, string amenity, int desiredCount){
        cost = GetPaths(source, CostType);
        vector<AmenityCost> amenityLocations;
        auto Compare = [this](int lhs, int rhs){ //custom comparator for priority queue to sort by lowest cost
            return (*cost)[lhs] < (*cost)[rhs]; 
        };
        priority_queue<int, vector<int>, decltype(Compare)> pq(Compare);
        for (int i = 0; i < numVertices; i++){
            pq.emplace(i);
        }
        int count = 0; 
        while (count != desiredCount && !pq.empty()){
            int currVertex = pq.top();
            pq.pop();
            vector<string> amenities = (*vertices)[currVertex]->GetAmenities();
            if ( std::find(amenities.begin(), amenities.end(), amenity) != amenities.end() )
                count++;
                amenityLocations.push_back(AmenityCost((*vertices)[currVertex], (*cost)[currVertex]));
        }
        return amenityLocations;
    };


    stack<Vertex*> ReconstructPath(Vertex* origin, Vertex* goal, string CostType){
        if (origin->GetID() != latestSource || CostType != latestCostType){
            vector<float>* pathCosts = GetPaths(origin, CostType);
        }

        stack<Vertex*> path;
        Vertex* current = goal;
        int currentID = current->GetID();
        // Add each vertex to stack path
        int count = 0;
        while((*parent)[currentID] != currentID && current != origin && count != numVertices){
            path.push(current);
            currentID = (*parent)[currentID];
            current = (*vertices)[currentID];
            count++;
        }
        path.push(current);
        return path;
    }



    vector<float>* GetPaths(Vertex* source, string CostType){
        if (numVertices == 0){ // need to update numVertices once graph has been filled
            this->numVertices = graph->GetNumberVertices();
        }
        if (source->GetID() == latestSource && CostType == latestCostType){
            return cost; // if last call is the same, return latest computed value
        }else{
            latestSource = source->GetID();
            latestCostType = CostType;
        }

        parent = new vector<int>;
        for (int i = 0; i < numVertices; i++){
            parent->push_back(i); // set parent as self;
        };
        auto Compare = [this](int lhs, int rhs){ //custom comparator for priority queue to sort by lowest cost
            return (*cost)[lhs] < (*cost)[rhs]; 
        };
        priority_queue<int, vector<int>, decltype(Compare)> pq(Compare);
        cost = new vector<float>(numVertices, INF); //reinitialise cost here 
        vector<bool> visited(numVertices, false);
        int sourceIndex = source->GetID();
        cost->at(sourceIndex) = 0;
        pq.emplace(sourceIndex); 
        while (!pq.empty()){  //depends on priorityqueue imp
            int currVertex = pq.top();
            pq.pop();
            visited[currVertex] = true; // may need to make visited a map?? as vertices as not numbered here
            for (auto next: graph->GetAdjacentVerticesByID(currVertex)){
                int adjVert = next; // depends on imp
                float weight = graph->GetCost(currVertex, next, CostType); // depends on imp
                if (visited[adjVert] == false && (*cost)[adjVert] > (*cost)[currVertex]){
                   (*cost)[adjVert] = (*cost)[currVertex] + weight;
                    pq.emplace(adjVert);
                    (*parent)[adjVert] = currVertex;
                    //(*vertices)[adjVert]->SetParent((*vertices)[currVertex]);
                }
                if (visited[adjVert] && (*cost)[adjVert] == 0){
                    //(*vertices)[adjVert]->SetParent((*vertices)[currVertex]);
                    (*parent)[adjVert] = currVertex;
                }
            }
        }
        return cost; //vector of costs; index is same as index in vertices;
    }

};

#endif