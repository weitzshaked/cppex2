

#include <algorithm>
#include "ikea.h"

int main()
{
    auto *catalog = new ikea();
    int choice;
    std::cout << menu << std::endl;
    std::cin >> choice;
    while (choice != 7)
    {
        switch (choice)
        {
            case 1:
                catalog->input_stock();
                break;
            case 2:
                catalog->find_by_id();
                break;
            case 3:
                catalog->find_by_name();
                break;
            case 4:
                catalog->print_by_id();
                break;
            case 5:
                catalog->print_by_name();
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

int ikea::input_stock()
{
    std::string path;
    std::cin >> path;

    return 0;
}

/**
 * find a item by it's id
 * @return
 */
void ikea::find_by_id()
{
    try
    {
        std::cout << items.at(get_input<unsigned int>());
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Item not found" << std::endl;
    }
}

bool comp_by_id(const Item& first, const Item& second) const
{
    return first.get_id() > second.get_id();
}


void ikea::print_by_id()
{
    if(items.size() != 0)
    {
        std::sort(items.begin(), items.end(), comp_by_id);
        for (auto &item: items)
        {
            std::cout << item;
        }
    }
}

bool comp_by_name(const Item& first, const Item& second) const
{
    return first.get_name() > second.get_name();
}


/**
 * prints items by name
 */
void ikea::print_by_name()
{
    if(items.size() != 0)
    {
        std::sort(items.begin(), items.end(), comp_by_name);
        for (auto &item: items)
        {
            std::cout << item;
        }
    }
}

int ikea::sell()
{
    Item to_sell;
    double quantity;
    try
    {
        to_sell = *items.at(get_input<unsigned int>());
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Item not found" << std::endl;
    }
    if (to_sell.)
    {
        std::cout << "Please enter number of items:" << std::endl;
    }
    else
    {
        std::cout << "Please enter desired quantity:" << std::endl;
    }
    std::cin >> quantity;
    if (to_sell.get_quantity() >= quantity)
    {
        to_sell.set_quantity(to_sell.get_quantity() - quantity);
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
T& ikea::get_input()
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


