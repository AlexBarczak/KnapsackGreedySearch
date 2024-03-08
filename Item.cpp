#include <iostream>

#include "Item.h"

using namespace std;

ostream& operator<< (ostream &out, const Item *item){
    out << "ID:     " << item->ID << "\n"
        << "weight: " << item->weight << "\n"
        << "profit: " << item->utility << "\n";
    return out;
}

Item::Item(int ID, int weight, int utility)
{
    this->ID = ID;
    this->weight = weight;
    this->utility = utility;
}

int Item::getID(){
    return this->ID;
}

int Item::getWeight(){
    return this->weight;
}

int Item::getUtility(){
    return this->utility;
}