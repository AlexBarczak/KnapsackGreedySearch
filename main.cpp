#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

int factorial(int x){
    if (x <= 1){
        return 1;
    }
    return x*factorial(x-1);
}

int KnapsackNodes(int itemcount){
    int total = 0;

    for (int i = 0; i < itemcount; i++)
    {
        total += factorial(itemcount)/factorial(i);
    }
    
    return total;
}

class KnapsackHeuristic
{
public:
    bool operator() (Knapsack* a, Knapsack* b){
        return true;
    }
};

void breadthFirstSearch();

vector<Item*> items;

//priority_queue<Knapsack, vector<Knapsack>, KnapsackHeuristic> frontier;
vector<Knapsack> frontier;
//vector<Knapsack> exploredSet;

int main(int argc, char const *argv[])
{
    string fileLine;

    // get capacity
    ifstream dataFile("p07_c.txt");
    getline(dataFile, fileLine);
    dataFile.close();
    int capacity = stoi(fileLine);

    {
        vector<int> weights;
        vector<int> profits;
        
        // get item weights
        dataFile.open("p07_w.txt");
        while (getline(dataFile, fileLine))
        {
            weights.push_back(stoi(fileLine));   
        }
        dataFile.close();

        // get item profits
        dataFile.open("p07_p.txt");
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
            Item* currentItem = new Item((*currentw), (*currentp));
            items.push_back(currentItem);

            currentw = next(currentw);
            currentp = next(currentp);
        }
        
    }

    Knapsack initialState(capacity);
    frontier.push_back(initialState);
    Knapsack bestNode = frontier.back();
    cout << &bestNode << endl;

    int nodesFound = 0;
    int nodesSearched = 0;
    int limiter = 100000;

    while (!frontier.empty() && limiter > nodesSearched)
    {
        Knapsack currentNode = frontier.back();
        frontier.pop_back();

        //cout << "checking bag: " << &currentNode << endl;

        if (currentNode.contentsWeight() < currentNode.getCapacity() && bestNode.contentsUtility() < currentNode.contentsUtility())
        {
            cout << "new best bag found: " << &currentNode << endl;
            bestNode = currentNode;
        }
        
        //exploredSet.push_back(currentNode);

        vector<Knapsack> childNodes = currentNode.generateChildNodes(items);
        nodesFound += childNodes.size();
        frontier.insert(frontier.end(), childNodes.begin(), childNodes.end());

        nodesSearched++;
    }

    cout << "best bag found was: " << &bestNode << endl;
    cout << "expected node count: " << KnapsackNodes(items.size()) << endl;
    cout << "nodes found: " << nodesFound << endl;
    cout << "nodes searched: " << nodesSearched << endl;
    

    return 0;
}