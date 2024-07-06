#ifndef ROUTEPLANNERUTILS_H
#define ROUTEPLANNERUTILS_H


#include <regex>
#include <random>

#include "Vertex.h"

#include "Enums.h"

using namespace std;

#include <iostream>

namespace RoutePlannerUtils{

    int GetRandomNumber(int upper) {
        //from C++11 - more reliable than the older C-style srand() function: 
        static random_device rd;  // obtain a random seed from the hardware
        static mt19937 eng(rd()); // Standard Mersenne Twister engine seeded with rd()
        uniform_int_distribution<int> distribution(0, upper-1); // distribution from lower to upper bound that are passed in

        int randomNumber = distribution(eng);// generate random number
    return randomNumber;
}

    string MinToHour(float minutes){
        int hours = static_cast<int>(round(minutes/60)); 
        float mins = static_cast<int>(round(fmod(minutes,60)));
        string time = to_string(hours) + " hours " + to_string(minutes) + "minutes";
        return time;
    }

    int CharToIndex(char c){
        return (c - 'a');
    }

    char IndexToChar(int i){
        return ('a' + i);
    }

    string enum2Str(SettlementType sett){
        switch(sett){
            case city : return "citadel"; //"city";
            case town : return "town";
            case village : return "hamlet"; //"village";
            default: return "settlement";
        }
    }

    bool ContainsNonAlpha(string name){
        return !std::regex_match(name, std::regex("^[A-Za-z]+$"));
    }

    string MakeLowerCase(string str){
        for (auto& elem: str){
            elem = tolower(elem);
        }
        return str;
    }
};

#endif 