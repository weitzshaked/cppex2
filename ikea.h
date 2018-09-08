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

    std::vector<Item *> items;
    std::vector<string> input;
    ItemType type;

    /**
     * checks if the description is by the correct format
     * @param desc
     * @param format
     * @return 0 on success, -1 otherwise
     */
    int checkFormat(string& desc,const string& format) const;

    /**
     * gets the first 4 lines from input file
     * @param inFile
     * @return 0 on success, -1 otherwise
     */
    void getFirstLines(std::ifstream &inFile);

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
    const string ENTER_NUMBER = "please enter catalog number: ";
    const string ENTER_NAME = "please enter product name: ";
    const string ENTER_PATH = "please enter file path: ";
    const string ENTER_ITTEM = "Please enter number of items:";
    const string ENTER_QUANTITY = "Please enter desired quantity:";
    const string NOT_FOUND = "Item not found";
    const string BAD_FORMAT = "Bad file formmating";
    const string MISSING_SEPERATOR = "Separator Missing";
    const string SEPERATOR = "-----";
    const string INVALID_INPUT = "Invalid input";
    const string PUBLISH_YEAR = "Year of publication";
    const string LENGTH = "Length";
    const string OPEN_ERROR = "Failed to open file";
    const string SELL_ERROR = "Not enough stock to sell";
    const string ITEM_ERROR = "Item ID already exists";

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
    void inputStock();

    /**
     * finds item by id from user input
     * @return
     */
    Item* findById(bool printItem);

    /**
     * find item by name from user input
     * @return
     */
    void findByName();

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
    void sell();

    void printMenu();

    void addItem(bool isInt);

    const string & findNameById(int id);

    /**
 * gets an item by id given
 * @param id
 * @return
 */
    Item& getById(int id);
};

#endif //CPPEX2_IKEA_H
