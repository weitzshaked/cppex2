//
// Created by weitz on 03/09/2018.
//

#ifndef CPPEX2_MOVIESANDBOOKS_H
#define CPPEX2_MOVIESANDBOOKS_H

#include "Item.h"

class MoviesAndBooks : public Item
{
public:
    MoviesAndBooks(int id, string &name, double price, double quantity, string author, string year,
                   string length) :
            Item(id, name, price), _quantity(quantity), _author(author), _yearOfPublish(year),
            _length(length)
    {};

    virtual void printItem()
    {
        Item::printItem();
        std::cout << "Author: " << _author << std::endl;
        std::cout << "Year of publication: " << _yearOfPublish << std::endl;
        std::cout << "Length: " << _author << std::endl;
    }

protected:
    string _author;
    string _yearOfPublish;
    string _length;
};


#endif //CPPEX2_MOVIESANDBOOKS_H
