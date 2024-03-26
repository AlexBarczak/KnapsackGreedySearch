#include "KnapsackMetaData.h"

// factorial function used to aid in the determining of total possible state nodes
long KnapsackMetaData::factorial(int x){
    if (x <= 1){
        return 1;
    }
    return x*factorial(x-1);
}

// function for calculating the number of posssible states needing searched through
// when a brute force method is taking and redundant cases are not discarded

// note that an overflow will occur for large numbers of items
long KnapsackMetaData::knapsackNodes(int itemcount){
    long total = 0;

    for (int i = 0; i < itemcount; i++)
    {
        total += factorial(itemcount)/factorial(i);
    }
    
    return total;
}