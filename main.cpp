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

priority_queue<Knapsack, vector<Knapsack>, KnapsackCompare> frontier;
set<int> exploredSet;

int main(int argc, char const *argv[])
{
    string fileChosen;
    string fileLine;

    if (argc >= 3)
    {
        string fileName(argv[1]);
        fileChosen = "DataFromFSU/" + fileName;
    }else{
        cout    << "arguments not supplied\n"
                << "provide arguments as followed:\n"
                << "./a.out <filepath> <datasource>\n"
                << "where filepath points to a dataset and datasource is 'FSU' 'UC' 'JJ'\n"
                << "for Florida State Uni, Cauca Univarsity and JorikJooken as the data sources to describe their format" << endl;
        return 0;
    }

    KnapsackData data;

    if (argv[2] == "FSU")
    {
        KSReading::FSU_LoadItems(fileChosen, data);
    } else if (argv[2] == "UC")
    {
        KSReading::UniCauca_LoadItems(fileChosen, data);
    }

    KSReading::FSU_LoadItems(fileChosen, data);

    Knapsack initialState(data.capacity);
    frontier.emplace(initialState);
    Knapsack bestNode = frontier.top();
    cout << &bestNode << endl;


    // utility to weight eatio
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
        // take next node in frontier and remove it from the frontier
        Knapsack currentNode = frontier.top();
        frontier.pop();

        if (exploredSet.find(currentNode.generateID()) != exploredSet.end()){
            nodesDiscarded++;
            continue;
        }

        exploredSet.insert(currentNode.generateID());
        
        
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