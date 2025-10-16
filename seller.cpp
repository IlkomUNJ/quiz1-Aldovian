#include "seller.h"

void Seller::addNewItem(int newId, const string& newName, int newQuantity, double newPrice) {
    Item newItem(newId, newName, newQuantity, newPrice);
    items.push_back(newItem);
    cout << "Item '" << newName << "' berhasil ditambahkan!" << endl;
}

void Seller::updateItem(int itemId, const string& newName, int newQuantity, double newPrice) {
    for (auto& item : items) {
        if (item.getId() == itemId) {
            item.alterItemById(itemId, newName, newQuantity, newPrice);
            cout << "Item dengan ID " << itemId << " berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "Item tidak ditemukan!" << endl;
}

void Seller::showInventory() const {
    cout << "\n=== INVENTORI SELLER ===" << endl;
    if (items.empty()) {
        cout << "Belum ada barang." << endl;
        return;
    }
    for (const auto& item : items) {
        cout << "ID: " << item.getId()
             << " | Nama: " << item.getName()
             << " | Stok: " << item.getQuantity()
             << " | Harga: $" << item.getPrice() << endl;
    }
}
