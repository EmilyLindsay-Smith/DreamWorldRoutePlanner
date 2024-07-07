# DreamWorld Route Planner Design Report

Author: Dr. Emily Lindsay-Smith
Date: July 2024

--------------------------------------------------------------
## The Scenario

Welcome to the DreamWorld Route Planner. 

The route planner creates 100 settlements in a 100x100 unit sized world. 20% of the settlements are large settlements, e.g. citadels; 30% are medium size settlements, e.g. towns; and 50% are small sized settlements, e.g. hamlets.

The route planner generates a road network between the settlements, such that:
	all large settlements are connected by fast roads
	all large and medium settlements are connected by medium roads
	all medium and small settlements are connected by slow roads

The user can interact with the route planner in the following ways:

1) The user can display an alphabetised list of all locations in DreamWorld, and include their settlement type and coordinates
3) The user can search for locations either using the entire string or a substring (prefix).
4) The user can display all available information about a specific location
5) The user can request a path between two locations, and see two routes : one optimised for time and the other for distance
6) The user can request the route to the nearest amenity to a specific location
7) The user can regenerate the settlements and road network in DreamWorld
8) The user can see some information about how the road network was generated. 

## Requirements
GoogleTest is required to run the tests. All other included libraries are part of STL.

## Design

The DreamWorld Route Planner consists of classes. Each class has the following purpose:

| Class			| Purpose						|
|-----------------------|-------------------------------------------------------|	
| CLI	 		| controls user interactions with the application	|
| Engine		|controls all the application functions			|
| Generator		| controls generating the settlements and roads		|
| NameGenerator		|generates names for settlements and friends		|
| Graph			| contains the road network and settlements		|
| Prim			| generates the road network using Prim's Algorithm	|
| Dijkstra		| path finding using Dijkstra's Algorithm		|
| PrefixTree		| links names to vertex points				|
| Vertex		| settlements and their attributes			|


The other .h files are as follows:
| File			| Purpose						|
|-----------------------|-------------------------------------------------------|
| Enums.h		| for enum SettlementType declaration			|
| RoutePlannerUtils.h	| namespace with utility functions			|
| Timer.h		| timer functions					|



Some of the design decisions are discussed below:

### PathFinding

This application required finding the shortest path between two vertices (for route finding) as well as the shortest path between all vertices (for finding nearest amenity). 

The possible choices for this function were Dijkstra's Algorithm, Dial's Algorithm, A* Algorith, and ??THE OTHER ONE??.

Dijkstra + AdjMatrix	Time O(V^2), Space O(V&2)
Dijkstra + AdjList with priority queue 	Time(O(ElogV), Space O(E+V) 
Dial's Algorithm: Time O(numVert * maxEdgeWeight), Space O(numVert * maxEdgeWeight) 
	- however, this is better when the edge weights are only a small set of distinct values. This is not the case with this application, as weights are Euclidean distances calculated as floats or time calculated as Euclidean Distances divided by speed limits. 

In this implementation, the costs, parents and visited are represented as arrays. An alternative would be to have a hashmap, where insertion/search is also O(1) however it is faster to access arrays than hash maps. In the graph, the vertices are in ID order where ID == index

### Road Generation

To generate the road network, there are two main considerations. Firstly, that all the settlements are connected to each other; secondly, that multiple routes exist between settlements.

A minimum spanning tree is a good way to generate a connected graph with a smaller number of edges [and thus save space/time in finding paths]. Two possible choices are Prim's Algorithm and Kruskal's Algorithm. As the graph here is dense (with all possible edges between all vertices), Prim's Algorithm is more efficient than Kruskal's would be.

If Prim's Algorithm is implemented with an adjacency matrix, the time complexity is O(V*2); however, if it is implemented with an adjacency list and a binary heap, the time complexity is O(ElogV) with O(V) space. In theory, the time complexity can be further reduced to O(E + logV) if Fibonacci heaps are used; however in practice this can take longer due to the constants. 

One minimum spanning tree will only generate one possible route between vertices. Therefore, Prim's algorithm is running multiple times in order to generate fast roads, medium roads, and slow roads. 

### SearchTree

The user needs to be able to identify settlements by name. If all the names are known, then a hash based solution is efficient as insertion and search can both be done in constant time (O(1)). However, as the settlement names are generated here as novel words, it is useful for the user to be able to search using only part of the name, even only the first letter. This is not possible do to in constant time with a hash map.

To search for substrings in text, there are two main solutions: processing the search string then searching linearly through the text (e.g. Rabin Karp); or processing the text to facilitate search (e.g. using a trie). As the text (the list of names) does not change constantly, it is a good candidate for processing the text into a trie of some kind. 

A prefix tree is a good solution here. Insertion/Search in prefix trees is O(numWords * averageWordLength), so is faster than pattern matching algorithms such as Rabin Karp. Where a substring is found in the Prefix tree but is not at a leaf, depth first search is used to return all the possible matches. Depth first search is also used to return all the strings in alphabetical order.

Generalised suffix trees do have faster insertion (O(n) for Uskonnen)) and search (O(patternLenth)); however they require more space. Furthermore, in this application is it more useful to return all the strings that start with the same letter, rather than all the strings that contain the same letter.

## Testing
Unit Tests have been written to cover the public methods of these classes. A screenshot showing all tests pass as of TIME can be found HERE.