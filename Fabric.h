//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_FABRIC_H
#define CPPEX2_FABRIC_H

#include "Item.h"

class Fabric: public Item
{
public:
    Fabric(int id, string &name, double price, double quantity, double weight):
            Item(id, name, price, false), _quantity(quantity),_weight(weight){};
    virtual void printItem(){Item::printItem(); std::cout << "Weight: " << _weight << std::endl;}

protected:
    double _weight;

};


#endif //CPPEX2_FABRIC_H