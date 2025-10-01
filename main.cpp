#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"

enum PrimaryPrompt { LOGIN, REGISTER, EXIT };

using namespace std;

vector<Buyer> buyers;
int buyerCounter = 1;
int bankCounter = 1;

int main() {
    PrimaryPrompt prompt = LOGIN;
    Buyer* currentBuyer = nullptr;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
        case LOGIN: {
            if (buyers.empty()) {
                cout << "Belum ada akun. Silakan register dulu." << endl;
                break;
            }
            cout << "Masukkan nama untuk login: ";
            string nama;
            cin >> nama;
            bool found = false;
            for (auto& b : buyers) {
                if (b.getName() == nama) {
                    currentBuyer = &b;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "User tidak ditemukan." << endl;
                break;
            }

            cout << "Login berhasil sebagai " << currentBuyer->getName() << endl;

            // Sub menu Buyer
            int subChoice = 0;
            while (subChoice != 5) {
                cout << "\n=== Menu Buyer ===" << endl;
                cout << "1. Cek Info Akun" << endl;
                cout << "2. Buat Akun Bank" << endl;
                cout << "3. Deposit" << endl;
                cout << "4. Withdraw" << endl;
                cout << "5. Logout" << endl;
                cin >> subChoice;

                switch (subChoice) {
                case 1:
                    currentBuyer->showBuyerInfo();
                    break;
                case 2: {
                    if (currentBuyer->getBankAccount() != nullptr) {
                        cout << "Sudah punya akun bank." << endl;
                        break;
                    }
                    string address, phone, email;
                    double initialDeposit;
                    cout << "Alamat: "; cin >> address;
                    cout << "HP: "; cin >> phone;
                    cout << "Email: "; cin >> email;
                    cout << "Deposit awal: "; cin >> initialDeposit;
                    BankCustomer* acc = new BankCustomer(bankCounter++, currentBuyer->getName(), address, phone, email, initialDeposit);
                    currentBuyer->linkBankAccount(acc);
                    break;
                }
                case 3: {
                    if (currentBuyer->getBankAccount() == nullptr) {
                        cout << "Belum punya akun bank!" << endl;
                        break;
                    }
                    double amt;
                    cout << "Jumlah deposit: "; cin >> amt;
                    currentBuyer->getBankAccount()->deposit(amt);
                    break;
                }
                case 4: {
                    if (currentBuyer->getBankAccount() == nullptr) {
                        cout << "Belum punya akun bank!" << endl;
                        break;
                    }
                    double amt;
                    cout << "Jumlah withdraw: "; cin >> amt;
                    currentBuyer->getBankAccount()->withdraw(amt);
                    break;
                }
                case 5:
                    cout << "Logout berhasil." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                }
            }

            break;
        }

        case REGISTER: {
            string nama;
            cout << "Masukkan nama: ";
            cin >> nama;
            buyers.push_back(Buyer(buyerCounter++, nama));
            cout << "Akun Buyer berhasil dibuat dengan nama: " << nama << endl;
            break;
        }

        case EXIT:
            cout << "Exiting." << endl;
            break;

        default:
            cout << "Invalid option." << endl;
            break;
        }
        cout << endl;
    }

    return 0;
}
