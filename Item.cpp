//
// Created by weitz on 01/09/2018.
//

#include <iomanip>
#include "Item.h"


/**
 * @return id of item
 */
int Item::getId() const
{
	return _id;
}


/**
 * @return name of item
 */
const std::string &Item::get_name() const
{
	return _name;
}

/**
 * set quantity to param
 * @param quantity
 */
void Item::setQuantity(double quantity)
{
	_quantity = quantity;
}

/**
 * prints item
 */
void Item::printItem() const
{
	std::cout << "Item: " << _id << std::endl;
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Quantity: ";
	if (_quantityIsInt)
	{
		std::cout << std::fixed << std::setprecision(2) << _quantity << std::endl;
	}
	else
	{
		std::cout <<(int) _quantity << std::endl;
	}
	std::cout << "Price: " << _price << std::endl;
}


/**
 * @return true if is int, false if double
 */
bool Item::quantityIsInt() const
{
	return _quantityIsInt;
}

/**
 * @return quantity of item
 */
double Item::getQuantity() const
{
	return _quantity;
}
