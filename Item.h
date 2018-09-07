//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_PRODUCT_H
#define CPPEX2_PRODUCT_H


#include <string>
#include <iostream>

using std::string;

/**
 * Class representing a product
 */

class Item
{
protected:
    int _id;
    string _name;
    double _quantity = 0;
    double _price;
    bool _quantityIsInt;

public:
    /**
     * @return quantity of item
     */
    double getQuantity() const;


    bool quantityIsInt() const;

    void setQuantity(double _quantity);

    int getId() const;

    const string &get_name() const;

    /**
     * constructor
     */
    Item(int id, string &name, double price, double quantity, bool isInt = true):
            _id(id), _name(name), _price(price),_quantity(quantity), _quantityIsInt(isInt){};

    /**
     * prints item
     */
    virtual void printItem() const;
};


#endif //CPPEX2_PRODUCT_H
