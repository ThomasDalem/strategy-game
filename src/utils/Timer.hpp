#ifndef TIMER_HPP
#define TIMER_HPP

#include <cstdint>

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    uint64_t getDeltaTime() const;

private:
    uint64_t _begin;
};

#endif // TIMER_HPP