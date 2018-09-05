//
// Created by weitz on 01/09/2018.
//

#include "Cloth.h"

friend std::ostream &operator<<(std::ostream &os, const Cloth &other)
{
    operator<<(os,other);
    os << "Weight: " << other._weight << std::endl;
    return os;
}
