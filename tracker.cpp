#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "Tracker.h"

using namespace std;

// Returns today's date
string Tracker::getTodayDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_string(ltm->tm_mday) + "-" +
           to_string(ltm->tm_mon + 1) + "-" +
           to_string(1900 + ltm->tm_year);
}
Expense Tracker::readExpense(string line)
{
    Expense e;

    stringstream ss(line);

    getline(ss, e.date, ',');
    getline(ss, e.expenseName, ',');
    getline(ss, e.catg, ',');

    string amount;
    getline(ss, amount);

    e.amount = stod(amount);

    return e;
}
// Displays the menu
void Tracker::showMenu()
{
    cout << "\n=====================================\n";
    cout << "      PERSONAL EXPENSE TRACKER\n";
    cout << "=====================================\n";
    cout << "Today's Date : " << getTodayDate() << endl;

    cout << "\n1. Add Expense";
    cout << "\n2. View Today's Expenses";
    cout << "\n3. View All Expenses";
    cout << "\n4. Daily Total";
    cout << "\n5. Search Expense";
    cout << "\n6. Delete Expense";
    cout << "\n7. Category Report";
    cout << "\n8. Highest Expense";
    cout << "\n9. Lowest Expense";
    cout << "\n10. Exit";

    cout << "\n\nEnter Choice : ";
}

// Adds an expense
void Tracker::addExpense()
{
    Expense e;

    e.date = getTodayDate();

    cin.ignore();

    cout << "\nExpense Name : ";
    getline(cin, e.expenseName);

    cout << "Category : ";
    getline(cin, e.catg);

    cout << "Amount : ";
    cin >> e.amount;

    ofstream file("expenses.txt", ios::app);

    file << e.toFileString() << endl;

    file.close();

    cout << "\nExpense Saved Successfully!\n";
}

// Displays all expenses
void Tracker::viewAllExpenses()
{
    ifstream file("expenses.txt");

    if (!file)
    {
        cout << "\nNo expenses found.\n";
        return;
    }

    string line;

    cout << "\n=========================================================\n";
    cout << left << setw(15) << "Date"
         << setw(20) << "Expense"
         << setw(15) << "Category"
         << "Amount\n";
    cout << "=========================================================\n";

    while (getline(file, line))
    {
       Expense e = readExpense(line);

       cout << left
            << setw(15) << e.date
            << setw(20) << e.expenseName
            << setw(15) << e.catg
            << e.amount << endl;
    }

    file.close();
}

// Shows today's expenses
void Tracker::viewTodayExpenses()
{
    ifstream file("expenses.txt");

    string today = getTodayDate();
    string line;
    bool found = false;

    cout << "\n========== TODAY'S EXPENSES ==========\n";

    while (getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        if (d == today)
        {
            found = true;

            cout << left
                 << setw(20) << n
                 << setw(15) << c
                 << "Rs. " << a << endl;
        }
    }

    if (!found)
    {
        cout << "No expenses for today.\n";
    }

    file.close();
}

// Calculates today's total
void Tracker::dailyTotal()
{
    ifstream file("expenses.txt");

    string today = getTodayDate();
    string line;

    double total = 0;

    while (getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        if (d == today)
        {
            total += stod(a);
        }
    }

    file.close();

    cout << "\nToday's Total Spending : Rs. " << total << endl;
}
// Search Expense
void Tracker::searchExpense()
{
    ifstream file("expenses.txt");

    if (!file)
    {
        cout << "\nNo expense records found.\n";
        return;
    }

    string searchName;

    cin.ignore();

    cout << "\nEnter Expense Name : ";
    getline(cin, searchName);

    string line;
    bool found = false;

    cout << "\n================ SEARCH RESULT ================\n";

    while (getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        if (n == searchName)
        {
            found = true;

            cout << "Date      : " << d << endl;
            cout << "Expense   : " << n << endl;
            cout << "Category  : " << c << endl;
            cout << "Amount    : Rs. " << a << endl;
            cout << "----------------------------------------\n";
        }
    }

    if (!found)
    {
        cout << "Expense not found.\n";
    }

    file.close();
}
void Tracker::deleteExpense()
{
    ifstream file("expenses.txt");

    if (!file)
    {
        cout << "\nNo expense records found.\n";
        return;
    }

    ofstream temp("temp.txt");

    string searchName;

    cin.ignore(1000, '\n');

    cout << "\nEnter Expense Name to Delete: ";
    getline(cin, searchName);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        if (n == searchName)
        {
            found = true;
            continue;      // Skip this record (delete it)
        }

        temp << d << "," << n << "," << c << "," << a << endl;
    }

    file.close();
    temp.close();

    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    if (found)
        cout << "\nExpense Deleted Successfully!\n";
    else
        cout << "\nExpense Not Found!\n";
}
void Tracker::categoryReport()
{
    ifstream file("expenses.txt");

    if (!file)
    {
        cout << "\nNo expense records found.\n";
        return;
    }

    double food = 0;
    double transport = 0;
    double shopping = 0;
    double bills = 0;
    double entertainment = 0;
    double others = 0;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        double amount = stod(a);

        if (c == "Food")
            food += amount;
        else if (c == "Transport")
            transport += amount;
        else if (c == "Shopping")
            shopping += amount;
        else if (c == "Bills")
            bills += amount;
        else if (c == "Entertainment")
            entertainment += amount;
        else
            others += amount;
    }

    file.close();

    cout << "\n========== CATEGORY REPORT ==========\n";
    cout << "Food           : Rs. " << food << endl;
    cout << "Transport      : Rs. " << transport << endl;
    cout << "Shopping       : Rs. " << shopping << endl;
    cout << "Bills          : Rs. " << bills << endl;
    cout << "Entertainment  : Rs. " << entertainment << endl;
    cout << "Others         : Rs. " << others << endl;
}
void Tracker::highestExpense()
{
    ifstream file("expenses.txt");

    if(!file)
    {
        cout<<"\nNo expense records found.\n";
        return;
    }

    string line;

    string maxDate;
    string maxName;
    string maxCategory;

    double maxAmount = -1;

    while(getline(file,line))
    {
       Expense e = readExpense(line);

       if(e.amount > maxAmount)
       {
          maxAmount = e.amount;
          maxDate = e.date;
          maxName = e.expenseName;
          maxCategory = e.catg;
       }
    }

    file.close();

    if(maxAmount==-1)
    {
        cout<<"No data available.\n";
        return;
    }

    cout<<"\n========== HIGHEST EXPENSE ==========\n";

    cout<<"Date      : "<<maxDate<<endl;
    cout<<"Expense   : "<<maxName<<endl;
    cout<<"Category  : "<<maxCategory<<endl;
    cout<<"Amount    : Rs. "<<maxAmount<<endl;
}
void Tracker::lowestExpense()
{
    ifstream file("expenses.txt");

    if(!file)
    {
        cout << "\nNo expense records found.\n";
        return;
    }

    string line;

    string minDate;
    string minName;
    string minCategory;

    double minAmount = 999999999;

    while(getline(file, line))
    {
        stringstream ss(line);

        string d, n, c, a;

        getline(ss, d, ',');
        getline(ss, n, ',');
        getline(ss, c, ',');
        getline(ss, a);

        double amount = stod(a);

        if(amount < minAmount)
        {
            minAmount = amount;
            minDate = d;
            minName = n;
            minCategory = c;
        }
    }

    file.close();

    if(minAmount == 999999999)
    {
        cout << "No data available.\n";
        return;
    }

    cout << "\n========== LOWEST EXPENSE ==========\n";

    cout << "Date      : " << minDate << endl;
    cout << "Expense   : " << minName << endl;
    cout << "Category  : " << minCategory << endl;
    cout << "Amount    : Rs. " << minAmount << endl;
}
// Main Program Loop
void Tracker::start()
{
    int choice;

    do
    {
        showMenu();

       if (!(cin >> choice))
       {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Invalid input!\n";
          continue;
      }


    switch(choice)

       {
        case 1:
        addExpense();
        break;

        case 2:
        viewTodayExpenses();
        break;

        case 3:

        viewAllExpenses();
        break;

        case 4:
        dailyTotal();
        break;

        case 5:
        searchExpense();
        break;

        case 6:
        deleteExpense();
        break;

        case 7:
        categoryReport();
        break;



        case 8:
        highestExpense();
        break;


        case 9:
        lowestExpense();
        break;

        case 10:
        cout << "\nThank you for using Personal Expense Tracker.\n";
        break;

        default:
        cout << "\nInvalid Choice!\n";
        }
    } while(choice != 10);
}