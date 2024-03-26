#ifndef KNAPSACK_DATA_READING_H
#define KNAPSACK_DATA_READING_H

#include <set>
#include <iostream>

#include "Item.h"

class KSReading
{
private:
    
public:
    // load items for Florida state university data set
    static void FSU_LoadItems(std::string filepath, set<Item*>& items);
    // load items for university of Cauca data set
    static void UniCauca_LoadItems(std::string filepath, set<Item*>& items);
    // load items for data set from following:
    // https://github.com/JorikJooken/knapsackProblemInstances
    // from paper at
    // https://www.sciencedirect.com/science/article/abs/pii/S037722172101016X
    static void SD_LoadItems(std::string filepath, set<Item*>& items);
};

#endif