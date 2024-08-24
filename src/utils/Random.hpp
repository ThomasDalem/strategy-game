#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

inline std::random_device rd;
inline std::mt19937 gen(rd());

class RandomInt
{
public:
    RandomInt(int min = 0, int max = 10);
    ~RandomInt() = default;

    int generate();

private:
    std::uniform_int_distribution<> _distrib;
};

class RandomFloat
{
public:
    RandomFloat(float min = 0.f, float max = 10.f);
    ~RandomFloat() = default;

    float generate();

private:
    std::uniform_real_distribution<> _distrib;
};

#endif
