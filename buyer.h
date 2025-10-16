#ifndef BUYER_H
#define BUYER_H

#include <string>
#include "bank_customer.h"
using namespace std;

class Buyer {
private:
    int id;
    string name;
    BankCustomer &account;

public:
    Buyer(int id, const string& name, BankCustomer &account0)
        : id(id), name(name), account(account0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    BankCustomer& getAccount() { return account; }

    void setId(int newId) { id = newId; }
    void setName(const string& newName) { name = newName; }
};

#endif
