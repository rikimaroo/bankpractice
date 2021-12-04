#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<bits/stdc++.h>
#include"customer.h"
#include"bank.h"
#include"transaction.h"
#include"function.h"

using namespace std;

int main()
{
    cout << "welocome" << endl;
    unsigned int count = 0;
    bank pro;
    vector <customer> owner(2);//tempelate
    string get;
    getline(cin, get, ' ');
    transform(get.begin(), get.end(), get.begin(), ::tolower); //lower case string

    while (get != "exit")
    {
        if (get == "create")
        {
            create();
        }
        else if (get == "add_ip" || get == "add-ip")
        {
            add_ip();
        }
        else if (get == "renewal")
        {
            renewal();
        }
        else if (get == "desposit")
        {
            desposit();
        }
        else if (get == "transfer")
        {
            transfer();
        }
        else if (get == "withdraw")
        {
            withdraw();
        }
        else if (get == "add_profit" || get == "add-profit")
        {
            add_profit();
        }
        else if (get == "get_loan" || get == "get-loan")
        {
            get_loan();
        }
        else if (get == "pay_loan" || get == "pay-loan")
        {
            pay_loan();
        }
        else if (get == "bank")
        {
            info_bank();
        }
        else if (get == "report")
        {
            report();
        }
        else if (get == "help")
        {
            help();
        }
        else if (isdigit(get[0]))
        {
            info_naccount(get);
        }
        else if (isalpha(get[0]))
        {
            info_aaccount(get);
        }
        else
        {
            cout << "your request is not valid" << endl;
        }

        cout << "in count akhar hast:" << count << endl;
        cout << pro.get_count_stats() << endl;
        for (size_t i = count; i < pro.get_count_stats(); i++, count++)//save transaction information in account
        {
            for (size_t j = 0; j < owner.size(); j++)
            {
                if (pro.stats_bank[i].get_sender() == owner[j].get_username() 
                                                    || pro.stats_bank[i].get_reciver() == owner[j].get_username())
                {
                    cout << "in akhar main miad?" << endl;
                    transaction * temp = &pro.stats_bank[i];
                    owner[j].stats_customer.push_back(temp);
                }
                
            }
           
        }
        

        fflush(stdin);
        getline(cin, get, ' ');
        transform(get.begin(), get.end(), get.begin(), ::tolower); //lower case string
    }

    return 0;
}