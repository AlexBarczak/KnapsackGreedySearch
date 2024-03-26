#include <iostream>
#include <algorithm>
#include <vector>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

Knapsack::Knapsack()
{
    this->capacity = 0;
}

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

    auto currentItem = knapsack->getContents().begin();
    auto endItem = knapsack->getContents().end();

    out << endl << "contents: " << endl;

    while (currentItem != endItem)
    {
        out << (*currentItem)->getID() << " ";
        currentItem = next(currentItem);
    }
    

    return out;
}

vector<Knapsack> Knapsack::generateChildNodes(set<Item*> availableItems){
    vector<Knapsack> childNodes;

    auto currentItem = availableItems.begin();
    auto endItem = availableItems.end();

    while (currentItem != endItem)
    {
        if(find(this->contents.begin(), this->contents.end(), *currentItem) == this->contents.end()) {
            Knapsack childNode(*this);
            childNode.contents.insert(*currentItem);
            childNodes.push_back(childNode);
        }

        currentItem = next(currentItem);
    }

    return childNodes;   
}

set<Item*>& Knapsack::getContents(){
    return (this->contents);
}

int Knapsack::generateID(){
    int KnapsackID = 0;
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    while (currentItem != endItem)
    {
        KnapsackID = KnapsackID | (1 << (*currentItem)->getID());
        currentItem = next(currentItem);
    }
    return KnapsackID;
}