//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_KITCHENUTENSILS_H
#define CPPEX2_KITCHENUTENSILS_H


#include "Item.h"
#include "Furniture.h"

class Kitchenware : public Furniture
{
public:
    /**
     * constructor
     * @param id
     * @param name
     * @param price
     * @param quantity
     * @param x
     * @param y
     * @param z
     * @param capacity
     */
    Kitchenware(int id, string &name, double price, double quantity, double x, double y, double z,
                double capacity) : Furniture(id, name, price, quantity, x, y, x),
                                   _capacity(capacity)
    {};

    /**
     * prints the item
     */
    void printItem() const override
    {
        Furniture::printItem();
        std::cout << "Capacity: " << _capacity << std::endl;
        std::cout << "-----" << std::endl;
    }

protected:
    double _capacity;

};


#endif //CPPEX2_KITCHENUTENSILS_H
