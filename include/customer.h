#ifndef _customer
#define _customer

#include<string>
#include<vector>
#include"bank.h"
#include"transaction.h"

class customer
{
private:
    std::string username;
    unsigned int card_number;
    std::string opening;
    std::string expiration;
    long double money = 0;//deposit
    long double loan = 0;
    //int tournover;
    std::string date_profit = "0";
    std::vector<std::string> ip;
public:
    //customer(/* args */);
    //~customer();

    void set_username(std::string);
    std::string get_username();

    void set_ip(std::string);
    std::string get_ip(int);
    int get_ip_size();

    void set_card_number();
    unsigned int get_card_number();

    void set_opening();
    std::string get_opening();

    void set_expiration();
    std::string get_expiration();

    void set_money(long double);
    long double get_money();

    void set_loan(long double);
    long double get_loan();

    void set_date_profit(std::string);
    std::string get_day_profit();

    void print_infomation();
    
    std::vector<transaction *> stats_customer;
};


#endif