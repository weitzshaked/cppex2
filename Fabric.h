//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_FABRIC_H
#define CPPEX2_FABRIC_H

#include "Item.h"

class Fabric : public Item
{
public:
    /**
     * constructor
     * @param id
     * @param name
     * @param price
     * @param quantity
     * @param weight
     */
    Fabric(int id, string &name, double price, double quantity, double weight) :
            Item(id, name, price, quantity, false), _weight(weight)
    {};

    /**
     * prints the item
     */
    void printItem() const override
    {
        Item::printItem();
        std::cout << "Weight: " << _weight << std::endl;
        std::cout << "-----" << std::endl;
    }

protected:
    double _weight;

};


#endif //CPPEX2_FABRIC_H
