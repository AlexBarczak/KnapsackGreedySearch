/*
    Author: Aleksander Barczak
    Matric number: 2497555
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

// list of actions?
set<Item*> items;

// priority queue will be implemented once ready to start applying greedy best first search
//priority_queue<Knapsack, vector<Knapsack>, KnapsackHeuristic> frontier;
vector<Knapsack> frontier;
// explored set will be implemented once ready to apply graph structure to set
set<int> exploredSet;

// factorial function used to aid in the determining of total possible state nodes
long factorial(int x){
    if (x <= 1){
        return 1;
    }
    return x*factorial(x-1);
}

// function for calculating the number of posssible states needing searched through
// when a brute force method is taking and redundant cases are not discarded

long knapsackNodes(int itemcount){
    long total = 0;

    for (int i = 0; i < itemcount; i++)
    {
        total += factorial(itemcount)/factorial(i);
    }
    
    return total;
}

void loadItems(string filePath){
    int itemID = 0;
    vector<int> weights;
    vector<int> profits;

    string fileLine;
    
    // get item weights
    ifstream dataFile(filePath + "_w.txt");
    while (getline(dataFile, fileLine))
    {
        weights.push_back(stoi(fileLine));   
    }
    dataFile.close();

    // get item profits
    dataFile.open(filePath + "_p.txt");
    while (getline(dataFile, fileLine))
    {
        profits.push_back(stoi(fileLine));   
    }
    dataFile.close();

    auto currentw = weights.begin();        
    auto currentp = profits.begin();

    auto endw = weights.end();

    while (currentw != endw)
    {
        Item* currentItem = new Item(itemID++, (*currentw), (*currentp));
        items.insert(currentItem);

        currentw = next(currentw);
        currentp = next(currentp);
    }
}

int main(int argc, char const *argv[])
{
    string fileChosen = "DataFromFSU/p02";
    string fileLine;

    cout << "arguments found: " << argc << endl;

    if (argc >= 2)
    {
        string fileName(argv[1]);
        fileChosen = "DataFromFSU/" + fileName;
    }

    // get capacity
    cout << "filepath: " << fileChosen + "_c.txt" << endl;
    ifstream dataFile(fileChosen + "_c.txt");

    if(dataFile.fail()){
        cout << "file not found" << endl;
        return 0;
    }

    getline(dataFile, fileLine);
    dataFile.close();
    int capacity = stoi(fileLine);

    loadItems(fileChosen);

    Knapsack initialState(capacity);
    frontier.push_back(initialState);
    Knapsack bestNode = frontier.back();
    cout << &bestNode << endl;

    int nodesFound = 0;
    int nodesDiscarded = 0;
    int nodesSearched = 0;
    int limiter = 1000000;
    if (argc >= 3)
    {
        try
        {
            limiter = stoi(argv[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            cout << "putting value of limiter back to 1000000";
            limiter = 1000000;
        }
        
        
    }
    

    while (!frontier.empty() && limiter > nodesSearched)
    {
        // take next node in frontier and remove it from the frontier
        Knapsack currentNode = frontier.back();
        frontier.pop_back();

        exploredSet.insert(currentNode.generateID());
        
        
        // check if this node performs better than the previously best performing node
        if (currentNode.contentsWeight() < currentNode.getCapacity() && bestNode.contentsUtility() < currentNode.contentsUtility())
        {
            cout << "new best bag found: " << &currentNode << endl;
            bestNode = currentNode;
        }

        // get the child nodes available from this node and add them to the frontier
        vector<Knapsack> childNodes = currentNode.generateChildNodes(items);
        nodesFound += childNodes.size();

        auto currentChildNode = childNodes.begin();
        auto endChildNode = childNodes.end();

        while (currentChildNode != endChildNode)
        {            

            if ((*currentChildNode).contentsWeight() < (*currentChildNode).getCapacity() && exploredSet.find(currentChildNode->generateID()) == exploredSet.end())
            {
                frontier.push_back(*currentChildNode);
            }else{
                nodesDiscarded++;
            }
            currentChildNode = next(currentChildNode);
        }

        nodesSearched++;
    }

    cout << "best bag found was: " << &bestNode << endl;
    cout << "max node count when order matters: " << knapsackNodes(items.size()) << endl;
    cout << "max node count when order does not matter: " << pow(2, items.size()) << endl;
    cout << "nodes found: " << nodesFound << endl;
    cout << "nodes discarded: " << nodesDiscarded << endl;
    cout << "nodes searched: " << nodesSearched << endl;

    cout << "percentage of unique item combinations searched: " << nodesSearched/pow(2, items.size())*100 << "%" << endl;

    return 0;
}