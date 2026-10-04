#include <iostream>
#include <sstream>
#include "Expense.h"

using namespace std;

Expense::Expense()
{
    date="";
    expenseName="";
    catg="";
    amount=0;
}

Expense::Expense(string d,string n,string c,double a)
{
    date=d;
    expenseName=n;
    catg=c;
    amount=a;
}

void Expense::display() const
{
    cout<<"Date : "<<date<<endl;
    cout<<"Expense : "<<expenseName<<endl;
    cout<<"Category : "<<catg<<endl;
    cout<<"Amount : Rs. "<<amount<<endl;
    cout<<"----------------------------------"<<endl;
}

string Expense::toFileString() const
{
    stringstream ss;

    ss<<date<<","
      <<expenseName<<","
      <<catg<<","
      <<amount;

    return ss.str();
}