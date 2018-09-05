//
// Created by shaked.weitz on 9/5/18.
//

#ifndef CPPEX2_CANDY_H
#define CPPEX2_CANDY_H

#include "Item.h"

class Candy: public Item
{
public:
    Candy(int id, std::string &name, double price,double quantity, double calories):
            Item(id, name, price, false),_quantity(quantity),_calories(calories){};
    virtual void printItem()
    {
        Item::printItem();
        std::cout << "Calories: " << _calories << std::endl;
    }
protected:
    double _calories;
};
#endif //CPPEX2_CANDY_H
