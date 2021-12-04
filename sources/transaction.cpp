#include<iostream>
#include<string>
#include"transaction.h"

using namespace std;

/*transaction::transaction(string names, string namer, long double money, string date, string exp)
{
    set_sender(names);
    set_reciver(namer);
    set_amount(money);
    set_date(date);
    set_explantion(exp);
}

transaction::~transaction()
{

}*/

void transaction::set_sender(std::string name)
{
    sender = name;
}

string transaction::get_sender()
{
    return sender;
}

void transaction::set_reciver(std::string name)
{
    reciver = name;
}

string transaction::get_reciver()
{
    return reciver;
}

void transaction::set_amount(long double money)
{
    amount = money;
}

long double transaction::get_amount()
{
    return amount;
}

void transaction::set_date(std::string date)
{
    this->date = date;
}

string transaction::get_date()
{
    return date;
}

void transaction::set_explantion(std::string exp)
{
    explanation = exp;
}

string transaction::get_explantion()
{
    return explanation;
}
