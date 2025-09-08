#include <iostream>
using namespace std;
#pragma once

class Store {
    public:
        Store(string storeName, string storeSquareFeet, string storeSize, string storeAddress, string storeNeighborhood, string storeLatitude, string storeLongitude);
        string getName();
        string getSquareFeet();
        string getSize();
        string getAddress();
        string getNeighborhood();
        string getLatitude();
        string getLongitude();

    private:
        string name;
        string squareFeet;
        string size;
        string address;
        string neighborhood;
        string latitude;
        string longitude;
};

class Neighborhood {
    public:
        Neighborhood(string nHood, int newNumLarge = 0, int newNumSmall = 0);
        string getNHoodName();
        int getNHoodLarge();
        int getNHoodSmall();
        int numLarge;
        int numSmall;
    private:
        string nHoodName;


};

Store::Store(string storeName, string storeSquareFeet, string storeSize, string storeAddress, string storeNeighborhood, string storeLatitude, string storeLongitude) {
    name = storeName;
    squareFeet = storeSquareFeet;
    size = storeSize;
    address = storeAddress;
    neighborhood = storeNeighborhood;
    latitude = storeLatitude;
    longitude = storeLongitude;
}
string Store::getName() {
    return name;
}
string Store::getSquareFeet() {
    return squareFeet;
}
string Store::getSize() {
    return size;
}
string Store::getAddress() {
    return address;
}
string Store::getNeighborhood() {
    return neighborhood;
}
string Store::getLatitude() {
    return latitude;
}
string Store::getLongitude() {
    return longitude;
}

Neighborhood::Neighborhood(string nHood, int newNumLarge, int newNumSmall) {
    nHoodName = nHood;
    numLarge = newNumLarge;
    numSmall = newNumSmall;
}
string Neighborhood::getNHoodName() {
    return nHoodName;
}
int Neighborhood::getNHoodLarge() {
    return numLarge;
}
int Neighborhood::getNHoodSmall() {
    return numSmall;
}