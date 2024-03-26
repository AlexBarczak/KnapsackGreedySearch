#include <vector>
#include <fstream>

#include "KSReading.h"

using namespace std;

void  KSReading::FSU_LoadItems(std::string filepath, set<Item*>& items){
    int itemID = 0;
    vector<int> weights;
    vector<int> profits;

    string fileLine;
    
    // get item weights
    ifstream dataFile(filepath + "_w.txt");
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
        items.insert(currentItem);

        currentw = next(currentw);
        currentp = next(currentp);
    }
}

void  KSReading::UniCauca_LoadItems(std::string filepath, set<Item*>& items){

}

void  KSReading::SD_LoadItems(std::string filepath, set<Item*>& items){

}