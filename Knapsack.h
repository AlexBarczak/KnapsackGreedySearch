/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <set>

#include "Item.h"

using namespace std;

// struct for containing basic data about the problem
struct KnapsackData
{
    public:
    int capacity;
    set<Item*, p_ItemSorter> items;
    vector<Item*> solution;
};

// struct for representing the knapsack ID, more efficient storage of data than storing the whole node in the
// explored set, which would be a whole pointer per item in the bag instead of this implementation
// requiring one bit per item though it behaves somewhat like a hash map, if we had a knapsack storing a single 
// pointer with ID 128 it would take four integers in the ID array, twice as large as the pointer itself
// but since we store large amounts of items in most cases, most cases make this more efficient
struct KnapsackID{
    public:
    size_t size;
    int* ID;
};

// the knapsack itself, representing a single node in the state space
class Knapsack
{
private:
    // keeps track of the capacity of the bag
    int capacity; 
public:
    // and keeps track of the items it stores in it, pointers are more efficient than storing the whole struct, since the items
    // never change.
    set<Item*> contents;
    // constructors
    Knapsack();
    Knapsack(int capacity);
    // getters
    int getCapacity();
    int contentsWeight();
    int contentsUtility();
    set<Item*>& getContents();
    // return the id of the node
    KnapsackID generateID();
    vector<Knapsack> generateChildNodes(set<Item*, p_ItemSorter> availableItems);
    friend ostream& operator<< (ostream &out, Knapsack* knapsack);
};

#endif