#ifndef TIMER_H
#define TIMER_H

#include<iostream>
#include<chrono>
#include<string>

using namespace std;

class Timer{
public:
    /*
    Whene initializing the timer object, a timer start until it
    gets destroyed and the time (period) is printed by the destrucotor
    automatically when the function ends.
    */
    Timer(const string& function_name); // constructor
    ~Timer(); // destructor

private:
    // the name of the function we want to calculate the time
    string function_name;

    // instance of time_point class provided by chrono library
    // uses the high resolution clock specialized for short periods
    // when creating the timer object, the start time is the time when it is created
    chrono::time_point<chrono::high_resolution_clock> start_time;

};

#endif