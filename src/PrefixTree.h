#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#define ALPHABET_SIZE (26) // defined globally as used for both Node & Trie

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "Vertex.h"
#include "RoutePlannerUtils.h" // for charToIndex, IndexToChar

using namespace std;
using namespace RoutePlannerUtils;

// OPTIMISATION:
/*
    Current alphabet vector of children is inefficient - replace with e.g. map to avoid iterating over empty values?
        need to update in Node class and in every alphabet length for loop
*/


struct RefPair{
    // used in PrefixTree
    string queryString;
    Vertex* stringRef;
    RefPair(string x, Vertex* y){
        this->queryString = x;
        this->stringRef = y;
    }
// Overload operators - needed for e.g. set<RefPair>

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
                cout << char('a' + i) << "," << endl;
            }
        }
        cout << endl;
    };
};



//Time Complexity to Create: O(W*L): W = num words, L = average word length
//Time Complexity to Search: O(W*L): - perform L steps for W words?
// Hash insertion/lookup similar complexity but can't look up words by prefix


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

  
public:
    int numStrings;
    PrefixTree(){
        this->numStrings = 0;
        this->root = new Node();
    }
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

    void PrintSearchResults(vector<RefPair>* results){
        //Prints results from e.g. Search()
        if (results->empty()){
            cout << "No results found" << endl;
        }else if(static_cast<int>(results->size()) == 1){
            cout << "String found: " << (*results)[0].queryString << ":" << (*results)[0].stringRef << endl;
        }else{

            cout << static_cast<int>(results->size()) << " results found: " << endl;
            for (int i = 0; i < static_cast<int>(results->size()); i++){
                cout << "\t" <<  (*results)[i].queryString << ":" << (*results)[i].stringRef << endl;
            }
        }
        return;
    }

    void PrintLexiconResults(set<string>* results){
        //Prints results for FindAllStrings()
        if (results->empty()){
            cout << "No results found" << endl;
        }else{
            if(static_cast<int>(results->size()) != this->numStrings){
                throw runtime_error("Problem finding all strings in tree - incorrect number of strings returned");
            }
            cout << static_cast<int>(results->size()) << "/" << this->numStrings << " results found: " << endl;
            for (auto it = results->begin(); it != results->end(); it++){
                cout << "\t" << (*it) << endl;
            }
        }
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

    set<string>* FindAllLocations(){
        // Utility Func to call FindAllStrings() to print strings in lexicographical order;
        Node* node = root;
        string currString = "";
        set<string>* currentResults = new set<string>;
        set<Node*>* visited = new set<Node*>;
        return FindAllStrings(node, currString, currentResults, visited);
    }
    vector<RefPair>* FindAllLocationsVerbose(){
        // Utility Func to call FindAllStrings() to print strings in lexicographical order;
        Node* node = root;
        string currString = "";
        vector<RefPair>* currentResults = new vector<RefPair>;
        set<Node*>* visited = new set<Node*>;
        return FindAllStringsVerbose(node, currString, currentResults, visited);
    }
};

#endif
/*
int main(){
    Trie *t = new Trie();
    t->Insert("apple", 12);
    t->Insert("hello", 0);
    t->Insert("banana", 1);
    t->Insert("baloon", 9);
    t->Insert("baronness", 13);
    t->Insert("helping", 2);
    t->Insert("cello", 3);
    t->Insert("help", 4);
    t->Insert("helpful", 5);
    t->Insert("charming", 22);
    t->Insert("charles", 23);
    t->PrintSearchResults(t->Search("cello"));
    t->PrintSearchResults(t->Search("helo"));
    t->PrintSearchResults(t->Search("he"));
    t->PrintSearchResults(t->Search("char"));

    t->PrintLexiconResults(t->FindAllStrings());
    return 0;
}
*/