//
// Created by weitz on 03/09/2018.
//

#ifndef CPPEX2_MOVIESANDBOOKS_H
#define CPPEX2_MOVIESANDBOOKS_H

#include "Item.h"

class MoviesAndBooks : public Item
{
public:
    /**
     * constructor
     * @param id
     * @param name
     * @param price
     * @param quantity
     * @param author
     * @param year
     * @param length
     */
    MoviesAndBooks(int id, string &name, double price, double quantity, string& author, string& year,
                   string& length) :
            Item(id, name, price,quantity), _author(author), _yearOfPublish(year),
            _length(length)
    {};

    /**
     * prints the item
     */
    void printItem() const override
    {
        Item::printItem();
        std::cout << "Author: " << _author << std::endl;
        std::cout << "Year of publication: " << _yearOfPublish << std::endl;
        std::cout << "Length: " << _length << std::endl;
        std::cout << "-----" << std::endl;
    }

protected:
    string _author;
    string _yearOfPublish;
    string _length;
};


#endif //CPPEX2_MOVIESANDBOOKS_H
