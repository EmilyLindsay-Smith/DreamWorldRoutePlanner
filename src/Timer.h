#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

using namespace std;

class Timer
{
private:
    string TimeName;
    std::chrono::high_resolution_clock::time_point start;
    chrono::duration<double> duration; 

public:
    Timer(string TimeName){
        this->TimeName = TimeName;
        //cout << "Starting " << TimeName << endl;
        start = chrono::high_resolution_clock::now();
    }
    void ReStart(){
        start = chrono::high_resolution_clock::now();
    }

    void End(){
        auto end = chrono::high_resolution_clock::now();
        duration = end - start;
    };

    void End_Verbose(){
        auto end = chrono::high_resolution_clock::now();
        duration = end - start;
        
        cout << TimeName << " Elapsed time: " << duration.count() << " seconds" << endl;
    };

    void PrintDuration(){
        cout << TimeName << ": \t " << duration.count() << endl;

    };

    auto Duration(){
        return duration.count();
    }

};
#endif