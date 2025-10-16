#pragma once
#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Seller : public Buyer {
private:
    int sellerId;
    string sellerName;
    vector<Item> items;

public:
    Seller(Buyer buyer, int sellerId, const string& sellerName)
        : Buyer(buyer.getId(), buyer.getName(), buyer.getAccount()),
          sellerId(sellerId), sellerName(sellerName) {}

    void addNewItem(int newId, const string& newName, int newQuantity, double newPrice);
    void updateItem(int itemId, const string& newName, int newQuantity, double newPrice);
    void showInventory() const;
};
