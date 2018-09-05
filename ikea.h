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

using std::string;

class ikea
{
private:
    enum ItemType{ candy, fabric, kitchen, movieAndBook, tableAndChair};
    const string NOTFOUND = "Item not found";
    const string ITEMSINPUT = "Please enter number of items:";
    const string QUANTITYINPUT = "Please enter desired quantity:";
    const string BADFORMAT = "Bad file formmating";
    std::vector<Item *> items;
    std::vector<string> input;
    ItemType type;

    int checkFormat(string desc, string format);
    int getFirstLines(std::ifstream& inFile);
    void inputMovieOrBook(std::ifstream& inFile);
    void inputFurniture(std::ifstream& inFile);
    int getInt();
    string getString();
    void checkSeparator(std::ifstream& inFile);

public:
    /**
     * constructor
     */
    ikea() = default;

    /**
     * destructor
     */
    ~ikea()
    {for(auto &item: items){delete item;}};

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
    Item & findById();

    /**
     * find item by name
     * @return
     */
    void find_by_name();

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

    int addItem(bool isInt);
};

#endif //CPPEX2_IKEA_H
