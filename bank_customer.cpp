#include "bank_customer.h"
#include <iostream>
using namespace std;

string BankCustomer::getName() const { return name; }
int BankCustomer::getId() const { return id; }
double BankCustomer::getBalance() const { return balance; }

void BankCustomer::setBalance(double amount) { balance = amount; }

void BankCustomer::addBalance(double amount) { balance += amount; }

bool BankCustomer::withdrawBalance(double amount) {
    if (amount > balance) {
        cout << "Rejected: Insufficient funds!" << endl;
        return false;
    }
    balance -= amount;
    return true;
}

void BankCustomer::printInfo() const {
    cout << "Customer Name: " << name << endl;
    cout << "Customer ID: " << id << endl;
    cout << "Balance: $" << balance << endl;
}
