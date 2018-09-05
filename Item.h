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
protected:
    int _id;
    std::string _name;
    virtual int _quantity;
    double _price;
public:
    int get_quantity() const;

    void set_quantity(int _quantity);

    int get_id() const;

    const std::string &get_name() const;

    /**
     * default constructor
     */
    virtual Item() = 0;

    /**
     * << operator, streams product into ostream
     * @param os
     * @param other
     * @return
     */
    virtual friend std::ostream &operator<<(std::ostream &os, const Item &other);
};


#endif //CPPEX2_PRODUCT_H
