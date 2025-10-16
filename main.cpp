#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"
using namespace std;

enum PrimaryPrompt { LOGIN, REGISTER, EXIT };

vector<BankCustomer*> bankAccounts;
vector<Buyer*> buyers;
vector<Seller*> sellers;
int buyerCounter = 1;
int bankCounter = 1;
int sellerCounter = 1;

int main() {
    PrimaryPrompt prompt = LOGIN;
    Buyer* currentBuyer = nullptr;
    Seller* currentSeller = nullptr;

    while (prompt != EXIT) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Login sebagai Buyer\n";
        cout << "2. Register Buyer\n";
        cout << "3. Login sebagai Seller\n";
        cout << "4. Exit\n";
        cout << "Pilih: ";

        int choice;
        cin >> choice;

        if (choice == 4) { prompt = EXIT; break; }

        switch (choice) {
        case 1: {
            string nama;
            cout << "Masukkan nama Buyer: ";
            cin >> nama;

            for (auto& b : buyers) {
                if (b->getName() == nama) {
                    currentBuyer = b;
                    cout << "Login berhasil sebagai Buyer: " << nama << endl;
                    break;
                }
            }

            if (!currentBuyer) {
                cout << "Buyer tidak ditemukan!\n";
                break;
            }

            int sub;
            do {
                cout << "\n=== Menu Buyer ===\n";
                cout << "1. Lihat Info Akun\n2. Deposit\n3. Withdraw\n4. Logout\nPilih: ";
                cin >> sub;
                switch (sub) {
                    case 1: currentBuyer->getAccount().printInfo(); break;
                    case 2: {
                        double amt; cout << "Jumlah deposit: "; cin >> amt;
                        currentBuyer->getAccount().addBalance(amt); break;
                    }
                    case 3: {
                        double amt; cout << "Jumlah withdraw: "; cin >> amt;
                        currentBuyer->getAccount().withdrawBalance(amt); break;
                    }
                }
            } while (sub != 4);
            currentBuyer = nullptr;
            break;
        }

        case 2: {
            string nama; double deposit;
            cout << "Masukkan nama Buyer: ";
            cin >> nama;
            cout << "Deposit awal: ";
            cin >> deposit;

            auto* acc = new BankCustomer(bankCounter++, nama, deposit);
            auto* newBuyer = new Buyer(buyerCounter++, nama, *acc);

            bankAccounts.push_back(acc);
            buyers.push_back(newBuyer);

            cout << "Akun Buyer berhasil dibuat!\n";
            break;
        }

        case 3: {
            if (buyers.empty()) {
                cout << "Buat akun Buyer dulu sebelum jadi Seller!\n";
                break;
            }
            string nama;
            cout << "Masukkan nama Buyer untuk jadi Seller: ";
            cin >> nama;

            Buyer* buyerFound = nullptr;
            for (auto& b : buyers) {
                if (b->getName() == nama) { buyerFound = b; break; }
            }

            if (!buyerFound) {
                cout << "Buyer tidak ditemukan!\n";
                break;
            }

            auto* newSeller = new Seller(*buyerFound, sellerCounter++, nama);
            sellers.push_back(newSeller);
            currentSeller = newSeller;
            cout << "Login sebagai Seller berhasil!\n";

            int sub;
            do {
                cout << "\n=== Menu Seller ===\n";
                cout << "1. Tambah Item\n2. Lihat Inventori\n3. Update Item\n4. Logout\nPilih: ";
                cin >> sub;

                switch (sub) {
                    case 1: {
                        int id, qty; double price; string itemName;
                        cout << "Nama item: "; cin >> itemName;
                        cout << "ID: "; cin >> id;
                        cout << "Stok: "; cin >> qty;
                        cout << "Harga: "; cin >> price;
                        currentSeller->addNewItem(id, itemName, qty, price);
                        break;
                    }
                    case 2: currentSeller->showInventory(); break;
                    case 3: {
                        int id, qty; double price; string itemName;
                        cout << "Masukkan ID item yang ingin diupdate: "; cin >> id;
                        cout << "Nama baru: "; cin >> itemName;
                        cout << "Stok baru: "; cin >> qty;
                        cout << "Harga baru: "; cin >> price;
                        currentSeller->updateItem(id, itemName, qty, price);
                        break;
                    }
                }
            } while (sub != 4);
            currentSeller = nullptr;
            break;
        }

        default:
            cout << "Pilihan tidak valid!\n";
        }
    }

    for (auto acc : bankAccounts) delete acc;
    for (auto b : buyers) delete b;
    for (auto s : sellers) delete s;

    cout << "Program selesai." << endl;
    return 0;
}
