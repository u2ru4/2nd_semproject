#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
using namespace std;

class Expense
{
public:
    string date;
    string expenseName;
    string catg;
    double amount;

    Expense();

    Expense(string d, string n, string c, double a);

    void display() const;

    string toFileString() const;
};

#endif
