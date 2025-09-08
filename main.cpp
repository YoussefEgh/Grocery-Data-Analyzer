/*
Author: Youssef Elghawabi
Program: This program takes in data about food deserts 
in Chicago and allows the user to search for 
specific grocery stores, find nearest grocery store, 
and analyze the number & size of grocery stores per neighborhood. 
*/

#include <iostream>
#include "classes.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include "distance.h"


using namespace std;

// gets general info for grocery store- number of total stores, large stores, & average size of stores
// stores is a vector of stores used to get info for each store
void generalGrocInfo(vector<Store> stores) {
    int largeStores = 0;
    int validLrgStr = 0;
    double totalSqrFt = 0.0;
    int storesSize = stores.size();
    double averageSize = 0.0;

    // loops through each store to get total number of large stores 
    for (int i = 0; i < stores.size(); ++i) {
        if (stores.at(i).getSize() == "Large") {
            largeStores++;
            totalSqrFt += stod(stores.at(i).getSquareFeet());
            if (stod(stores.at(i).getSquareFeet()) > 0) {
                validLrgStr++;
            }            
        }
    }
        // calculates average size
        averageSize = totalSqrFt/validLrgStr;

    cout << "Number of grocery stores: " << storesSize << endl;
    cout << "Number of large grocery stores: " << largeStores << endl;
    cout << "Average size of large grocery stores: " << fixed << setprecision(1) << averageSize << endl;
    cout << endl;
}

// lists each neighborhood in order of the number of stores & outputs L or S depending on size
// stores is a vector of stores used to get info for each store
void nHoodChart(vector<Store> stores, vector<Neighborhood> nHoods) {

   // counts number of large & small stores in neighborhood
    for (int x = 0; x < nHoods.size(); ++x) {
        for (int y = 0; y < stores.size(); ++y) {
            if (nHoods.at(x).getNHoodName() == stores.at(y).getNeighborhood()) {
                if (stores.at(y).getSize() == "Large") {
                    nHoods.at(x).numLarge++;
                }
                else {
                    nHoods.at(x).numSmall++;
                }
            }
        }
    }

    // insertion sort to alphabetically sort the list
    for (int n = 1; n < nHoods.size(); ++n) {
        int j = n;
        while (j > 0 && nHoods.at(j).getNHoodName() < nHoods.at(j-1).getNHoodName()) {
            Neighborhood temp = nHoods.at(j);
            nHoods.at(j) = nHoods.at(j-1);
            nHoods.at(j-1) = temp;
            --j;
        }
    }

    // insertion sort to sort the list based on number of stores - Greatest to smallest
    for (int n = 1; n < nHoods.size(); ++n) {
        int j = n;
        while (j > 0 && nHoods.at(j).numLarge+nHoods.at(j).numSmall > nHoods.at(j-1).numLarge+nHoods.at(j-1).numSmall) {
            Neighborhood temp = nHoods.at(j);
            nHoods.at(j) = nHoods.at(j-1);
            nHoods.at(j-1) = temp;
            --j;
        }
    }

    // prints each neighborhood with number of large (L) and small stores (S)
    for (int i = 0; i < nHoods.size(); ++i) {
        cout << setfill('L');
        cout << nHoods.at(i).getNHoodName() << " " << setw(nHoods.at(i).numLarge) << "";
        cout << setfill('S');
        cout << setw(nHoods.at(i).numSmall) << "" << endl;        
    }
    cout << endl;
}

// finds closest store to user's chosen point
// stores is a vector of stores used to get info for each store
// outputs the closest store & closest largest store, their distance, & whether it's a food desert 
void findCloseStore(vector<Store> stores) {
    double latitudeInput;
    double longitudeInput;
    double minDistance = 999999999999;
    double minLargeDts = 999999999999;
    string closestStore;
    string closestLrgStr;
    string closestAddress;
    string closestLrgAddress;
    bool foodDesert = true;

    cout << "Enter latitude: ";
    cin >> latitudeInput; 
    cout << "Enter longitude: ";
    cin >> longitudeInput;

    // loops through each store to find closest normal store and closest largest store (minimum distance)
    for (int i = 0; i < stores.size(); ++i) {
        double distanceMiles = distance(latitudeInput, longitudeInput, stod(stores[i].getLatitude()), stod(stores[i].getLongitude()));
        if (distanceMiles < minDistance) {
            minDistance = distanceMiles;
            closestStore = stores[i].getName();
            closestAddress = stores[i].getAddress();
        }
        if (distanceMiles < minLargeDts && stores[i].getSize() == "Large") {
            minLargeDts = distanceMiles;
            closestLrgStr = stores[i].getName();
            closestLrgAddress = stores[i].getAddress();
        }
    }

    cout << "The closest store is " 
    << fixed << setprecision(1) << minDistance 
    << " miles away." << endl;
    cout << "  " << closestStore << " is at " 
    << closestAddress << endl;

    if (closestStore == closestLrgStr) { 
        cout << "That is a large store." << endl;
    }
    else {
        cout << "The closest large store is " 
        << fixed << setprecision(1) << minLargeDts
        << " miles away." << endl;
        cout << "  " << closestLrgStr << " is at " 
        << closestLrgAddress << endl;
        cout << endl;
    }
    if (minDistance <= 0.5 || minLargeDts <= 1) {
        foodDesert = false;
    }
    if (foodDesert) {
        cout << "This location is a food desert." << endl;
    }
}

// outputs information about a given store using user's input- Store name, address, community, size, & sq. feet
// stores is a vector of stores used to get info for each store
void searchStore(vector<Store> stores) {
    string storeInput;
    string tempStr;
    int count = 0;

    cout << "Enter store to search for: ";
    getline(cin, tempStr);
    getline(cin, storeInput);


    for (int x = 0; x < storeInput.size(); ++x) {
        storeInput[x] = toupper(storeInput.at(x));
    }
    // outputs info for user's inputted store
    for (int i = 0; i < stores.size(); ++i) {
        if (stores.at(i).getName().find(storeInput) < 30) {
            cout << "Store: " << stores.at(i).getName() << endl;
            cout << "Address: " << stores.at(i).getAddress() << endl;
            cout << "Community: " << stores.at(i).getNeighborhood() << endl;
            cout << "Size: " << stores.at(i).getSize() << endl;
            cout << "Square Feet: " << stores.at(i).getSquareFeet() << endl;
            ++count;
            cout << endl;
       }
    }
    if (count == 0) {
        cout << "No stores found." << endl;
        cout << endl;
    }
}

int main() {
    ifstream fileIn;
    string filename;
    string storeName;
    string storeSquareFeet;
    string storeSize;
    string storeAddress;
    string storeNeighborhood;
    string storeLatitude;
    string storeLongitude;
    string tempStr;
    int userChoice = 0;
    int count = 0;
    vector<Store> stores;
    vector<Neighborhood> nHoods;

    cout << "Enter filename: ";
    cin >> filename;
    cout << endl;
    fileIn.open(filename);

    // reads each line (store) in the file and store it in a vector of type stores
    while (!fileIn.eof()) { 
        getline(fileIn, storeName, ',');
        getline(fileIn, storeSquareFeet, ',');
        getline(fileIn, storeSize, ',');
        getline(fileIn, storeAddress, ',');
        getline(fileIn, storeNeighborhood, ',');
        getline(fileIn, storeLatitude, ',');
        getline(fileIn, storeLongitude);


        Store Grocery(storeName, storeSquareFeet, storeSize, storeAddress, storeNeighborhood, storeLatitude, storeLongitude);
        stores.push_back(Grocery);

    }

    // stores stores' neighborhoods in vector of class Neighborhood
    for (int x = 0; x < stores.size(); x++) {
        string currNHood = stores.at(x).getNeighborhood();
        for (int y = 0; y < nHoods.size(); ++y) {
            if (currNHood == nHoods.at(y).getNHoodName()) {
                count++;
            }
        }
        if (count == 0) {
            Neighborhood groceryNHood(currNHood);
            nHoods.push_back(groceryNHood);
        }
        count = 0;
    }

    // runs the program until user inputs 5
    while (userChoice != 5) {
        cout << " Select a menu option: " << endl;
        cout << "   1. Display general grocery stores information" << endl;
        cout << "   2. Display neighborhood charts" << endl;
        cout << "   3. Find closest stores" << endl;
        cout << "   4. Search for store by name" << endl;
        cout << "   5. Exit" << endl;
        cout << "Your choice: ";
        cin >> userChoice;


        if (userChoice == 1) {
            generalGrocInfo(stores);
        }
        else if (userChoice == 2) {
            nHoodChart(stores, nHoods);
        }
        else if (userChoice == 3) {
            findCloseStore(stores);
        }
        else if (userChoice == 4) {
            searchStore(stores);
        }
    }
}
