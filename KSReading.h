/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#ifndef KNAPSACK_DATA_READING_H
#define KNAPSACK_DATA_READING_H

#include <set>
#include <iostream>

#include "Knapsack.h"
#include "Item.h"

class KSReading
{
private:
    
public:
    // load items for Florida state university data set
    static void FSU_LoadItems(std::string filepath, KnapsackData& data);
    // load items for university of Cauca data set
    static void UniCauca_LoadItems(std::string filepath, KnapsackData& data);
    // load items for data set from following:
    // https://github.com/JorikJooken/knapsackProblemInstances
    // from paper at
    // https://www.sciencedirect.com/science/article/abs/pii/S037722172101016X
    static void SD_LoadItems(std::string filepath, KnapsackData& data);
};

#endif