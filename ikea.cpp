#include "ikea.h"


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
                catalog->inputStock();
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
                catalog->sell();
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
    std::cout<<"6. Sell item" << std::endl;
    std::cout << "7. Exit" << std::endl;
}


int ikea::inputStock()
{
    std::string path;
    std::cin >> path;

    std::ifstream inFile(path.c_str());

    if(!inFile)
    {
        std::cerr << "" << std::endl;
        return -1;
    }

    return 0;
}

/**
 * find a item by it's id
 * @return
 */
void ikea::findById()
{
    try
    {
        std::cout << items.at(getInput<unsigned int>());
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
    if(!items.empty())
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
    if(!items.empty())
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
    }
    catch (const std::out_of_range &e)
    {
        std::cout << NOTFOUND << std::endl;
    }
    if (to_sell->)
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


/**
 * gets input from keyboard of a certain type
 * @tparam T
 * @return
 */
template <typename T>
T& ikea::getInput()
{
    T input;
    std::cin >> input;
//    //todo bad/fail
//    if()
//    {
//
//    }
    return input;
}


