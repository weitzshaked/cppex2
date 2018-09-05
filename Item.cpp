//
// Created by weitz on 01/09/2018.
//

#include "Item.h"

std::ostream &operator<<(std::ostream &os, const Item &other)
{
    os << "Item: " << other._id << std::endl;
    os << "Name: " << other._name << std::endl;
    os << "Quantity: " << other._quantity << std::endl;
    os << "Price: " << other._price << std::endl;
    return os;
}

int Item::get_id() const
{
    return _id;
}

const std::string &Item::get_name() const
{
    return _name;
}

int Item::get_quantity() const
{
    return _quantity;
}

void Item::set_quantity(int _quantity)
{
    Item::_quantity = _quantity;
}
