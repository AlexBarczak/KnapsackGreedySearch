#include <iostream>
#include <algorithm>
#include <vector>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

Knapsack::Knapsack(int capacity)
{
    this->capacity = capacity;
}

int Knapsack::contentsWeight(){
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    int weightTotal = 0;

    while (currentItem != endItem)
    {
        weightTotal += (*currentItem)->getWeight();
        currentItem = next(currentItem);
    }
    
    return weightTotal;
}

int Knapsack::contentsUtility(){
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    int utilityTotal = 0;

    while (currentItem != endItem)
    {
        utilityTotal += (*currentItem)->getUtility();
        currentItem = next(currentItem);
    }
    
    return utilityTotal;
}

int Knapsack::getCapacity(){
    return this->capacity;
}

ostream& operator<< (ostream &out, Knapsack* knapsack){
    out << "Bag contents weight: " << knapsack->contentsWeight() << " and have utility: " << knapsack->contentsUtility();
    return out;
}

vector<Knapsack> Knapsack::generateChildNodes(vector<Item*> availableItems){
    vector<Knapsack> childNodes;

    auto currentItem = availableItems.begin();
    auto endItem = availableItems.end();

    while (currentItem != endItem)
    {
        if(find(this->contents.begin(), this->contents.end(), *currentItem) == this->contents.end()) {
            Knapsack childNode(*this);
            childNode.contents.push_back(*currentItem);
            childNodes.push_back(childNode);
        }

        currentItem = next(currentItem);
    }

    return childNodes;
    
}