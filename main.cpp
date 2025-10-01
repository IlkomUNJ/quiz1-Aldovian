#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"

using namespace std;

enum PrimaryPrompt { LOGIN, REGISTER, EXIT };

vector<BankCustomer*> bankAccounts;
vector<Buyer*> buyers;
int buyerCounter = 1;
int bankCounter = 1;

int main() {
    PrimaryPrompt prompt = LOGIN;
    Buyer* currentBuyer = nullptr;

    while (prompt != EXIT) {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilih: ";
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
        case LOGIN: {
            if (buyers.empty()) {
                cout << "Belum ada akun. Silakan register dulu.\n" << endl;
                break;
            }
            cout << "Masukkan nama untuk login: ";
            string nama;
            cin >> nama;

            bool found = false;
            for (auto& b : buyers) {
                if (b->getName() == nama) {
                    currentBuyer = b;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "User tidak ditemukan.\n" << endl;
                break;
            }

            cout << "Login berhasil sebagai " << currentBuyer->getName() << endl;

            // Sub menu Buyer
            int subChoice = 0;
            while (subChoice != 4) {
                cout << "\n=== Menu Buyer ===" << endl;
                cout << "1. Cek Info Akun" << endl;
                cout << "2. Deposit" << endl;
                cout << "3. Withdraw" << endl;
                cout << "4. Logout" << endl;
                cout << "Pilih: ";
                cin >> subChoice;

                switch (subChoice) {
                case 1:
                    currentBuyer->getAccount().printInfo();
                    break;
                case 2: {
                    double amt;
                    cout << "Jumlah deposit: ";
                    cin >> amt;
                    currentBuyer->getAccount().addBalance(amt);
                    break;
                }
                case 3: {
                    double amt;
                    cout << "Jumlah withdraw: ";
                    cin >> amt;
                    currentBuyer->getAccount().withdrawBalance(amt);
                    break;
                }
                case 4:
                    cout << "Logout berhasil.\n" << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                }
            }
            break;
        }

        case REGISTER: {
            string nama;
            double depositAwal;

            cout << "Masukkan nama: ";
            cin >> nama;
            cout << "Masukkan deposit awal: ";
            cin >> depositAwal;

            BankCustomer* acc = new BankCustomer(bankCounter++, nama, depositAwal);
            bankAccounts.push_back(acc);

            Buyer* newBuyer = new Buyer(buyerCounter++, nama, *acc);
            buyers.push_back(newBuyer);

            cout << "Akun Buyer berhasil dibuat dengan nama: " << nama << "\n" << endl;
            break;
        }

        case EXIT:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Pilihan tidak valid.\n" << endl;
            break;
        }
    }

    for (auto acc : bankAccounts) delete acc;
    for (auto b : buyers) delete b;

    return 0;
}
