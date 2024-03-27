/*
    Author: Aleksander Barczak
    Matric number: 2497555
    AI Project Team 2
*/
#include <vector>
#include <fstream>
#include <sstream>

#include "KSReading.h"

using namespace std;

// function for reading in data from the Florida State University datasets
void  KSReading::FSU_LoadItems(std::string filepath, KnapsackData& data){

    // write the items directly to the data struct
    set<Item*>* items = &(data.items);

    // FSU stores problems details across four file,
    // the p, w, s, and c file corresponding to the profit, weight, solution and capacity
    // each file is read individually and its details stored before we put them into data structures
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

    //  read capacity from file
    getline(dataFile, fileLine);
    //  close the file
    dataFile.close();
    //  convert from string to int
    data.capacity = stoi(fileLine);
    
    // get item weights
    dataFile.open(filepath + "_w.txt");
    while (getline(dataFile, fileLine))
    {
        weights.push_back(stoi(fileLine));   
    }
    dataFile.close();

    // get item utility values
    dataFile.open(filepath + "_p.txt");
    while (getline(dataFile, fileLine))
    {
        profits.push_back(stoi(fileLine));   
    }
    dataFile.close();

    //  compile weight and utility data into data structure
    auto currentw = weights.begin();        
    auto currentp = profits.begin();

    auto endw = weights.end();

    // for each item
    while (currentw != endw)
    {
        // give the item and ID and its corresponding weight and utility
        Item* currentItem = new Item(itemID++, (*currentw), (*currentp));
        items->insert(currentItem);

        // move on to the next values
        currentw = next(currentw);
        currentp = next(currentp);
    }
}

// function for reading in data from the University of Cauca datasets
void  KSReading::UniCauca_LoadItems(std::string filepath, KnapsackData& data){

    // write the items directly to the data struct
    set<Item*>* items = &(data.items);

    int itemID = 0;

    // each line in the 
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
        // read the line into a string stream to separate the words
        stringstream ss(fileLine);

        // get the number of items and convert to int
        ss >> word;
        itemCount = stoi(word);

        // get the capacity of the knapsack and convert to int
        ss >> word;
        data.capacity = stoi(word);
    }
    
    // declare weight and profit variables
    int weight;
    int profit;

    // create each item for each line corresponding to an item in the file
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

// this would have been the implementation of reading in the data from the source by JorikJooken (sources in header file)
// abandoned due to constraints, large datasets being covered by the University of Cauca and also due to some data sets 
// from this source containing floating point values which would require additional logic in developing
void  KSReading::SD_LoadItems(std::string filepath, KnapsackData& data){
    // not implemented
}