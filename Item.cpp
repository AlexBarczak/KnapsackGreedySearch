#include <iostream>

#include "Item.h"

using namespace std;

ostream& operator<< (ostream &out, const Item *item){
    out << "weight: " << item->weight << "\n"
        << "profit: " << item->utility << "\n";
    return out;
}

Item::Item(int weight, int utility)
{
    this->weight = weight;
    this->utility = utility;
}