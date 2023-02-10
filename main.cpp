#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <chrono>

#include "Timer.h"


int main(){
    std::random_device r;
    std::mt19937_64 mt(r());
    std::uniform_int_distribution dist(1, 100);

    std::vector<int> vector1;
    std::list<int> list1;
    Timer<std::chrono::microseconds> T_list(false);
    Timer<std::chrono::microseconds> T_vector(true);
    {
        std::cout << "Filling vector: "; 
        Timer<std::chrono::microseconds> T1(true);
        for(auto i = 0; i < 1'000'000; i++){
            vector1.push_back(dist(mt));
        }
    }
    T_list.Start();
    T_vector.Pause();
    {
        std::cout << "Filling list: ";
        Timer<std::chrono::microseconds> T1(true);
        for(auto i = 0; i < 1'000'000; i++){
            list1.push_back(dist(mt));
        }
    }
    {
        std::cout << "Sort list: ";
        Timer<std::chrono::microseconds> T1(true);
        list1.sort();
    }
    T_list.Pause();
    T_vector.Continue();
    {
        std::cout << "Sort vector: ";
        Timer<std::chrono::microseconds> T1(true);
        std::sort(vector1.begin(), vector1.end());
    }

    return 0;
}