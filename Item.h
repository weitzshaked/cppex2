//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_PRODUCT_H
#define CPPEX2_PRODUCT_H


#include <string>
#include <iostream>

/**
 * Class representing a product
 */
class Item
{
    using std::string;

protected:
    int _id;
    string _name;
    double _quantity = 0;
    double _price;
    bool _quantityIsInt;

public:
    double get_quantity() const;

    void set_quantity(int _quantity);

    int get_id() const;

    const string &get_name() const;

    /**
     * constructor
     */
    virtual Item(int id, string &name, double price, bool isInt = true):
            _id(id), _name(name), _price(price), _quantityIsInt(isInt){};

    virtual void printItem();
};


#endif //CPPEX2_PRODUCT_H
