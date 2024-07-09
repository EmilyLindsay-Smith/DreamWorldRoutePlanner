#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

#include "Enums.h"
#include "RoutePlannerUtils.h" // for enum2str

using namespace std;
using namespace RoutePlannerUtils;

struct Location{
    int x;
    int y;
    Location(){};
    Location(int x, int y){
        this->x = x;
        this->y = y;
    }

};

class Vertex{
private:
    int ID = -1;
    string name = "";
    string friendName = "";
    string friendSurname = "";
    Location* coordinates = new Location(); 
    SettlementType settlement;
    vector<string>* amenities = new vector<string>;
public:
    Vertex(){};
    ~Vertex(){
        delete coordinates;
        amenities->clear();
        delete amenities;
    }

    Vertex(int ID, string name, string friendName, int x, int y, SettlementType settlement){
        if (ID >=0){
            this->ID = ID;
        }
        
        if (!ContainsNonAlpha(name)){
            name = MakeSentenceCase(name);
            this->name = name;
        }
        if (!ContainsNonAlpha(friendName)){
            this->friendName = friendName;
        }
        if (x >=0 && y >= 0){
            this->coordinates = new Location(x,y);
        }
        this->settlement = settlement;
    }
//Basic Getter/Setter
    int GetID() const {
        return this->ID;
    }

    void SetID(int ID){
        if (ID >=0){
            this->ID = ID;
        }
        return;
    }
    void SetName(string name){
        if (!ContainsNonAlpha(name)){
            name = MakeSentenceCase(name);
            this->name = name;
        }
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
        return;
    }

    string GetFriend(){
        return this->friendName;
    }
    void SetFriend(string friendName){
        if (!ContainsNonAlpha(friendName)){
            this->friendName = friendName;
        }
        return;
    }

    string GetFriendSurname(){
        return this->friendSurname;
    }
    void SetFriendSurname(string friendName){
        if (!ContainsNonAlpha(friendName)){
            this->friendSurname = friendName;
        }
        return;
    }

    Location* GetCoordinates(){
        return this->coordinates;
    }
    void SetX(int x){
        if (x >=0){
            this->coordinates->x = x;
        }
        return;
    }

    void SetY(int y){
        if (y >=0){         
            this->coordinates->y = y;
        }
        return;
    }

    void SetCoordinates(int x, int y ){
        if (x >=0 && y >= 0){
            this->coordinates = new Location(x,y);
        }
        return;
    }

    vector<string>* GetAmenities(){
        return this->amenities;
    }

    void AddAmenities(string amenity){
        if (!ContainsNonAlpha(amenity)){
            amenities->push_back(amenity);
        }
        return;
    }

    bool AllSet(){
        // Checks ID, Name, SettlementType, Coordinates and Amenities set
        if (GetID() == -1){
            cout << "ID not set" << endl;
            return false;
        }
        if (GetName() == ""){
            cout << "name not set" << endl;
            return false;
        }
        if (GetSettlement() <0 || GetSettlement() >3){
            cout << "stype not set" << endl;
            return false;
        }
        if (GetCoordinates()->x <0 || GetCoordinates()->x > 100){
            cout << "x not set" << endl;
            return false;
        }
        if (GetCoordinates()->y <0 || GetCoordinates()->y > 100){
            cout << "y not set" << endl;
            return false;
        }
        if (amenities->size() == 0){
            cout << "amenities not set" << endl;
            return false;
        }
        return true;
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
            << " located at the coordinates (" << coordinates->x << "," << coordinates->y <<")."
            << " Your friend " << this->friendName << (this->friendSurname != "" ? " " : "" )<< this->friendSurname << " lives here."<< endl;
        if (!amenities->empty()){
            cout << this->name << "'s amenities include: " << endl;
            vector<string>::iterator it = amenities->begin();
            for (it; it < amenities->end(); it++){
                cout << "\t " << *it << endl;
            }
        }
    }
};
#endif