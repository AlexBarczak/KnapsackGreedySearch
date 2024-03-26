#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "KSReading.h"

using namespace std;

void  KSReading::FSU_LoadItems(std::string filepath, KnapsackData& data){

    set<Item*>* items = &(data.items);

    int itemID = 0;
    vector<int> weights;
    vector<int> profits;

    string fileLine;

    // get capacity
    ifstream dataFile(filepath + "_c.txt");

    if(dataFile.fail()){
        cout << "file not found" << endl;
        throw std::invalid_argument("file not found");
    }

    getline(dataFile, fileLine);
    dataFile.close();
    data.capacity = stoi(fileLine);
    
    // get item weights
    dataFile.open(filepath + "_w.txt");
    while (getline(dataFile, fileLine))
    {
        weights.push_back(stoi(fileLine));   
    }
    dataFile.close();

    // get item profits
    dataFile.open(filepath + "_p.txt");
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
        items->insert(currentItem);

        currentw = next(currentw);
        currentp = next(currentp);
    }
}

void  KSReading::UniCauca_LoadItems(std::string filepath, KnapsackData& data){
    set<Item*>* items = &(data.items);

    int itemID = 0;

    string fileLine;
    string word;

    ifstream dataFile(filepath);

    if(dataFile.fail()){
        cout << "file not found" << endl;
        throw new exception();
    }

    // file format is:
    // number_of_items capacity
    // item_1_profit item_1_weight
    // item_2_profit item_2_weight
    // :             :
    // item_n_profit item_n_weight
    // optimal solution

    // where the optimal solution is written in n 1s and 0s
    // such that the mth item is optimal if the mth binary value is 1

    // get capacity
    getline(dataFile, fileLine);
    int itemCount;
    {
        stringstream ss(fileLine);

        ss >> word;
        itemCount = stoi(word);

        ss >> word;
        data.capacity = stoi(word);
    }
    
    int weight;
    int profit;

    for (int i = 0; i < itemCount; i++){
        getline(dataFile, fileLine);
        stringstream ss(fileLine);
        // get item weights
        ss >> word;
        weight = stoi(word);        
        // get item profits
        ss >> word;
        profit = stoi(word);

        Item* currentItem = new Item(itemID++, weight, profit);
        items->insert(currentItem);
    }
    
}

void  KSReading::SD_LoadItems(std::string filepath, KnapsackData& data){
    // not implemented
}