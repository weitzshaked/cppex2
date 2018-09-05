//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_IKEA_H
#define CPPEX2_IKEA_H

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Item.h"

class ikea
{
private:
    const std::string NOTFOUND = "Item not found";
    const std::string ITEMSINPUT = "Please enter number of items:";
    const std::string QUANTITYINPUT = "Please enter desired quantity:";
    std::vector<Item *> items;

    template<typename T>
    T &getInput();

public:
    /**
     * constructor
     */
    ikea() = default;

    /**
     * destructor
     */
    ~ikea()
    { delete[] items; };

    /**
     * inputs items to stock from file
     * @param path
     * @return
     */
    int inputStock();

    /**
     * finds item by id
     * @return
     */
    void findById();

    /**
     * find item by name
     * @return
     */
    void find_by_name();

    //todo const?
    /**
     * prints items by id
     * @param id
     */
    void printById();

    /**
     * prints items by name
     * @param name
     */
    void printByName();

    /**
     * sells a item
     * @return
     */
    int sell();

    void printMenu();

};

#endif //CPPEX2_IKEA_H
