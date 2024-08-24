#include "Random.hpp"

// INT
RandomInt::RandomInt(int min, int max) : _distrib(min, max)
{}

int RandomInt::generate()
{
    return _distrib(gen);
}

// FLOAT
RandomFloat::RandomFloat(float min, float max) : _distrib(min, max)
{}

float RandomFloat::generate()
{
    return _distrib(gen);
}
