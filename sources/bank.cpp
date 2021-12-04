#include<iostream>
#include<string>
#include"bank.h"

using namespace std;

void bank::set_client()
{
    client++;
}

unsigned int bank::get_client()
{
    return client;
}

void bank::set_total_money(long double money)
{
    long double residual = get_total_money();//residual account money
    residual += money;//sum or Submission 

    total_money = money;
}

long double bank::get_total_money()
{
    return total_money;
}

void bank::set_total_loans(long double money)
{
    long double temp = get_total_loans();
    temp += money;

    total_loans = temp;
}

long double bank::get_total_loans()
{
    return total_loans;
}

void bank::set_profits_loan(long double profit)
{
    long double temp = get_profits_loan();
    temp += profit;

    profits_loan = temp;
}

long double bank::get_profits_loan()
{
    return profits_loan;
}

void bank::set_demands(long double deman)
{
    long double temp = get_demands();
    temp += deman;

    demands = temp;
}

long double bank::get_demands()
{
    return demands;
}

void bank::set_bankrupt(int rupt)
{
    if (rupt == 0)
    {
        bankrupt = true;
    }
    else
    {
        bankrupt = false;
    }
}

bool bank::get_bankrupt()
{
    return bankrupt;
}

void bank::print_stats()
{
    cout << "number of customers:" << get_client() << endl
         << "the total amount of money:" << get_total_money() << endl
         << "the total amount of loans given:" << get_total_loans() << endl
         << "the total amount of outstanding loans:" << get_demands() << endl
         << "the total amount of profit loans:" << get_profits_loan() << endl
         << "bank status:";
         if (get_bankrupt())
            cout << "bankrupt" << endl;
         else
            cout << "normal" << endl;
         
        cout << "-----------------------------------" << endl;
}

void bank::set_count_stats()
{
    count_stats++;
}

unsigned int bank::get_count_stats()
{
    return count_stats;
}