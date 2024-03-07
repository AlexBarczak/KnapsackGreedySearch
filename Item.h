#ifndef KNAPSACK_ITEM_H
#define KNAPSACK_ITEM_H

#include <iostream>

using namespace std;

class Item
{
private:
    int weight;
    int utility;
public:
    Item(int weight, int utility);
    int getWeight();
    int getUtility();
    friend ostream& operator<< (ostream &out, const Item *item);
};

#endif