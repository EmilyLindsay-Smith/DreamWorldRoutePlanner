# DreamWorld Route Planner Design Report

Author: Dr. Emily Lindsay-Smith
Date: July 2024
Purpose: 1000 word report on design decisions for this project

## The Scenario

Welcome to the DreamWorld Route Planner. 

The route planner creates 100 settlements in a 100x100 unit sized world. 20% of the settlements are large, 30% are medium and 50% are small. It generates a road network between the settlements, such that:
	large settlements are connected by fast roads
	large and medium settlements are connected by medium roads
	medium and small settlements are connected by slow roads

The user can perform the following actions:

1) Display an alphabetised list of all locations, including settlement type and coordinates
2) Search for locations either using the entire string or a substring
3) Display all available information about a specific location
4) Request a path between two locations, and receive two routes : shortest distance and fastest time
5) Request the nearest amenity to a specific location
6) Regenerate the settlements and road network

## Requirements
GoogleTest is required to run the tests. All other included libraries are part of STL.

## Design

The DreamWorld Route Planner classes have the following purposes:

| Class			| Purpose						|
|-----------------------|-------------------------------------------------------|	
| CLI	 		| controls user interactions with the application	|
| Engine		| controls all the application functions		|
| Generator		| controls generating the settlements and roads		|
| NameGenerator		| generates names for settlements and friends		|
| Graph			| contains the road network and settlements		|
| Prim			| generates the road network using Prim's Algorithm	|
| Dijkstra		| path finding using Dijkstra's Algorithm		|
| PrefixTree		| links names to vertex points				|
| Vertex		| settlements and their attributes			|

Some of the design decisions are discussed below:

### Vertex and Edge Containers
To access a given vertex in the graph, I need to be able to search by name or by ID number. To search by name, I implemented a Prefix Tree. To search by ID, I stored all the vertices in a vector in ID order, such that the vertex with ID=0 is at index 0, ID=1 at index 1, etc. 

Similarly in the Dijkstra class, I represented the edge costs, parent and visited flag as vectors where the index position corresponded to ID, as in the vertices vector. This approach is superior to a hash map based approach as, although insertion and finding are O(1) for both structures, accessing a vector by index is faster than accessing a hash map.

### Road Generation

I needed to generate a connected road network with multiple routes between settlements.

A Minimum Spanning Tree algorithm can generate a connected graph with the fewest edges [which saves space/time in finding paths]. I considered the following algorithms:

| Algorithm			| Average Time Complexity | Space Complexity	|
|-------------------------------|-------------------------|---------------------|
| Prim (Adjacency Matrix) 	| O(V*V) 		  | O(V*V)		| 
| Prim (Binary heap)		| O((V+E)logV) 		  | O(V + E) 		| 
| Prim (Fibonacci heap)		| O(E+logV) 		  | O(V + E) 		| 
| Kruskal			| O(Elog(E)+Elog(V)) 	  | O(V + E) 		|

As the MST algorithm has to consider all possible edges in a 100x100 space here, Prim is preferred over Kruskal as it is more efficient in dense graphs. An adjacency list with binary heap based priority queue implementation gives complexity improvements over Kruskal and other Prim implementations. While in theory a Fibonacci heap gives better time complexity, in practice it can be slower due to the hidden constants. 

Prim generates one possible route between vertices. To give a wider range of road types, I called Prim 5 times on different subsets of settlements.

### SearchTree

The user needs to be able to identify settlements by name. If all the names are known, then a hash based solution is efficient as insertion and search can both be done in constant time (O(1)). However, as the settlement names are generated here as novel words, it is useful for the user to be able to search using only part of the name, even only the first letter. This is not possible do to in constant time with a hash map. 

I considered the following solutions:
 
| Solution			| Insertion 				| Search				|	
|-------------------------------|---------------------------------------|-------------------------------|
| Pattern match e.g. Rabin Karp	| O(1) *(hash insertion)*		| O(patternLength + textLength)	|				
| Prefix Tree			| O(numWords * averageWordLength)	| O(patternLength)		| 
| Suffix Tree e.g. Uskonnen	| O(n)					| O(patternLength) 		| 

To search for substrings in text, there are two main solutions: processing the search string then searching linearly through the text (e.g. Rabin Karp, Knuth-Morris-Pratt, Aho-Corasick); or processing the text to facilitate search (e.g. using a trie). As the text (the list of names) does not change, this application is a good candidate for processing the text into a trie to permit faster search times. While generalised suffix trees have faster insertion and search than prefix trees, they return strings where the pattern is anywhere in the word. As the stored strings are novel to the user here, it is more useful to only return strings that start with the search pattern. Therefore a prefix tree is the preferred option for sorting the settlement names here.

### PathFinding

The user can request the shortest path between two vertices as well as the shortest path between all vertices (for finding nearest amenity). 

I considered the following algorithms:

| Algorithm 			| Average Time Complexity 	| Space Complexity 			|
|-------------------------------|-------------------------------|---------------------------------------|
| A*				| *depends on heuristics*	| O(branching factor * nodes on path)	|
| Dijkstra  			| O(V^2) 			| O(E+V)				| 
| Dijisktra (Binary Heap) 	| O((E+V)logV) 			| O(E+V)				| 
| Dial				| O(E+(num buckets * V)) 	| O(V * maxWeight) 			|
| Floyd-Warshall		| O(V^3)			| O(V*V)				|

Computing the shortest paths to all vertices is needed to search for the nearest amenity. A* only returns a single path so is unsuitable. Dial's Algorithm can be faster than Dijkstra, however it relies on having a finite number of weights. This is unsuitable as here edge weights are Euclidean distances stored as floats. Floyd-Warshall generates all routes between all vertices, but has a greater time complexity than Dijkstra run V times; furthermore, it requires more space to store all the computed path costs and path parents. Therefore, Dijkstra is the preferred choice. 

I implemented Dijkstra with an adjacency list graph and a binary heap priority queue, as this is faster than with an adjacency matrix. Dijkstra with binary heaps can has a worst case time complexity of O((V*V)logV) if the graph is very dense. However here the number of edges is low (147) compared to total possible edges (9999) so better time complexity can be expected.

## Testing
Unit Tests have been written to cover the public methods of Dijkstra, Generator, Graph, PrefixTree, Prim, RoutePlannerUtils, and Vertex. A record of the latest test output is at /testoutput.txt
