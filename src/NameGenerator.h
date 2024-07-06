#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H

#include <iostream>
#include <string>
#include <vector>

#include "RoutePlannerUtils.h" // for GetRandomNumber

using namespace std;
using namespace RoutePlannerUtils;

class NameGenerator
{
private: //45 vowels, 11 onsets, 49 codas, 5 syl types
    vector<string> onset = {"b", "d", "g", "p", "t" , "k" , "f", "s", "sh", "z", "ch", "l", "m", "n", "r"};
    vector<string> complexOnset = {"br", "dr", "gr", "pr", "tr" , "kr" , "fr", "shr",  
                            "bl", "gl", "pl", "kl" , "fl", "sl", 
                            "sp", "st" , "sk" ,  "sl", "sm", "sn", "sw", 
                             "spr", "str" , "skr"};
    vector<string> vowel = {"a", "e", "i", "o", "u"};
    vector<string> longVowel = {"ai", "ei", "oi", "oo"};
    vector<string> coda = {"b", "d", "g", "p", "t" , "k" , "f", "s", "sh", "z", "ch", "l", "m", "n", "r"};
    vector<string> complexCoda = {"rb", "rd", "rg", "rp", "rt" , "rk" , "rf", "rs", "rl", "rm", "rn",
                            "lb", "ld", "lg", "lp", "lt" , "lk" , "lf", "lm", 
                            "sp", "st" , "sk"};
    vector<string> syllableType = {"ovc", "Ovc", "OvC", "OVc", "oVc", "OVc",
                                    //"ovcovc", "ovcOvc", "ovcOvC", "ovcOVc", "ovcoVc", "ovcOVc",
                                    "ovovc", "ovOvc", "ovov", "Ovov", "OvOv", "ovOv",
                                    "oVovc", "oVOvc", "oVov", "OVov", "OVOv", "oVOv",
                                    "oVoV", "OVoV", "OVOV", "oVOV",
                                    "ovOV", "OvoV", "OvOV", "ovOV", 
                                    //"ovOvC", 
                                    //"ovOVc", "ovoVc", "ovOVc",
                                    "oVovc", "oVOvc",
                                    // "oVOvC", "oVOVc", "oVoVc", "oVOVc"};
                                   // "Ovcovc", "OvcOvc", "OvcOvC", "OvcOVc", "OvcoVc", "OvcOVc"
                                   };
    vector<string> firstnameSuffix = {"a", "o", "ia", "iyya", "ius", "anne", "inna", "ita", "ix", "enne", "essa", "ette", "een", "y", "an", "ah", "as", "is", "us", "er", "opher", "ifor", "id", "athon", "alyn", "ian", "en"};
    vector<string> surnameSuffix = {"smith", "er", "maker", "wright", "kins", "kinson", "ard", "erd", "man", "son", "ley", "ly", "by"};
    vector<string> countySuffix = {"shire", "land", "hamshire", "ington", "folk", "sex"};
    vector<string> villageSuffix = {"by", "ford", "beck", "burn", "combe", "cot", "croft", "den", "don", "ey", "field", "keth", "ley", "lip", "shaw", "shep", "thorpe", "thwaite", "toft", "wold", 
                                    "stead", "ham", "ton", "worth", "berry", "dale", "fold", "gate", "garth", "glen", "hithe", "holm", "hirst", "hurst", "ing", "inge", "law", "low", "ridge", "stow", "stowe", "wick", "way", "side" };
    vector<string> townSuffix = {"", "borough", "bury", "cester", "ford", "mouth", "beck", "bourne", "burn", "caster", "cester", "combe", "mere", "minster", "more", "ness", "pool", "ster", "thorpe", "thwaite", "wall", "weald", "wold",
                                    "stead", "ham", "ton", "worth", "berry", "dale", "fold", "gate", "garth", "glen", "hithe", "holm", "hirst", "hurst", "ing", "inge", "law", "low", "ridge", "stow", "stowe", "wick", "way", "side"};
    vector<string> citySuffix = {"", "burgh", "berg", "mouth", "bourne", "caster", "cester", "folk", "mere", "minster", "more", "ness", "pool", "port", "ster",
                                    "stead", "ham", "ton", "worth", "berry", "dale", "fold", "gate", "garth", "glen", "hithe", "holm", "hirst", "hurst", "ing", "inge", "law", "low", "ridge", "stow", "stowe", "wick", "way", "side"};

public:
    NameGenerator(){
    };

    int GetVowelLength(){
        return static_cast<int>(this->vowel.size());
    }
    int GetOnsetLength(){
        return static_cast<int>(this->onset.size());
    }
    int GetCodaLength(){
        return static_cast<int>(this->coda.size());
    }
    int GetLongVowelLength(){
        return static_cast<int>(this->longVowel.size());
    }
    int GetComplexOnsetLength(){
        return static_cast<int>(this->complexOnset.size());
    }
    int GetComplexCodaLength(){
        return static_cast<int>(this->complexCoda.size());
    }
    int GetSyllableTypeLength(){
        return static_cast<int>(this->syllableType.size());
    }
    int GetSurnameSuffixLength(){
        return static_cast<int>(this->surnameSuffix.size());
    }
    int GetFirstnameSuffixLength(){
        return static_cast<int>(this->firstnameSuffix.size());
    }
    int GetCountySuffixLength(){
        return static_cast<int>(this->countySuffix.size());
    }  
    int GetVillageSuffixLength(){
        return static_cast<int>(this->villageSuffix.size());
    }
    int GetTownSuffixLength(){
        return static_cast<int>(this->townSuffix.size());
    }
    int GetCitySuffixLength(){
        return static_cast<int>(this->citySuffix.size());
    }
    string GetOnset(){
        return this->onset[GetRandomNumber(GetOnsetLength())];
    };
    string GetVowel(){
        return this->vowel[GetRandomNumber(GetVowelLength())];
        };
    string GetCoda(){
        return this->coda[GetRandomNumber(GetCodaLength())];
        };

    string GetComplexOnset(){
        return this->complexOnset[GetRandomNumber(GetComplexOnsetLength())];
    };
    string GetLongVowel(){
        return this->longVowel[GetRandomNumber(GetLongVowelLength())];
        };
    string GetComplexCoda(){
        return this->complexCoda[GetRandomNumber(GetComplexCodaLength())];
        };    

    string GetSyllable(){
        string output =  this->syllableType[GetRandomNumber(GetSyllableTypeLength())];
        return output;
        };

    string GetSuffix(string suffixType){
        string output;
        if (suffixType == "surname"){
            output = this->surnameSuffix[GetRandomNumber(GetSurnameSuffixLength())];
        }else if (suffixType == "firstname"){
             output = this->firstnameSuffix[GetRandomNumber(GetFirstnameSuffixLength())];  
        }else if (suffixType == "county"){
            output = this->countySuffix[GetRandomNumber(GetCountySuffixLength())];
        }else if (suffixType == "village"){
            output = this->villageSuffix[GetRandomNumber(GetCountySuffixLength())];
        }else if (suffixType == "town"){
            output = this->townSuffix[GetRandomNumber(GetTownSuffixLength())];
        }else if (suffixType == "city"){
            output = this->citySuffix[GetRandomNumber(GetCitySuffixLength())];
        }else{
            output = "";
        };
        return output;
    }
    string GetName(string suffixType){
        string wordStructure = GetSyllable();
        string newName;

         for (int i = 0; i < wordStructure.length(); i++){
            if (wordStructure[i] == 'o'){
                newName += GetOnset();
            }else if (wordStructure[i] == 'O'){
                newName += GetComplexOnset();
            }else if (wordStructure[i] == 'v'){
                newName += GetVowel();
            }else if (wordStructure[i] == 'V'){
                newName += GetLongVowel();
            }else if (wordStructure[i] == 'c'){
                newName += GetCoda();
            }else if (wordStructure[i] == 'C'){
                newName += GetComplexCoda();
            }
        }
        newName += GetSuffix(suffixType);
        newName[0] = toupper(newName[0]);
        return newName;
    };

};
#endif

/*
int main(){
    NameGenerator* namer = new NameGenerator();
    int SIZE = 15;
    vector<string> suffixes = {"surname", "county", "village", "town", "city", "potato"};
    for (int i = 0; i < SIZE; i++){
        string suffixType = suffixes[GetRandomNumber(suffixes.size())];
        cout << "Name for " << suffixType << " : " << namer->GetName(suffixType) << endl;
    }
// PAUSE FUNC
    
    bool boolean;
    boolean = true;

    if (boolean == true) {
        cout << "Press any key to exit" << endl;
        cin >> boolean; 
    }


    return 0;
};
*/