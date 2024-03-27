/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#include <iostream>

#include "Item.h"

using namespace std;

// write out the exact details of an item, written to take a pointer because that's
// what we handle in all cases in this program
ostream& operator<< (ostream &out, const Item *item){
    out << "ID:     " << item->ID << "\n"
        << "weight: " << item->weight << "\n"
        << "profit: " << item->utility << "\n";
    return out;
}

// constructor
Item::Item(int ID, int weight, int utility)
{
    this->ID = ID;
    this->weight = weight;
    this->utility = utility;
}

// return id
int Item::getID(){
    return this->ID;
}

// return weight
int Item::getWeight(){
    return this->weight;
}

//return utility
int Item::getUtility(){
    return this->utility;
}