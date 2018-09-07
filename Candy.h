//
// Created by shaked.weitz on 9/5/18.
//

#ifndef CPPEX2_CANDY_H
#define CPPEX2_CANDY_H

#include "Item.h"

class Candy: public Item
{
public:
    /**
     * constructor
     * @param id
     * @param name
     * @param price
     * @param quantity
     * @param calories
     */
    Candy(int id, std::string &name, double price,double quantity, double calories):
            Item(id, name, price, quantity, false),_calories(calories){};

    /**
     * prints the item
     */
    void printItem() const override
    {
        Item::printItem();
        std::cout << "Calories: " << _calories << std::endl;
        std::cout << "-----" << std::endl;
    }
protected:
    double _calories;
};
#endif //CPPEX2_CANDY_H
