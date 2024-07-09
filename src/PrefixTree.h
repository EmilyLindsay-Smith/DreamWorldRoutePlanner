#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#define ALPHABET_SIZE (26) // defined globally as used for both Node & PrefixTree

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "Vertex.h"
#include "RoutePlannerUtils.h" // for charToIndex, IndexToChar

using namespace std;
using namespace RoutePlannerUtils;


struct RefPair{
    // used in PrefixTree
    string queryString;
    Vertex* stringRef;
    RefPair(string x, Vertex* y){
        this->queryString = x;
        this->stringRef = y;
    }
// Overloaded operators - needed for e.g. set<RefPair>

    bool operator<(const RefPair& rhs) const {
        return this->stringRef->GetID() < rhs.stringRef->GetID();
    };

    bool operator>(const RefPair& rhs) const {
        return this->stringRef->GetID() > rhs.stringRef->GetID();
    };
    
    bool operator==(const RefPair& rhs) const {
        return this->stringRef->GetID() == rhs.stringRef->GetID();
    };
    bool operator!=(const RefPair& rhs) const {
        return this->stringRef->GetID() != rhs.stringRef->GetID();
    }

};

class Node{
public:
    Node* children[ALPHABET_SIZE];
    bool isWordEnd;
    Vertex* stringRef;

    Node(){
        this->isWordEnd = false;
        this->stringRef = nullptr;
        for (int i = 0 ; i < ALPHABET_SIZE; i++){
            // initialises all chidlren to null pointer
            this->children[i] = nullptr;
        }
    };
    // Utility func primarily for debugging
    void PrintChildren(){
        for (int i = 0; i< ALPHABET_SIZE; i++){
            if (this->children[i] != nullptr){
                cout << IndexToChar(i) << "," << endl;
            }
        }
        cout << endl;
    };
};

class PrefixTree{
private:
    Node* root;

    vector<RefPair>* FindMatches(Node* node, string query, vector<RefPair>* currentResults){
        // Looks for partial matches for query in the tree
        if (node->isWordEnd){ // partial match found
            currentResults->push_back(RefPair(query, node->stringRef));
        };

        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (node->children[i] != nullptr){
                char child = IndexToChar(i);
                string extendedQuery = query + child; 
                FindMatches(node->children[i], extendedQuery, currentResults);
            }
        }
        return currentResults;
    }

        set<string>* FindAllStrings(Node* node, string currString, set<string>* currentResults, set<Node*>* visited){
        //DFS to retrieve all strings in tree in lexicographical order
        visited->insert(node);
        if (node->isWordEnd){
            currentResults->insert(currString);
        }
        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (node->children[i] != nullptr && (visited->find(node->children[i])==visited->end())){
                char c = IndexToChar(i);
                string newString = currString + c;
                FindAllStrings(node->children[i], newString, currentResults, visited);
            }
        }
        return currentResults;
    }

    vector<RefPair>* FindAllStringsVerbose(Node* node, string currString, vector<RefPair>* currentResults, set<Node*>* visited){
        //DFS to retrieve all strings in tree in lexicographical order
        visited->insert(node);
        if (node->isWordEnd){
            currentResults->push_back(RefPair(currString, node->stringRef));
        }
        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (node->children[i] != nullptr && (visited->find(node->children[i])==visited->end())){
                char c = IndexToChar(i);
                string newString = currString + c;
                FindAllStringsVerbose(node->children[i], newString, currentResults, visited);
            }
        }
        return currentResults;
    }


public:
    int numStrings;
// Constructor
    PrefixTree(){
        this->numStrings = 0;
        this->root = new Node();
    }
// Insert New String
    bool Insert(string key, Vertex* stringRef){
        if (ContainsNonAlpha(key)) return false; // if non-alphabetical chars present
        key = MakeLowerCase(key);
        //Iterates through current tree, adding nodes for chars currently not in the tree
        Node* node = root;
        for (int i = 0; i < key.length(); i++){
            int charIndex = CharToIndex(key[i]);
            if(node->children[charIndex] == nullptr){
                //Add new child node if char not a current child
                node->children[charIndex] = new Node();
            }
            node = node->children[charIndex];
        }
        //mark last node as leaf
        if (node->stringRef != nullptr){
            // then this string is already present in the tree, will not overwrite existing stringRef
            return false;
        }else{
            node->isWordEnd = true;
            node->stringRef = stringRef;
            this->numStrings++;
            return true ;
        }
    }
//Check if string present in the tree
   vector<RefPair>* Search(string query){
        if (ContainsNonAlpha(query)){// if non-alphabetical chars present
            vector<RefPair>* nullResults = new vector<RefPair>;
            return nullResults;
        }  
        query = MakeLowerCase(query);
        // Searches for query in tree; if only partial match found, calls FindMatches() to retrieve all partial matches
        Node* node = root;
        vector<RefPair> *currentResults = new vector<RefPair>;
        // Check if substring is could be present in the tree
        for (char c: query){
            int charIndex = CharToIndex(c);
            if (node->children[charIndex] == nullptr){
                //substring cannot exist in the tree
                return currentResults; //empty vector
            }
            // update node to keep running through the substring
            node = node->children[charIndex];
        }
        //If prefix is present in the tree, check if the whole word has be found:
        if (node->stringRef != nullptr){
            currentResults->push_back(RefPair(query, node->stringRef));
            return currentResults;
        }
        // Otherwise, look for the partial matches
        return FindMatches(node, query, currentResults);
    }

// Get All locations in lexicographical order
    set<string>* FindAllLocations(){
        // Utility Func to call FindAllStrings() to print strings in lexicographical order;
        Node* node = root;
        string currString = "";
        set<string>* currentResults = new set<string>;
        set<Node*>* visited = new set<Node*>;
        return FindAllStrings(node, currString, currentResults, visited);
    }
// Get All locations in lexicographical order with their stringRef pointer
    vector<RefPair>* FindAllLocationsVerbose(){
        // Utility Func to call FindAllStrings() to print strings in lexicographical order;
        Node* node = root;
        string currString = "";
        vector<RefPair>* currentResults = new vector<RefPair>;
        set<Node*>* visited = new set<Node*>;
        return FindAllStringsVerbose(node, currString, currentResults, visited);
    }
// Get all the initial chars in the tree
    vector<char> FindAllStart(){
        vector<char> allFirst;       
        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (root->children[i] != nullptr){
                // if root child exists
                char c = IndexToChar(i);
                allFirst.push_back(c);
            }
        }
        return allFirst;
    }

};
#endif
