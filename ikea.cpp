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

void ikea::inputMovieOrBook(std::ifstream inFile)
{
    string line;
    string desc;
    for (int i = 5; i < 7; i++)
    {
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> desc;
        switch (i)
        {
            case 5:
                if (!checkFormat(desc, "Year of publication:"))
                {
                    iss >> input[i];
                }
                break;
            case 6:
                if (!checkFormat(desc, "Length:"))
                {
                    iss >> input[i];
                }
                break;
            default:
                break;
        }
    }
    type = movieAndBook;
}


void ikea::inputFurniture(std::ifstream inFile)
{
    string line;
    string desc;
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> desc;

    if (!checkFormat(desc, "Capacity:"))
    {
        iss >> input[7];
        type = kitchen;
    }
    else if (checkFormat(desc, "Material:"))
    {
        iss >> input[7];
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> desc;
        if (checkFormat(desc, "Color:"))
        {
            iss >> input[8];
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
    string desc;
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> desc;
    if (desc == "Weight:")
    {
        iss >> input[5];
        type = fabric;
        addItem(false);
    }
    else if (desc == "Calories:")
    {
        iss >> input[5];
        type = candy;
        addItem(false);
    }
    else if (desc == "Author:")
    {
        iss >> input[5];
        inputMovieOrBook(inFile);
        addItem(true);
    }
    else if (desc == "Dimensions:")
    {
        iss >> input[5] >> input[6] >> input[7];
        inputFurniture(inFile);
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


int ikea::getFirstLines(std::ifstream inFile)
{
    string line;
    string desc;
    for (int i = 0; i < 4; i++)
    {
        std::getline(inFile, line);
        std::istringstream iss(line);
        iss >> desc;
        switch (i)
        {
            case 0:
                if (!checkFormat(desc, "Item:"))
                {
                    iss >> input[i];
                }
                break;
            case 1:
                if (!checkFormat(desc, "Name:"))
                {
                    iss >> input[i];
                }
                break;
            case 2:
                if (!checkFormat(desc, "Quantity:"))
                {
                    iss >> input[i];
                }
                break;
            case 3:
                if (!checkFormat(desc, "Price:"))
                {
                    iss >> input[i];
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
void ikea::findById()
{
    try
    {
        getInput<unsigned int>();
    }
    catch (const std::out_of_range &e)
    {
        std::cout << NOTFOUND << std::endl;
    }
}


//todo find by name lambda?
void ikea::find_by_name()
{
    try
    {

    }
    catch (const std::out_of_range &e)
    {
        std::cout << NOTFOUND << std::endl;
    }
}


bool compById(const Item &first, const Item &second) const
{
    return first.get_id() > second.get_id();
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

bool compByName(const Item &first, const Item &second) const
{
    return first.get_name() > second.get_name();
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
    Item *to_sell;
    double quantity;
    try
    {
        to_sell = *items.at(getInput<unsigned int>());
        if (to_sell->is_quantityIsInt())
        {
            std::cout << ITEMSINPUT << std::endl;
        }
        else
        {
            std::cout << QUANTITYINPUT << std::endl;
        }
        std::cin >> quantity;
        if (to_sell->get_quantity() >= quantity)
        {
            to_sell->set_quantity(to_sell->get_quantity() - quantity);
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


/**
 * gets input from keyboard of a certain type
 * @tparam T
 * @return
 */
template<typename T>
T &ikea::getInput()
{
    //todo fail or this way?
    T input;
    if(std::cin >> input)
    {
        return input;
    }
    else
    {
     std::cerr << "" << std::endl;
    }
}


//todo line separator