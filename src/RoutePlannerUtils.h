#ifndef ROUTEPLANNERUTILS_H
#define ROUTEPLANNERUTILS_H

#include <regex>
#include <random>

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
        if (minutes <= 0){
            return "0 hours 0 minutes";
        }
        int hours = static_cast<int>(floor(minutes/60)); 
        int mins = static_cast<int>(round(fmod(minutes,60)));
        string time = to_string(hours) + " hour" + (hours==1? "" : "s") + " " + to_string(mins) + " minutes";
        return time;
    }

    int CharToIndex(char c){
        int result = c - 'a';
        if (result < 0){
            result += 32;
        }
        return result;
    }

    char IndexToChar(int i){
        if (i > 25){
            throw runtime_error("Index cannot map to char");
        }
        return ('a' + i);
    }

    string enum2Str(SettlementType sett){
        switch(sett){
            case placeBig : return "citadel"; //"city";
            case placeMedium : return "town";
            case placeSmall : return "hamlet"; //"village";
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

    string MakeSentenceCase(string str){
        str[0] = toupper(str[0]);
        return str;
    }
};

#endif 