//
// Created by weitz on 01/09/2018.
//

#include "Item.h"

int Item::getId() const
{
    return _id;
}

const std::string &Item::get_name() const
{
    return _name;
}

void Item::setQuantity(double _quantity)
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

bool Item::quantityIsInt() const
{
    return _quantityIsInt;
}

double Item::getQuantity() const
{
    return _quantity;
}
