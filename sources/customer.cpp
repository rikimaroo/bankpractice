#include<iostream>
#include<string>
#include<string.h>//strtok
#include<exception>
#include<stdlib.h>
#include<time.h>
#include<random>
#include"customer.h"

using namespace std;

void customer::set_username(string name)
{
    if (isdigit(name[0]))
    {
        throw invalid_argument("invalid username, because the username start with a number");
    }
    
    username = name;
}

string customer::get_username()
{
    return username;
}

void customer::set_ip(string user_ip)
{
    char copy_ip[20];
    user_ip.copy(copy_ip, user_ip.size());
    char *temps;
    int tempi;

    temps = strtok(copy_ip, ".");//separate part one user_ip

    while (temps != NULL)
    {
        tempi = atoi(temps);
        if (tempi > 255)
        {
            throw invalid_argument("invalid ip");
        }

        temps = strtok(NULL, ".");//separate another part user_ip
    }

    ip.push_back(user_ip);

    ip.shrink_to_fit();//optimization
}

string customer::get_ip(int num)
{
    return ip[num];  
}

int customer::get_ip_size()
{
    return ip.size();
}

void customer::set_card_number()
{
    mt19937 mt(time(NULL));
    card_number = (mt() % 10000) + 1;
}

unsigned int customer::get_card_number()
{
    return card_number;
}

void customer::set_opening()
{
    time_t temp = time(NULL);//get time now
    tm *now = localtime(&temp);
    string op = to_string(now->tm_year+1900) + ".";//get year now
    op += to_string(now->tm_mon+1) + ".";//get month
    op += to_string(now->tm_mday);//get day

    opening = op;
}

string customer::get_opening()
{
    return opening;
}

void customer::set_expiration()
{
    /*string data_open = get_opening();
    char copp[100];
    data_open.copy(copp, data_open.size());
    char *temps;
    int tempi;
    temps = strtok(copp, ".");//get year
    tempi = atoi(temps);
    tempi += 2;

    string exp;
    exp = to_string(tempi);
    exp += ".";
    temps = strtok(NULL, ".");//get month
    exp += temps;
    exp += ".";
    temps = strtok(NULL, "\n");//get day
    exp += temps;*/

    time_t temp = time(NULL);
    tm * now = localtime(&temp);

    string exp = to_string(now->tm_year+1900+2) + ".";
    exp += to_string(now->tm_mon+1) + ".";
    exp += to_string(now->tm_mday);

    expiration = exp;
}

string customer::get_expiration()
{
    return expiration;
}

void customer::set_money(long double money)
{
    long double residual;
    residual = (get_money() + money);//residual account money and sum or Submission 

    this->money = residual;
}

long double customer::get_money()
{
    return money;
}

void customer::set_loan(long double loan)
{
    long double residual = get_loan();
    residual += loan;

    this->loan = residual;
}

long double customer::get_loan()
{
    return loan;
}

void customer::set_date_profit(string date)
{
    date_profit = date;
}

string customer::get_day_profit()
{
    return date_profit;
}

void customer::print_infomation()
{
        cout << "name is:" << get_username() << endl;
        cout << "list of IPs..." << endl;
        for (size_t j = 0; j < get_ip_size(); j++)
        {
            cout << get_ip(j) << "\t";

            if (j % 4 == 0)
            {
                cout << endl;
            }
        }

        cout << endl << "cardnumber is:" << get_money() << endl
             << "money is:" << get_money() << endl
             << "data opening account is:" << get_opening() << endl
             << "data expiration is:" << get_expiration() << endl
             << "debtor for the loan:" << get_loan() << endl
             << "-----------------------------------" << endl;
    
}