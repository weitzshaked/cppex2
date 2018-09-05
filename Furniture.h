//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_FURNITURE_H
#define CPPEX2_FURNITURE_H


#include "Item.h"

class Furniture : public Item
{
public:
    Furniture(int id, string &name, double price, double quantity, double x, double y,
                      double z) :
            Item(id, name, price,quantity), _dimensions{x, y, z}
    {};

    virtual void printItem()
    {
        Item::printItem();
        std::cout << "Dimensions: " << _dimensions[0] << " " << _dimensions[1] << " "
                  << _dimensions[2] << std::endl;
    }

protected:
    double _dimensions[3];

};


#endif //CPPEX2_FURNITURE_H
