//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_FABRIC_H
#define CPPEX2_FABRIC_H

#include "Item.h"

class Cloth: public Item
{
public:
    friend std::ostream &operator<<(std::ostream &os, const Item &other);

private:
    double _quantity;
    int _weight;

};


#endif //CPPEX2_FABRIC_H
