/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#ifndef KNAPSACK_ITEM_H
#define KNAPSACK_ITEM_H

#include <iostream>

using namespace std;

// item class specifying the details of any one item that could go in the sack
class Item
{
private:
    int ID;
    int weight;
    int utility;
public:
    // constructor
    Item(int ID, int weight, int utility);
    // getters
    int getID();
    int getWeight();
    int getUtility();
    // stream writer
    friend ostream& operator<< (ostream &out, const Item *item);
};

#endif