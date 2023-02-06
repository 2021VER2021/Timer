#include <iostream>
#include <math.h>
#include <chrono>

/// @brief 
/// It is the Timer class, allow's you to measure time your code runs
/// @tparam TimeType - time unit of mesurement
template <typename TimeType>
class Timer{
public:
    Timer():Timer(false){}

    Timer(bool is_starting){
        if (is_starting){
            Start();
        }
        else{
            Start();
            current_condition = false;
        }
        duration = duration.zero();
    }

    ~Timer(){}

    /// @brief use this method to Start the timer
    void Start(){
        start = std::chrono::steady_clock::now();
        current_condition = true;
        duration = duration.zero();
    }

    /// @brief use this method to show the current time on a timer, without interupting it
    void Loop(){
        if (current_condition){
            duration += std::chrono::steady_clock::now() - start;
            start = std::chrono::steady_clock::now();
        } 
        std::cout << std::chrono::duration_cast<TimeType>(duration).count() << std::endl;
    }

    /// @brief use this method to stop the timer and show the current time on a timer
    void Stop(){
        Loop();
        current_condition = false;
        duration = duration.zero();
    }

    /// @brief use this method to pause the timer, it will remember previous duration
    void Pause(){
        duration += std::chrono::steady_clock::now() - start;
        current_condition = false;
    }

    /// @brief use this method to continue timer after pausing it, or to start the timer, if it was stopped
    void Continue(){
        start = std::chrono::steady_clock::now();
        current_condition = true;
    }

private:
    bool current_condition;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::duration duration;
};

int main(){
    double sum = 0;
    Timer<std::chrono::microseconds> T;
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Stop();
    T.Start();
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Loop();
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Stop();
    T.Start();
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Loop();
    T.Pause();
    T.Loop();
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Loop();
    T.Continue();
    T.Loop();
    T.Start();
    T.Pause();
    for (int i = 0; i < 1'000'000; i++){
        sum += std::sin(i) + std::cos(i);
    }
    T.Stop();
}