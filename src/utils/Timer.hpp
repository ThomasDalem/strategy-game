#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    // Get elapsed time in seconds
    float getDeltaTime() const;

private:
    std::chrono::steady_clock::time_point _begin;
};

#endif // TIMER_HPP