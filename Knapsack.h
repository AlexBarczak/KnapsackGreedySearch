#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <set>

#include "Item.h"

using namespace std;

class Knapsack
{
private:
    int capacity; 
public:
    set<Item*> contents;
    Knapsack();
    Knapsack(int capacity);
    int getCapacity();
    int contentsWeight();
    int contentsUtility();
    set<Item*>& getContents();
    int generateID();
    vector<Knapsack> generateChildNodes(set<Item*> availableItems);
    friend ostream& operator<< (ostream &out, Knapsack* knapsack);
};

struct  KnapsackCompare
{
    public:
    bool operator()(Knapsack& lhs, Knapsack& rhs) const 
    {
        return lhs.contentsUtility()/lhs.contentsWeight() < rhs.contentsUtility()/rhs.contentsWeight();
    }
};

struct KnapsackData
{
    public:
    int capacity;
    set<Item*> items;
};


#endif