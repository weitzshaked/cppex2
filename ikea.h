//
// Created by weitz on 01/09/2018.
//

#ifndef CPPEX2_IKEA_H
#define CPPEX2_IKEA_H

#include <vector>
#include <iostream>
#include "Item.h"

//todo magic number format?
const std::string menu = "1. Input stock from file\n2. Find item by catalog number\n3. Find item by name\n 4. Print stock by catalog number\n5. Print stock by name\n6. Sell item\n7. Exit\n";


class ikea
{
private:
    std::vector<Item *> items;
    template <typename T>
    T& get_input();

public:
    /**
     * constructor
     */
    ikea() = default;

    /**
     * destructor
     */
    ~ikea() {delete[] items; };

    /**
     * inputs items to stock from file
     * @param path
     * @return
     */
    int input_stock();

    /**
     * finds item by id
     * @return
     */
    void find_by_id();

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
    void print_by_id();

    /**
     * prints items by name
     * @param name
     */
    void print_by_name();

    /**
     * sells a item
     * @return
     */
    int sell();


};

#endif //CPPEX2_IKEA_H
