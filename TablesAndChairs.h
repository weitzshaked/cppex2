//
// Created by weitz on 03/09/2018.
//

#ifndef CPPEX2_TABLESANDCHAIRS_H
#define CPPEX2_TABLESANDCHAIRS_H


#include "Furniture.h"

class TablesAndChairs : public Furniture
{
public:
    TablesAndChairs(int id, string &name, double price, double quantity, double x, double y,
                    double z,
                    string material, string color) : Furniture(id, name, price, quantity, x, y, x),
                                                     _material(material), _color(color)
    {};
    virtual void printItem()
    {
        Furniture::printItem();
        std::cout << "Material: " << _material << std::endl;
        std::cout << "Color: " << _color << std::endl;
        std::cout << "-----" << std::endl;
    }
protected:
    string _material;
    string _color;
};


#endif //CPPEX2_TABLESANDCHAIRS_H
