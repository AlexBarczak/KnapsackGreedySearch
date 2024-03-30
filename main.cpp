/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <stack>

#include "Knapsack.h"
#include "KSReading.h"
#include "Item.h"
#include "KnapsackMetaData.h"

using namespace std;

// priority queue for using best first search, and a set of explored KnapsacksIDs to allow
// graph search
stack<Knapsack, vector<Knapsack>> frontier;

int main(int argc, char const *argv[])
{
    // the file chosen by the user
    string fileChosen;

    // guiding message to aid user
    if (argc < 3){
        cout    << "arguments not supplied\n"
                << "provide arguments as followed:\n"
                << "./a.out <filename> <datasource>\n"
                << "where filepath points to a dataset and datasource is 'FSU' 'UC'\n"
                << "for Florida State Uni and Cauca Univarsityas the data sources to describe their format\n"
                << "DataFromFSU is the directory for FSU problems while large-scale is the directory for UC\n" 
                << "for example \"./a.out p01 FSU\" or \"./a.out knapPI_1_100_1000_1\"" << endl;
        return 0;
    }

    // data structure where problem information will be written
    // ideally would be a separate control class which performs the searching logic
    // but constraints and lack of experience force otherwise
    KnapsackData data;

    // determine which method of loading the file is to be used
    if (string(argv[2]) == "FSU")
    {
        // file will be in the FSU directory
        fileChosen = "DataFromFSU/" + string(argv[1]);
        // wrap in try to catch file or reading error
        try
        {
            // read the data into the data struct from the file specified
            KSReading::FSU_LoadItems(fileChosen, data);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    } else if (string(argv[2]) == "UC")
    {
        // file will be in the Cauca University directory
        // NOTE: Cauca university datasets are massive and will result in the process being terminated by the 
        // operating system due to running out of memory, I should also partially remedy this by implementing checks for nullptrs
        // when allocating memory (though this is very rarely done by me as most of the object are made on the stack)
        // to try and prevent the user from facing issues
        fileChosen = "large_scale/" + string(argv[1]);
        // wrap in try to catch file or reading error
        try
        {
            // read the data into the data struct from the file specified
            KSReading::UniCauca_LoadItems(fileChosen, data);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    }else{
        // user entered a format unrecognised by the program
        cout << "file format specified not recognised\n";
        return 0;
    }

    // create the initial node - an empty knapsack - and place it into the frontier
    Knapsack initialState(data.capacity);
    frontier.emplace(initialState);
    Knapsack bestNode = frontier.top();

    // utility to weight ratio, this is used for a dynamic form of applying constraint satisfaction problem design to this
    // whenever a child node is being considered we will check if its child nodes have the ability to go beyond the best performing
    // node being kept track of.
    // we do this by finding the best possible item in terms of utility to cost performance and supposing that a node is 
    // only capable of surpassing the current best node by filling the remaining space in it to the brim with 
    // a perfect item the size of the remaining space and the efficiency of the best item described here.
    double BestU2WRatio = -1;

    // basic find max algorithm on the items
    auto current = data.items.begin();
    auto end = data.items.end();

    while (current != end)
    {
        // figure out if this item has the best U2W ratio
        // calculate U2W ratio
        double U2W = (double)(*current)->getUtility()/(double)(*current)->getWeight();

        if (U2W > BestU2WRatio)
        {
            BestU2WRatio = U2W;
            
        }
        
        current = next(current);
    }

    // stats to provide some metadata
    int nodesFound = 1;
    int nodesDiscarded = 0;
    int nodesSearched = 0;
    // limiter cuts off execution, if number of nodes searched exceeds it,
    // to prevent cases of intractable time being used, though space is likely to run out firsst for such large
    // example
    int limiter = 1000000;
    // allow the customisation of the limiter
    if (argc == 4)
    {
        try
        {
            limiter = stoi(argv[3]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            cout << "putting value of limiter back to 1000000" << endl;
            limiter = 1000000;
        }
        
    }
    
    // begine state search
    // so long as there are still nodes to search and the limit has not been exceeded
    while (!frontier.empty() && limiter > nodesSearched)
    {
        // take next node in frontier and remove it from the frontier
        Knapsack currentNode = frontier.top();
        frontier.pop();

        // check if this node performs better than the previously best performing node
        if (currentNode.contentsWeight() <= currentNode.getCapacity() && bestNode.contentsUtility() < currentNode.contentsUtility())
        {
            cout << "new best bag found: " << &currentNode << endl;
            cout << "U2W of best bag: " << (float)currentNode.contentsUtility()/(float)currentNode.contentsWeight() << endl;
            bestNode = currentNode;
        }

        if(!(data.capacity - currentNode.contentsWeight())*BestU2WRatio + currentNode.contentsUtility() > bestNode.contentsUtility()){
            nodesSearched;
            continue;
        }

        // get the child nodes available from this node and add them to the frontier if suitable
        vector<Knapsack> childNodes = currentNode.generateChildNodes(data.items);
        nodesFound += childNodes.size();

        // for each child node in the generated nodes
        auto currentChildNode = childNodes.rbegin();
        auto endChildNode = childNodes.rend();

        while (currentChildNode != endChildNode)
        {            
            // discard the child if it exceeds the knapsack -- very basic CSP
            if ((*currentChildNode).contentsWeight() <= data.capacity &&
                // discard if node cannot surpass best node currently found -- dynamic CSP
                // the use of of converting values to doubles is due to errors found in previous versions of the program
                // believed to be due to floating point number accuracy issues, the program would discard items with very close
                // values
                ((data.capacity - currentChildNode->contentsWeight())*BestU2WRatio + currentChildNode->contentsUtility() >= bestNode.contentsUtility()))
            {
                // if suitable, add child node to those to be explored
                frontier.emplace(*currentChildNode);
            }else{
                // otherwise, discard the child node
                nodesDiscarded++;
            }
            // move on to the next node
            currentChildNode = next(currentChildNode);
        }
        
        // the node has been searched and it's children (where suitable) added to the frontier
        nodesSearched++;
        // update the user on number of nodes searched periodically
        if(nodesSearched % 500 == 0)cout << nodesSearched << " nodes searched, frontier size: " <<  frontier.size()<< "\n";
    }

    // tell user what the best performing node found was
    // also display contents of the bag as a series of ite IDs corresponding to the 
    // line an item was found on
    cout << "best bag found was: " << &bestNode << endl;
    cout << "max node count when order matters:";
    // Knapsack Nodes is a function trying to calculate the amount of nodes needing searched in a brute force manner
    // with all orderings of items considered, the value becomes too large to work with after a value of 21, though 
    // this is really just an issue with returning the value as an integer instead of a float which wuld approximate it
    // would fix if I had more time
    if (data.items.size() > 21)
    {
        cout << "too many for showing" << endl ;
    } else{
        cout << KnapsackMetaData::knapsackNodes(data.items.size()) << endl;
    }    
    
    // display some basic stats to the user
    cout << "max node count when order does not matter: " << pow(2, data.items.size()) << endl;
    cout << "nodes found: " << nodesFound << endl;
    cout << "nodes discarded: " << nodesDiscarded << endl;
    cout << "nodes searched: " << nodesSearched << endl;

    cout << "percentage of unique item combinations searched: " << nodesSearched/pow(2, data.items.size())*100 << "%" << endl;

    if (string(argv[2]) == "UC")
    {
        cout << "solution: \n";
        auto itemStart = data.solution.begin();
        auto itemEnd = data.solution.end();

        int utility = 0;
        int weight = 0;

        while (itemStart != itemEnd)
        {
            utility += (*itemStart)->getUtility();
            weight += (*itemStart)->getWeight();

            itemStart = next(itemStart);
        }
        
        cout << "utility: " << utility << endl;
        cout << "weight: " << weight << endl;
    }
    

    /*
    following code was used to find breaking point of floating point exception caused by calculating the total possible search nodes
    it already suffers from overflow after argument value 22, but having reached 66 it completely crashes
    for (int i = 0; i < 100; i++)
    {
        cout << i << ": " << KnapsackMetaData::knapsackNodes(i) << endl;

    }
    */

    return 0;
}