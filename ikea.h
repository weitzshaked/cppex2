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
    /**
     * enum for initializing a new item
     */
    enum ItemType{ candy, fabric, kitchen, movieAndBook, tableAndChair};
    const string NOTFOUND = "Item not found";
    const string ITEMSINPUT = "Please enter number of items:";
    const string QUANTITYINPUT = "Please enter desired quantity:";
    const string BADFORMAT = "Bad file formmating";
    std::vector<Item *> items;
    std::vector<string> input;
    ItemType type;

    /**
     * checks if the description is by the correct format
     * @param desc
     * @param format
     * @return 0 on success, -1 otherwise
     */
    int checkFormat(string& desc, string& format) const;

    /**
     * gets the first 4 lines from input file
     * @param inFile
     * @return 0 on success, -1 otherwise
     */
    int getFirstLines(std::ifstream& inFile);

    /**
     * gets next lines for MovieOrBook
     * @param inFile
     */
    void inputMovieOrBook(std::ifstream& inFile);

    /**
     * gets next lines for Furniture
     * @param inFile
     */
    void inputFurniture(std::ifstream& inFile);

    int getInt();

    string getString();

    /**
     * checks if the next line is a correct separator
     * @param inFile
     */
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

    void addItem(bool isInt);
};

#endif //CPPEX2_IKEA_H
