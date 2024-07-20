#ifndef DATA_HPP
#define DATA_HPP

#include "HUD/Layer.hpp"
#include <type_traits>

// Singleton class containing essential game information
class Data
{
public:
    static Data &getInstance() {
        static Data instance;

        return instance;
    };
    Data(const Data &other) = delete;
    void operator=(const Data &other) = delete;

    int supplies;

private:
    Data();
};

#endif