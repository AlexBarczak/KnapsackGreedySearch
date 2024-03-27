/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#ifndef KNAPSACK_META_DATA_H
#define KNAPSACK_META_DATA_H

// essentially an abstract class with the purpose of containing the factorial and knapsack nodes functions
class KnapsackMetaData
{
private:
    static long factorial(int x);
public:
    // return the number of nodes that would have to be searched in a brute force manner if we searched varying orderings
    // of the same item combinations, the value is grows at a factorial rate relative to the item count and so breaks quickly
    static long knapsackNodes(int itemCount);
    
};

#endif