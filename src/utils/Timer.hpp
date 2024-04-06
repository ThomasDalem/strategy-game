#ifndef TIMER_HPP
#define TIMER_HPP

#include <cstdint>

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    uint32_t getDeltaTime() const;

private:
    uint32_t _begin;
};

#endif // TIMER_HPP