#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

#include <vector>
#include "entt.hpp"

struct Parent
{ 
    entt::entity parent {entt::null};
};

struct Children
{
    std::vector<entt::entity> children;
};

#endif // RELATIONSHIP_HPP