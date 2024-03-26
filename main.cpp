/*
    Author: Aleksander Barczak
    Matric number: 2497555
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include <queue>

#include "Knapsack.h"
#include "KSReading.h"
#include "Item.h"
#include "KnapsackMetaData.h"

using namespace std;

struct compareIntArray{
    public:
    bool operator()(KnapsackID lhs, KnapsackID rhs) const 
    {
        if (lhs.size != rhs.size)
        {
            return lhs.size < rhs.size;
        }
        
        for (int i = 0; i < lhs.size; i++)
        {
            if (lhs.ID[i] != rhs.ID[i])
            {
                return lhs.ID[i] < rhs.ID[i];
            }
        }

        return false;
    }
};


priority_queue<Knapsack, vector<Knapsack>, KnapsackCompare> frontier;
set<KnapsackID, compareIntArray> exploredSet;

int main(int argc, char const *argv[])
{
    string fileChosen;
    string fileLine;

    if (argc < 3){
        cout    << "arguments not supplied\n"
                << "provide arguments as followed:\n"
                << "./a.out <filename> <datasource>\n"
                << "where filepath points to a dataset and datasource is 'FSU' 'UC'\n"
                << "for Florida State Uni and Cauca Univarsityas the data sources to describe their format\n"
                << "DataFromFSU is the directory for FSU problems while large-scale is the directory for UC" << endl;
        return 0;
    }

    KnapsackData data;

    if (string(argv[2]) == "FSU")
    {
        fileChosen = "DataFromFSU/" + string(argv[1]);
        try
        {
            KSReading::FSU_LoadItems(fileChosen, data);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    } else if (string(argv[2]) == "UC")
    {
        fileChosen = "large_scale/" + string(argv[1]);
        try
        {
            KSReading::UniCauca_LoadItems(fileChosen, data);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    }else{
        cout << "file format specified not recognised\n";
        return 0;
    }

    Knapsack initialState(data.capacity);
    frontier.emplace(initialState);
    Knapsack bestNode = frontier.top();
    cout << &bestNode << endl;

    // utility to weight ratio
    double BestU2WRatio = -1;

    auto current = data.items.begin();
    auto end = data.items.end();

    while (current != end)
    {
        // figure out if this item has the best U2W ratio
        // calculate U2W ratio
        double U2W = (*current)->getUtility()/(*current)->getWeight();

        if (U2W > BestU2WRatio)
        {
            BestU2WRatio = U2W;
        }
        
        current = next(current);
    }
    

    int nodesFound = 0;
    int nodesDiscarded = 0;
    int nodesSearched = 0;
    int limiter = 1000000;
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
    

    while (!frontier.empty() && limiter > nodesSearched)
    {
        cout << "hi" << endl;
        
        // take next node in frontier and remove it from the frontier
        Knapsack currentNode = frontier.top();
        frontier.pop();

        if (exploredSet.find(currentNode.generateID()) != exploredSet.end()){
            nodesDiscarded++;
            continue;
        }

        exploredSet.insert(currentNode.generateID());
        
        cout << "hello" << endl;


        // check if this node performs better than the previously best performing node
        if (currentNode.contentsWeight() <= currentNode.getCapacity() && bestNode.contentsUtility() < currentNode.contentsUtility())
        {
            cout << "new best bag found: " << &currentNode << endl;
            bestNode = currentNode;
        }

        // get the child nodes available from this node and add them to the frontier
        vector<Knapsack> childNodes = currentNode.generateChildNodes(data.items);
        nodesFound += childNodes.size();

        auto currentChildNode = childNodes.begin();
        auto endChildNode = childNodes.end();

        cout << "hey" << endl;

        while (currentChildNode != endChildNode)
        {            

            if ((*currentChildNode).contentsWeight() <= (*currentChildNode).getCapacity() && 
                  exploredSet.find(currentChildNode->generateID()) == exploredSet.end() &&
                  ((double)(data.capacity - currentChildNode->contentsWeight())*BestU2WRatio + (double)currentChildNode->contentsUtility() >= (double)bestNode.contentsUtility() * 0.99))
            {
                frontier.emplace(*currentChildNode);
            }else{
                nodesDiscarded++;
            }
            currentChildNode = next(currentChildNode);
        }
        
        nodesSearched++;
    }

    cout << "best bag found was: " << &bestNode << endl;
    cout << "max node count when order matters: " << KnapsackMetaData::knapsackNodes(data.items.size()) << endl;
    cout << "max node count when order does not matter: " << pow(2, data.items.size()) << endl;
    cout << "nodes found: " << nodesFound << endl;
    cout << "nodes discarded: " << nodesDiscarded << endl;
    cout << "nodes searched: " << nodesSearched << endl;

    cout << "percentage of unique item combinations searched: " << nodesSearched/pow(2, data.items.size())*100 << "%" << endl;

    return 0;
}