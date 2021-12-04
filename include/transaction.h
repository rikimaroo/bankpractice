#ifndef _transaction
#define _transaction
#include<vector>
#include<string>

class transaction
{
private:
    std::string sender;
    std::string reciver;
    long double amount;
    std::string date;
    std::string explanation;

public:
    //transaction(string, string, long double, string, string);
    //~transaction();

    void set_sender(std::string);
    std::string get_sender();

    void set_reciver(std::string);
    std::string get_reciver();

    void set_amount(long double);
    long double get_amount();

    void set_date(std::string);
    std::string get_date();

    void set_explantion(std::string);
    std::string get_explantion();
};

#endif