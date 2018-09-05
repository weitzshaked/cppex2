//
// Created by weitz on 01/09/2018.
//

#include "Item.h"

int Item::get_id() const
{
    return _id;
}

const std::string &Item::get_name() const
{
    return _name;
}

double Item::get_quantity() const
{
    return _quantity;
}

void Item::set_quantity(int _quantity)
{
    Item::_quantity = _quantity;
}

void Item::printItem()
{
    std::cout << "Item: " << _id << std::endl;
    std::cout << "Name: " << _name << std::endl;
    std::cout << "Quantity: ";
    std::cout << _quantityIsInt? (int)_quantity: _quantity;
    std::cout << std::endl;
    std::cout << "Price: " << _price << std::endl;
}
