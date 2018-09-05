#include <sstream>
#include <cstring>
#include "ikea.h"
#include "Fabric.h"
#include "Candy.h"
#include "Kitchenware.h"
#include "MoviesAndBooks.h"
#include "TablesAndChairs.h"


int main()
{
    auto *catalog = new ikea();
    int choice = 0;
    while (choice != 7)
    {
        catalog->printMenu();
        std::cin >> choice;
        switch (choice)
        {
            case 1:
                if (!catalog->inputStock())
                {
                    delete catalog;
                    return -1;
                }
                break;
            case 2:
                catalog->findById();
                break;
            case 3:
                catalog->find_by_name();
                break;
            case 4:
                catalog->printById();
                break;
            case 5:
                catalog->printByName();
                break;
            case 6:
                if (!catalog->sell())
                {
                    delete catalog;
                    return -1;
                }
                break;
            default:
                break;
        }
    }
    delete catalog;
    return 0;
}

void ikea::checkSeparator(std::ifstream& inFile)
{
    string line;
    getline(inFile, line);
    if(line != "-----")
    {
        std::cerr << "Separator Missing" << std::endl;
    }
}

void ikea::printMenu()
{
    std::cout << "1. Input stock from file" << std::endl;
    std::cout << "2. Find item by catalog number" << std::endl;
    std::cout << "3. Find item by name" << std::endl;
    std::cout << "4. Print stock by catalog number" << std::endl;
    std::cout << "5. Print stock by name" << std::endl;
    std::cout << "6. Sell item" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

int ikea::addItem(bool isInt)
{
    int id = 0;
    string name;
    double quantity = 0;
    double price = 0;
    try
    {
        id = std::stoi(input[0]);
        name = input[1];
        if (isInt)
        {
            quantity = std::stoi(input[2]);
        }
        else
        {
            quantity = std::stod(input[2]);
        }
        price = std::stod(input[3]);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid input" << e.what() << std::endl;
    }
    switch (type)
    {
        //todo special cases
        case candy:
            items.push_back(new Candy(id, name, price, quantity, std::stod(input[4])));
            return 0;
        case fabric:
            items.push_back(new Fabric(id, name, price, quantity, std::stod(input[4])));
            return 0;
        case kitchen:
            items.push_back(new Kitchenware(id, name, price, quantity, std::stod(input[4]),
                                            std::stod(input[5]), std::stod(input[6]),
                                            std::stod(input[7])));
            return 0;
        case movieAndBook:
            items.push_back(
                    new MoviesAndBooks(id, name, price, quantity, input[4], input[5], input[6]));
            return 0;
        case tableAndChair:
            items.push_back(new TablesAndChairs(id, name, price, quantity, std::stod(input[4]),
                                                std::stod(input[5]), std::stod(input[6]), input[7],
                                                input[8]));
            return 0;
        default:
            break;
    }
}

void ikea::inputMovieOrBook(std::ifstream& inFile)
{
    string line;
    string inputString;
    for (int i = 5; i < 7; i++)
    {
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> inputString;
        switch (i)
        {
            case 5:
                if (!checkFormat(inputString, "Year of publication:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            case 6:
                if (!checkFormat(inputString, "Length:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            default:
                break;
        }
    }
    type = movieAndBook;
}


void ikea::inputFurniture(std::ifstream& inFile)
{
    string line;
    string inputString;
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> inputString;

    if (!checkFormat(inputString, "Capacity:"))
    {
        iss >> inputString;
        input.push_back(inputString);
        type = kitchen;
    }
    else if (checkFormat(inputString, "Material:"))
    {
        iss >> inputString;
        input.push_back(inputString);
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> inputString;
        if (checkFormat(inputString, "Color:"))
        {
            iss >> inputString;
            input.push_back(inputString);
        }
        type = tableAndChair;
    }
}

int ikea::inputStock()
{
    string path;
    std::cin >> path;

    std::ifstream inFile(path);

    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    getFirstLines(inFile);

    string line;
    string inputString;
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> inputString;
    if (inputString == "Weight:")
    {
        iss >> inputString;
        input.push_back(inputString);
        type = fabric;
        checkSeparator(inFile);
        addItem(false);
    }
    else if (inputString == "Calories:")
    {
        iss >> inputString;
        input.push_back(inputString);
        type = candy;
        checkSeparator(inFile);
        addItem(false);
    }
    else if (inputString == "Author:")
    {
        iss >> inputString;
        input.push_back(inputString);
        inputMovieOrBook(inFile);
        checkSeparator(inFile);
        addItem(true);
    }
    else if (inputString == "Dimensions:")
    {
        string temp1, temp2;
        iss >> inputString >> temp1 >> temp2;
        input.push_back(inputString);
        input.push_back(temp1);
        input.push_back(temp2);
        inputFurniture(inFile);
        checkSeparator(inFile);
        addItem(true);
    }
    inFile.close();
    return 0;
}


int ikea::checkFormat(string desc, string format)
{
    if (desc != format)
    {
        std::cerr << BADFORMAT << std::endl;
        return -1;
    }
    return 0;
}


int ikea::getFirstLines(std::ifstream &inFile)
{
    string line;
    string inputString;
    for (int i = 0; i < 4; i++)
    {
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> inputString;
        switch (i)
        {
            case 0:
                if (!checkFormat(inputString, "Item:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            case 1:
                if (!checkFormat(inputString, "Name:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            case 2:
                if (!checkFormat(inputString, "Quantity:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            case 3:
                if (!checkFormat(inputString, "Price:"))
                {
                    iss >> inputString;
                    input.push_back(inputString);
                }
                break;
            default:
                break;
        }
    }
}

/**
 * find a item by it's id
 * @return
 */
Item & ikea::findById()
{
    int id = getInt();
    for(auto &item: items)
    {
        if(item->getId() == id)
        {
            item->printItem();
            return *item;
        }
    }
    std::cout << NOTFOUND << std::endl;
}


void ikea::find_by_name()
{
    string name = getString();
    for(auto &item: items)
    {
        if(item->get_name() == name)
        {
            item->printItem();
            return;
        }
    }
    std::cout << NOTFOUND << std::endl;
}


bool compById(const Item *first, const Item *second)
{
    return first->getId() > second->getId();
}

void ikea::printById()
{
    if (!items.empty())
    {
        std::sort(items.begin(), items.end(), compById);
        for (auto &item: items)
        {
            item->printItem();
        }
    }
}

bool compByName(const Item *first, const Item *second)
{
    return first->get_name() > second->get_name();
}


/**
 * prints items by name
 */
void ikea::printByName()
{
    if (!items.empty())
    {
        std::sort(items.begin(), items.end(), compByName);
        for (auto &item: items)
        {
            item->printItem();
        }
    }
}

int ikea::sell()
{
    Item to_sell;
    to_sell = findById();
    double quantity;
    try
    {
        if (to_sell.quantityIsInt())
        {
            std::cout << ITEMSINPUT << std::endl;
        }
        else
        {
            std::cout << QUANTITYINPUT << std::endl;
        }
        std::cin >> quantity;
        if (to_sell.getQuantity() >= quantity)
        {
            to_sell.setQuantity(to_sell.getQuantity() - quantity);
        }
        else
        {
            std::cout << "Not enough stock to sell" << std::endl;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cout << NOTFOUND << std::endl;
    }
}

int ikea::getInt()
{
    int input;
    if(std::cin >> input)
    {
        return input;
    }
    else
    {
     std::cerr << "" << std::endl;
    }
}

string ikea::getString()
{
    string input;
    if(std::cin >> input)
    {
        return input;
    }
    else
    {
        std::cerr << "" << std::endl;
    }
}