#include "Timer.h"

Timer::Timer(const string& funcion_name) : function_name{ funcion_name } {
    //The time when the object was created
    start_time = chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "The function " << function_name << " took " << duration << " microseconds." << endl;
}