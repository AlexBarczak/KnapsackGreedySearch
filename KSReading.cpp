#include <vector>
#include <fstream>

#include "KSReading.h"

using namespace std;

void  KSReading::FSU_LoadItems(std::string filepath, KnapsackData& data){

    set<Item*>* items = &(data.items);

    int itemID = 0;
    vector<int> weights;
    vector<int> profits;

    string fileLine;

    // get capacity
    cout << "filepath: " << filepath + "_c.txt" << endl;
    ifstream dataFile(filepath + "_c.txt");

    if(dataFile.fail()){
        cout << "file not found" << endl;
        throw new exception();
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

}

void  KSReading::SD_LoadItems(std::string filepath, KnapsackData& data){

}