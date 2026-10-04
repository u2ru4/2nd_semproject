#ifndef TRACKER_H
#define TRACKER_H

#include "Expense.h"
#include <vector>

using namespace std;

class Tracker
{
private:

    vector<Expense> expenses;

public:

    void showMenu();
    void addExpense();
    void viewAllExpenses();
    void viewTodayExpenses();
    void dailyTotal();
    string getTodayDate();
    void searchExpense();
    void deleteExpense();
    void categoryReport();
    void highestExpense();
    void lowestExpense();
    Expense readExpense(string line);
    void start();
};

#endif