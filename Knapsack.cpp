/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

// create empty knapsack, sometimes necessary by containers I've used to store them
Knapsack::Knapsack()
{
    this->capacity = 0;
}

// initialise knapsack to know its capacity
Knapsack::Knapsack(int capacity)
{
    this->capacity = capacity;
}

// return the total weight of the items in the knapsack
int Knapsack::contentsWeight(){
    // for each item
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    // run a running total loop
    int weightTotal = 0;

    while (currentItem != endItem)
    {
        // add the weight
        weightTotal += (*currentItem)->getWeight();
        currentItem = next(currentItem);
    }
    
    //  return total
    return weightTotal;
}

// return the total utility of the items in the knapsack
int Knapsack::contentsUtility(){
    // for each item
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    // run a running total loop
    int utilityTotal = 0;

    while (currentItem != endItem)
    {
        // add the utility
        utilityTotal += (*currentItem)->getUtility();
        currentItem = next(currentItem);
    }
    
    //  return the total
    return utilityTotal;
}

//return the capacity of the knapsack
int Knapsack::getCapacity(){
    return this->capacity;
}

// print the knapsack out to display its total weight, utility and the ids of the items within it
ostream& operator<< (ostream &out, Knapsack* knapsack){
    // print the weight and utility
    out << "Bag contents weight: " << knapsack->contentsWeight() << " and have utility: " << knapsack->contentsUtility();

    // for each item
    auto currentItem = knapsack->getContents().begin();
    auto endItem = knapsack->getContents().end();

    out << endl << "contents: " << endl;

    // print the ID of the item separated by a whitespace
    while (currentItem != endItem)
    {
        out << (*currentItem)->getID() << " ";
        currentItem = next(currentItem);
    }

    // return the ostream
    return out;
}

// create child nodes for searching the state space
vector<Knapsack> Knapsack::generateChildNodes(set<Item*> availableItems){
    // initialise list
    vector<Knapsack> childNodes;

    auto start = this->contents.begin();
    auto end = this->contents.end();

    int lowestID = 0;

    if (start != end)
    {
        lowestID = (*start)->getID();
        while (start != end)
        {
            if ((*start)->getID() < lowestID)
            {
                lowestID = (*start)->getID();
            }
            start = next(start);
        }
    }

    // for each item available
    auto currentItem = availableItems.begin();
    auto endItem = availableItems.end();

    while (currentItem != endItem)
    {
        // if the item is not in the bag already
        if((*currentItem)->getID() > lowestID && find(this->contents.begin(), this->contents.end(), *currentItem) == this->contents.end()) {
            // create a new bag based on this one
            Knapsack childNode(*this);
            // add in the missing item
            childNode.contents.insert(*currentItem);
            // put the new knapsack into the list
            childNodes.push_back(childNode);
        }

        currentItem = next(currentItem);
    }

    // return the list of child nodes
    return childNodes;   
}

// return the items in this bag
set<Item*>& Knapsack::getContents(){
    return (this->contents);
}

// create an ID for this bag
KnapsackID Knapsack::generateID(){
    // initialise struct
    KnapsackID ksID;

    // for each item in the bag
    auto currentItem = this->contents.begin();
    auto endItem = this->contents.end();

    // figure out what the largest ID you own is
    int largestItemID = 0;

    // find max algorithm on item ID
    while (currentItem != endItem)
    {
        if ((*currentItem)->getID() > largestItemID)
        {
            largestItemID = (*currentItem)->getID();
        }
        currentItem = next(currentItem);
    }

    // the size of the arrau will be the largest item ID, divided by the number of bits in one
    // array position + 1 because the array enumeration starts at 0
    ksID.size = largestItemID / 32 + 1;
    ksID.ID = new int[ksID.size];

    // initialise array values to 0
    for (int i = 0; i < ksID.size; i++)
    {
        ksID.ID[i] = 0;
    }

    // for each item
    auto startItem = this->contents.begin();

    while (startItem != endItem)
    {
        // get the item id       
        int id = (*startItem)->getID();
        // bitshift the exact position needed to specify this item is in the bag
        ksID.ID[id/32] = ksID.ID[id/32] | (1 << id%32);
        startItem = next(startItem);
    }

    // realising now that for the extremely large datasets which are thousands of items large, that if the item with id
    // 6400 is the only item in the bag it's equivalent to an array of a hundred pointers in size, would love to implement
    // a better solution to this kind of problem but there's no time for me 

    return ksID;
}