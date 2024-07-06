#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

#include "Enums.h"
#include "RoutePlannerUtils.h" // for enum2str

using namespace std;
using namespace RoutePlannerUtils;

//enum SettlementType{city, town, village};

struct Location{
    int x;
    int y;
    Location(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class Vertex{
private:
    int ID;
    string name;
    string friendName;
    Location* coordinates; 
    Vertex* parent;
    SettlementType settlement;
    vector<string> amenities;
public:
    Vertex(){};

    Vertex(int ID, string name, string friendName, int x, int y, SettlementType settlement){
        this->ID = ID;
        this->name = name;
        this->friendName = friendName;
        this->coordinates = new Location(x,y);
        this->settlement = settlement;
    }
//Basic Getter/Setter
    int GetID() const {
        return this->ID;
    }
    void SetID(int ID){
        this->ID = ID;
        return;
    }
    void SetName(string name){
        this->name = name;
        name[0] = toupper(name[0]);
        return;
    }
    string GetName(){
        return this->name;
    }
    SettlementType GetSettlement(){
        return this->settlement;
    }
    void SetSettlement(SettlementType settlement){
        this->settlement = settlement;
    }

    string GetFriend(){
        return this->friendName;
    }
    void SetFriend(string friendName){
        this->friendName = friendName;
    }
    Location* GetCoordinates(){
        return this->coordinates;
    }
    void SetX(int x){
        this->coordinates->x = x;
    }

    void SetY(int y){
        this->coordinates->y = y;
    }

    void SetCoordinates(int x, int y ){
        this->coordinates = new Location(x,y);
    }

    vector<string> GetAmenities(){
        return this->amenities;
    }

    void AddAmenities(string amenity){
        amenities.push_back(amenity);
    }
//Overloaded Operators for Comparison
    bool operator!=(const Vertex& rhd) const {
		if(ID != rhd.GetID()){
			return true;
		}else{
			return false;
		}
	};
	
    bool operator==(const Vertex& rhd)const {
		if(ID == rhd.GetID()){
			return true;
		}else{
			return false;
		}
	};

    void Display(){
        cout << this->name << " is a " << enum2Str(settlement) 
            << " located at the coordinates ( " << coordinates->x << "," << coordinates->y <<")."
            << "Your friend " << this->friendName << " lives here."<< endl;
        if (!amenities.empty()){
            cout << this->name << "'s amenities include: " << endl;
            for (auto amenity: amenities){
                cout << "\t " << amenity << endl;
            }
        }
    }
};
#endif