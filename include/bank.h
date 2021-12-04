#ifndef _bank
#define _bank

#include"transaction.h"

class bank
{
private:
    unsigned int client = 0;
    long double total_money = 0;
    long double total_loans = 0;
    long double profits_loan = 0;
    long double demands = 0;//motalebat
    bool bankrupt = false;//false = not bankrupt

    unsigned int count_stats = 0;
    
public:
    //bank(/* args */);
    //~bank();
    void set_client();
    unsigned int get_client();

    void set_total_money(long double);
    long double get_total_money();

    void set_total_loans(long double);
    long double get_total_loans();

    void set_profits_loan(long double);
    long double get_profits_loan();

    void set_demands(long double);
    long double get_demands();

    void set_bankrupt(int);
    bool get_bankrupt();

    void print_stats();

    void set_count_stats();
    unsigned int get_count_stats();
    
    std::vector<transaction> stats_bank;
};


#endif