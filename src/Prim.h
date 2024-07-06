#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include <list>
#include <unordered_map>
#include <queue> // priority_queue
#include <cmath> // for round

#include "Vertex.h"
#include "Graph.h"

#include "RoutePlannerUtils.h"
using namespace RoutePlannerUtils; // for EdgePair
using namespace std;

class PrimGraph;
class Prim;

class PrimGraph{
friend Prim;
private:
   vector<Vertex*>* vertices;
   size_t numVertices;
   unordered_map<Vertex*, unordered_map<Vertex*, float>>* adjList = new  unordered_map<Vertex*, unordered_map<Vertex*, float>>; 

    float CalculateWeight(Vertex* start, Vertex* end){
        int aX = start->GetCoordinates()->x;
        int aY = start->GetCoordinates()->y;
        int bX = end->GetCoordinates()->x;
        int bY = end->GetCoordinates()->y;
        float euclideanDistance = (float) sqrt(pow((aX - bX),2) + pow((aY - bY),2));
        return euclideanDistance;
    }

    void addEdge(Vertex* start, Vertex* end){
        if (start == end){
            return; // don't add an edge to itself
        }
        float dist = CalculateWeight(start, end);
        (*adjList)[start][end] = dist;
        (*adjList)[end][start] = dist;
        return;
    }

public:
    PrimGraph(vector<Vertex*>* vertices){
        this->vertices = vertices;
        this->numVertices = vertices->size();
        for(int i = 0; i < static_cast<int>(numVertices); i++){
            for (int j = 1; j< static_cast<int>(numVertices);j++){
               addEdge((*vertices)[i],(*vertices)[j]);
            }
        }
    };

    unordered_map<Vertex*, unordered_map<Vertex*, float>>* GetAdjList(){
        return this->adjList;
    };     
};


struct EdgePair{
    Vertex* origin;
    Vertex* dest;
    EdgePair(Vertex* o, Vertex* d){
        this->origin = o;
        this->dest = d;
    }
};


class Prim{
private:
    size_t numVertices;
    vector<Vertex*>* vertices;
    unordered_map<Vertex*, unordered_map<Vertex*, float>>* adjList;
    Vertex* currVertex = nullptr;

    static const int INF=99999;
/*
    auto Compare = [](Vertex* lhs, Vertex* rhs){ //custom comparator for priority queue to sort by lowest cost
        return (*adjList)[lhs][currVertex] < (*adjList)[rhs][currVertex]; 
    }
*/
    float GetCost(Vertex* current, Vertex* vertex){
        return (*adjList)[current][vertex];
    }
    vector<Vertex*> merge(Vertex* current, vector<Vertex*> leftVector, vector<Vertex*> rightVector){
        vector<Vertex*> mergedVector;
        int i = 0;
        int j = 0;
        while (i!= static_cast<int>(leftVector.size()) && j != static_cast<int>(rightVector.size())){
            float leftCost = GetCost(current, leftVector[i]);
            float rightCost = GetCost(current, rightVector[j]);
            if(leftCost <= rightCost){ // change to vertexDistance cost
                mergedVector.push_back(leftVector[i++]); // postfix increment gives i for now then increments for next use of i
            }else{
                mergedVector.push_back(rightVector[j++]);
            }
        }
        while (i!=static_cast<int>(leftVector.size())){
            mergedVector.push_back(leftVector[i++]);
        }
        while(j!=static_cast<int>(rightVector.size())){
            mergedVector.push_back(rightVector[j++]);
        }
        return mergedVector;        
    };

    vector<Vertex*> mergeSort(Vertex* current, vector<Vertex*>&adjacentVertices, int start, int end){
        if (start - end == 0){
            vector<Vertex*> t;
            t.push_back(adjacentVertices[start]);
            return t; 
        }
        int midpoint = (start + end ) / 2;

        vector<Vertex*> leftVector;
        vector<Vertex*> rightVector;
        leftVector = mergeSort(current, adjacentVertices, start, midpoint);
        rightVector = mergeSort(current, adjacentVertices, midpoint + 1, end);
        return merge(current, leftVector, rightVector);
        
    };

public:
    Prim(vector<Vertex*>* vertices){
        this->vertices = vertices;
        this->numVertices = vertices->size();
        PrimGraph *tmp = new PrimGraph(vertices);
        this->adjList = tmp->GetAdjList();
    }

    vector<EdgePair> GetExtraEdges(){
        vector<EdgePair> newEdges;
        for (int i = 0; i< static_cast<int>(numVertices); i++){
            Vertex* current = (*vertices)[i];
            unordered_map<Vertex*, float> vertexDistances = (*adjList)[current];
            vector<Vertex*> adjacentVertices = *vertices; // copy of vertices to sort by closest distance to current
            adjacentVertices = mergeSort(current, adjacentVertices, 0, static_cast<int>(numVertices)-1);
            for (int i = 0; i < 2; i++){
                Vertex* chosenVertex = adjacentVertices[3*i];
                newEdges.push_back(EdgePair(current, chosenVertex));
            }
        }
        return newEdges;
    }

    unordered_map<Vertex*, Vertex*> RunPrim(){
        auto Compare = [this](Vertex* lhs, Vertex* rhs){ //custom comparator for priority queue to sort by lowest cost
            return (*adjList)[lhs][currVertex] < (*adjList)[rhs][currVertex]; 
        };
        //Create priority queue for vertices that will be explored
        priority_queue<Vertex*, vector<Vertex*>, decltype(Compare)> pq(Compare);
        //Create map for keys, foundEdgess, and for tracking if vertices included
        unordered_map<Vertex*, float> key;
        unordered_map<Vertex*, Vertex*> foundEdges;
        unordered_map<Vertex*, bool> inMST;
        for (int i = 0; i < numVertices; i++){
            key[(*vertices)[i]] = INF;
            inMST[(*vertices)[i]] = false;
        };
        // Add first item in vertices to pq
        pq.push((*vertices)[0]);
        key[(*vertices)[0]] = 0.0;

        while (!pq.empty()){
            currVertex = pq.top();
            pq.pop();
            if (inMST[currVertex] == true){
                //different key values for same vertex can be included in pq as keys can't be decremented
                //therefore only count the lowest value and ignore other versions
                continue;
            }
            inMST[currVertex] = true;
            for (auto& [adjVertex, cost] : (*adjList)[currVertex]){
                if (inMST[adjVertex] == false && key[adjVertex] > cost){
                    key[adjVertex] = cost;
                    pq.push(adjVertex);
                    foundEdges[adjVertex] = currVertex;
                }
            }
        }
        return foundEdges;
    }
};

#endif