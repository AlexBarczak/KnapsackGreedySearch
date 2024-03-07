#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

#include "Item.h"

using namespace std;

class Knapsack
{
private:
    int capacity;
    vector<Item*> contents;
public:
    Knapsack(int capacity);
    int getCapacity();
    int contentsWeight();
    int contentsUtility();
    vector<Knapsack> generateChildNodes(vector<Item*> availableItems);
    friend ostream& operator<< (ostream &out, Knapsack* knapsack);
};

#endif