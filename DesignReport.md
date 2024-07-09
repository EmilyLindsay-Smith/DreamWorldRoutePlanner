# DreamWorld Route Planner Design Report

Author: Dr. Emily Lindsay-Smith
Date: July 2024
Purpose: 1000 word report on design decisions for this project

## The Scenario

Welcome to the DreamWorld Route Planner. 

The route planner creates 100 settlements in a 100x100 unit sized world. 20% of the settlements are large settlements, e.g. citadels; 30% are medium size settlements, e.g. towns; and 50% are small sized settlements, e.g. hamlets.

The route planner generates a road network between the settlements, such that:
	all large settlements are connected by fast roads
	all large and medium settlements are connected by medium roads
	all medium and small settlements are connected by slow roads

The user can interact with the route planner in the following ways:

1) The user can display an alphabetised list of all locations in DreamWorld, and include their settlement type and coordinates
2) The user can search for locations either using the entire string or a substring (prefix).
3) The user can display all available information about a specific location
4) The user can request a path between two locations, and see two routes : one optimised for time and the other for distance
5) The user can request the route to the nearest amenity to a specific location
6) The user can regenerate the settlements and road network in DreamWorld

## Requirements
GoogleTest is required to run the tests. All other included libraries are part of STL.

## Design

The DreamWorld Route Planner consists primarily of classes. Each class has the following purpose:

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
To access a given vertex in the graph, I need to be able to search by name or by ID number. To search by name, I implemented a Prefix Tree (see details below). To search by ID, I stored all the vertices in a vector in ID order, such that the vertex with ID=0 is at index 0, ID=1 at index 1.

Similarly in Dijkstra, I represented the edge costs, parent and visited flag as arrays where the index position corresponded to the same ID as in the vertices vector. This approach is superior to a hash map based approach as although insertion and finding are O(1) for both structures, accessing a vector by index is faster than accessing a hash map.

### Road Generation

To generate the road network, there are two main considerations. Firstly, that all the settlements are connected to each other; secondly, that multiple routes exist between settlements.

A minimum spanning tree is a good way to generate a connected graph with a small number of edges [and thus save space/time in finding paths]. I considered the following options:

|Algorithm			|Average Time Complexity|Space Complexity	| Strengths			|
|-------------------------------|-----------------------|-----------------------|-------------------------------|
| Prim (Adjacency Matrix) 	| O (V*2) 		|			| Efficient for dense graphs 	|
| Prim (Binary heap)		| O(ElogV) 		| O(V) 			| Efficient for dense graphs 	|
| Prim (Fibonacci heap)		| O(E+logV) 		|			| Efficient for dense graphs 	|
| Kruskal			| O(Nlog(E)+Nlog(N)) 	| 			| Efficient for sparse graphs 	|

As the MST algorithm has to consider all possible edges in a 100x100 space here, Prim is a more efficient choice. Implementing it with an adjacency list and binary heap based priority queue gives complexity improvements over Kruskal and other Prim implementations. While in theory a Fibonacci heap gives better time complexity, in practice it can be slower due to the constants. 

Prim generates one possible route between vertices. To give a wider range of road types, here Prim is called multiple times.

### SearchTree

The user needs to be able to identify settlements by name. If all the names are known, then a hash based solution is efficient as insertion and search can both be done in constant time (O(1)). However, as the settlement names are generated here as novel words, it is useful for the user to be able to search using only part of the name, even only the first letter. This is not possible do to in constant time with a hash map.

To search for substrings in text, there are two main solutions: processing the search string then searching linearly through the text (e.g. Rabin Karp, Knuth-Morris-Pratt, Aho-Corasick); or processing the text to facilitate search (e.g. using a trie). As the text (the list of names) does not change constantly, it is a good candidate for processing the text into a trie of some kind.

A prefix tree is a good solution here. Insertionh in prefix trees is O(numWords * averageWordLength) but search is O(keySize), so is faster than pattern matching algorithms such as Rabin Karp. Where a substring is found in the Prefix tree but is not at a leaf, depth first search is used to return all the possible matches. Depth first search is also used to return all the strings in alphabetical order.

the pattern search algorithms have an average time complexity between O(patternLength + textLength). However, to return all of the names in alphabetical order, or a list of hte first characters of all the names (both useful functions in this application), further sorting algorithms must be used. 

Generalised suffix trees do have faster insertion (O(n) for Uskonnen)) and search (O(patternLength)); however they require more space. Furthermore, in this application is it more useful to return all the strings that start with the same letter, rather than all the strings that contain the same letter.


### PathFinding

This application required finding the shortest path between two vertices (for route finding) as well as the shortest path between all vertices (for finding nearest amenity). 

I considered the following options:

| Algorithm 			| Average Time Complexity 	| Space Complexity 	|
|-------------------------------|-------------------------------|-----------------------|
| Dijkstra  			| O(V*V) 			| O (E+V)		| 
| Dijisktra (Binary Heap) 	| O((E+V)logV) 			| O(E+V)		| 
| Dijkstra (Fibonacci Heap) 	| O (E+(VlogV) 			|			| 
| Dial				| O(E+(num buckets * V)) 	| O (V * maxWeight) 	|

Computing the shortest paths to all vertices is an advantage in this application as it facilitates searching for the nearest amenity. Therefore, Dijkstra is preferable to A* which only returns a single path. Dial's Algorithm can be faster than Dijkstra, however it relies on having a finite number of weights which is not applicable here as edge weights are Euclidean distances stored as floats. I implemented Dijkstra with an adjacency list graph and a binary heap priority queue, as this is faster than with an adjacency matrix. Dijkstra with binary heaps can has a worst case time complexity of O((V^2)logV) if the graph is very dense. However here the number of edges is low (147) compared to total possible edges (9999). While in theory using Fibonacci Heaps has a lower complexity, it can be slower in practice due to large constants.

## Testing
Unit Tests have been written to cover the public methods of Dijkstra, Generator, Graph, PrefixTree, Prim, RoutePlannerUtils, and Vertex. A record of the latest test output is at /testoutput.txt
