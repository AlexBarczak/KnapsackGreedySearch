#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

#include "Item.h"

class Knapsack
{
private:
    int capacity;
    std::vector<Item*> contents;
public:
    Knapsack(int capacity);
};

Knapsack::Knapsack(int capacity)
{
    this->capacity = capacity;
}

#endif