#include <iostream>
#include <fstream>
#include <string>

#include "Knapsack.h"
#include "Item.h"

using namespace std;

vector<Item*> items;

vector<Knapsack*> frontier;
vector<Knapsack*> exploredSet;

void breadthFirstSearch();


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

    auto current = items.begin();
    auto end = items.end();

    while (current != end)
    {
        cout << (Item*)(*current);
        current = next(current);
    }

    cout << endl;

    Knapsack* initialState = new Knapsack(capacity);
    frontier.push_back(initialState);

    return 0;
}

