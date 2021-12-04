#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include"function.h"
#include"customer.h"
#include"bank.h"
#include"transaction.h"

using namespace std;

string time_now()
{
    time_t temp = time(NULL);//get time now
    tm *now = localtime(&temp);

    string data = to_string(now->tm_year+1900) + ".";//get year now
    data += to_string(now->tm_mon+1) + ".";//get month
    data += to_string(now->tm_mday);//get day

    return data;
}

bank pro;
vector <customer> owner(2);//tempelate

void help()
{
    cout << "defined commands...." << endl
         << "opening new account  --->  (create) username:ip" << endl
         << "add new ip  --->  (add_ip) username:new_ip" << endl
         << "renewal account  --->  (renewal) username:ip" << endl//chekesh kon age vaght shod
         << "desposit money to account  --->  (desposit) username:ip:money" << endl
         << "transfer money to another account  --->  (transfer) sender_username:sender_ip:reciver username or ip:money" << endl
         << "withraw money from the account  --->  (withdraw) username:ip:money" << endl
         << "add profit  --->  (add_profit) username" << endl
         << "getting loan  --->  (get_loan) username:ip:money" << endl
         << "pay the loan  --->  (pay_loan) username:money" << endl
         << "view 5recent transactions  --->  (report) username" << endl
         << "print account information  --->  (username) or (ip) or (card number)" << endl//dastor ra ba space vared konid 
         << "print bank information  --->  (bank)" << endl;//dastor ra ba space vared konid 
         
}

void create()
{
    if (owner.size() == pro.get_client())//resize vector if compelet vector
    {
        owner.resize(owner.size()+5);
    }

    string user;
    getline(cin, user, ':');//get user name

    string ip_user;
    getline(cin, ip_user);//get user ip
    
    bool use = false;//used username and ip before date, or no

    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }

        if (owner[i].get_username() == user)//chek username duplicate
        {
            cout << "warning: this name has been used before please try again with another name";
            use = true;
            break;
        }

        for (size_t j = 0; j < owner[i].get_ip_size(); j++)//chek ip duplicate
        {
            if (owner[i].get_ip(j) == ip_user)
            {
                cout << "this ip has been user before please try again with another ip";
                use = true;
                break;
            }
        }
        if (use)
        {
            break;
        }

    }
        
    if (!use)
    {
        bool flag = false;
        while (!flag)
        {
            flag = true;
            try
            {
                owner[pro.get_client()].set_username(user);//set username
            }
            catch(invalid_argument &pm)
            {
                cerr << pm.what() << endl;
                
                cout << "please try again enter a username--->";
                getline(cin, user);
                flag = false;
            }
        }
        
        flag = false;

        while (!flag)
        {
            flag = true;
            try
            {
                owner[pro.get_client()].set_ip(ip_user);//set ip
            }
            catch(invalid_argument &pm)
            {
                cerr << pm.what() << endl;
                
                cout << "please try again enter a ip--->";
                getline(cin, ip_user);
                flag = false;
            }
        }
        
        owner[pro.get_client()].set_card_number();//set card number
        for (size_t i = 0; i < owner.size(); i++)//chek card number for not deplicate
        {
            if (i == pro.get_client())
            {
                continue;
            }
            
            //cout << "inja?" << endl;
            if (owner[i].get_card_number() == owner[pro.get_client()].get_card_number())
            {
                owner[pro.get_client()].set_card_number();//change cardnumber
                i = -1;
            }
            
        }
        
        owner[pro.get_client()].set_opening();//set date opening account
        owner[pro.get_client()].set_expiration();//set data expiration account

        pro.set_client();//increse client bank

        cout << "create account is successfully" << endl;
    }              
}

void add_ip()
{
    string username;
    getline(cin, username, ':');

    string new_ip;
    getline(cin, new_ip);

    bool chek_name = false;
    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }

        if (owner[i].get_username() == username)
        {
            chek_name = true;
            bool repet = false;
            for (size_t j = 0; j < owner[i].get_ip_size() && !repet; j++)
            {
                if (owner[i].get_ip(j) == new_ip)
                {
                    repet = true;
                    cout << "this ip is available for this account" << endl;
                    break;
                }
                
            }
            if (!repet)
            {
                try
                {
                    owner[i].set_ip(new_ip);
                    cout << "ip added" << endl;
                }
                catch(invalid_argument &pm)
                {
                    std::cerr << pm.what() << endl;
                }
                    
            }
        }

        if (!chek_name)
        {
            cout << "this username has not been created in the bank account !!!" << endl;
        }

    }
    
}

void renewal()
{
    string username;
    getline(cin, username, ':');

    string ip;
    getline(cin, ip);

    char confirm = ' ';
    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }

        string data = time_now();

        if (owner[i].get_username() == username)
        {
            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == ip)
                {
                    if (data > owner[i].get_expiration())
                    {
                        cout << "this account has expiration" << endl;
                        cout << "your account balance is:" << owner[i].get_money() << endl;
                        cout << "(renewal account for 2 year cost is 2$), do you sure renewal account? (Y/N)--->";
                        cin >> confirm;
                    }
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        if (owner[i].get_money() >= 2)
                        {
                            owner[i].set_money(-2);
                            owner[i].set_expiration();//az har zamani ke aghdam be tamdid 
                                                            //kone 2sal afzode mishe

                            {//compelet information for report (class transaction)
                                pro.stats_bank[pro.get_count_stats()].set_sender(username);
                                pro.stats_bank[pro.get_count_stats()].set_reciver("...");
                                pro.stats_bank[pro.get_count_stats()].set_amount(2);
                                pro.stats_bank[pro.get_count_stats()].set_date(data);
                                pro.stats_bank[pro.get_count_stats()].set_explantion("renewal");

                                pro.set_count_stats();//increase count stats
                            }

                            break;
                        }
                        else
                        {
                            cout << "this account balance is less than 2$" << endl;

                            long double mod = 2 - owner[i].get_money();//get money for given loan
                            owner[i].set_money(-(owner[i].get_money()));//account balance equal 0

                            if (pro.get_total_money() > 2)
                            {//profit loan = 20%
                                owner[i].set_loan(mod + (mod * 0.2));//set loan for account

                                pro.set_demands(mod);//set and increase demands 
                                pro.set_total_loans(mod);//save loan in bank
                                pro.set_profits_loan(mod*0.2);//save profit loan in bank
                            }
                            else
                            {
                                cout << "The bank can not lend as much" << endl;
                            }
                            break;
                        }

                    }
                    else
                    {
                        cout << "your account has not yet expired" << endl;
                        cout << "do you sure renewal account??? (Y/N)--->";
                        cin >> confirm;

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            if (owner[i].get_money() >= 2)
                            {
                                owner[i].set_money(-2);
                                owner[i].set_expiration();//az har zamani ke aghdam be tamdid 
                                                                //kone 2sal afzode mishe

                                {//compelet information for report (class transaction)
                                    pro.stats_bank[pro.get_count_stats()].set_sender(username);
                                    pro.stats_bank[pro.get_count_stats()].set_reciver("...");
                                    pro.stats_bank[pro.get_count_stats()].set_amount(2);
                                    pro.stats_bank[pro.get_count_stats()].set_date(data);
                                    pro.stats_bank[pro.get_count_stats()].set_explantion("renewal");

                                    pro.set_count_stats();//increase count stats
                                }

                                break;
                            }
                            else
                            {
                                cout << "this account balance is less than 2$" << endl;

                                long double mod = 2 - owner[i].get_money();//get money for given loan
                                owner[i].set_money(-(owner[i].get_money()));//account balance equal 0

                                if (pro.get_total_money() > 2)
                                {//profit loan = 20%
                                    owner[i].set_loan(mod + (mod * 0.2));//set loan for account

                                    pro.set_demands(mod);//set and increase demands 
                                    pro.set_total_loans(mod);//save loan in bank
                                    pro.set_profits_loan(mod*0.2);//save profit loan in bank
                                }
                                else
                                {
                                    cout << "The bank can not lend as much" << endl;
                                }
                                break;
                            }
                        }
                        
                    }
                    if(confirm == 'n' || confirm == 'N')
                    {
                        break;
                    }
                    
                }
                
            }
            
        }
        if(confirm == 'n' || confirm == 'N')
        {
            break;
        }
        
    }
}

void desposit()
{

    if (pro.stats_bank.size() == pro.get_count_stats())//resize vector if compelet vector
    {
        pro.stats_bank.resize(pro.stats_bank.size()+5);
    }

    string username;
    getline(cin, username, ':');//get username

    string ip;
    getline(cin, ip, ':');//get ip

    string temp;
    getline(cin, temp);//get money
    long double currency = stold(temp);

    while (currency < 0)//chek currency
    {
        cout << "the amount given is not valid, enter the correct amount--->";
        getline(cin, temp); 
        currency = stold(temp);
    }

    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }

        if (owner[i].get_username() == username)//chek username
        {
            string data = time_now();
            if (data > owner[i].get_expiration())//chek expiration account
            {
                cout << data << endl << owner[i].get_expiration() << endl;
                cout << "this account has expiration please renwal account" << endl;
                break;
            }

            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == ip)
                {
                    owner[i].set_money(currency);//increase account balance
                    pro.set_total_money(currency);//increase bank balance
                    
                    {//compelet information for report (class transaction)
                        pro.stats_bank[pro.get_count_stats()].set_sender(username);
                        pro.stats_bank[pro.get_count_stats()].set_reciver("...");
                        pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                        pro.stats_bank[pro.get_count_stats()].set_date(data);
                        pro.stats_bank[pro.get_count_stats()].set_explantion("desposit");

                        pro.set_count_stats();//increase count stats
                    }

                    cout << "the deposit was successful" << endl;
                    break;
                }
                
            }
            
        }
        
    }
}

void transfer()
{
    string sender_name;
    getline(cin, sender_name, ':');

    string sender_ip;
    getline(cin, sender_ip, ':');

    string receiver_ip_name;//or ip or username
    getline(cin, receiver_ip_name, ':');

    string temp;
    getline(cin, temp);
    long double currency = stold(temp);
    while (currency < 0)//chek currency
    {
        cout << "the amount given is not valid, enter the correct amount--->";
        getline(cin, temp); 
        currency = stold(temp);
    }

    bool digit = false;
    if (isdigit(receiver_ip_name[0]))//chek receiver based on ip or username
    {//just chek 0 because not available username that start with a number
        digit = true;
    }
    
    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }

        if (owner[i].get_username() == sender_name)//find and chek username
        {
            string data = time_now();
            if (data > owner[i].get_expiration())//chek expiration account
            {
                cout << "this account has expiration please renwal account" << endl;
                break;
            }

            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == sender_ip)//chek ip sender
                {
                    if (!digit)//chek by username receiver
                    {
                        for (size_t m = 0; m < owner.size(); m++)//find and chek user name reciver
                        {
                            if (owner[m].get_username() == receiver_ip_name)
                            {
                                owner[i].set_money(-currency);//decrease sender money
                                owner[m].set_money(currency);//increase receiver money

                                {//compelet information for report (class transaction)
                                    pro.stats_bank[pro.get_count_stats()].set_sender(sender_name);
                                    pro.stats_bank[pro.get_count_stats()].set_reciver(receiver_ip_name);
                                    pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                                    pro.stats_bank[pro.get_count_stats()].set_date(data);
                                    pro.stats_bank[pro.get_count_stats()].set_explantion("transfer");

                                    pro.set_count_stats();//increase count stats
                                }
                                cout << "Money transferred successfully" << endl;
                                break;
                            }
                        }
                        
                    }
                    else if (digit)//chek by ip receiver
                    {
                        for (size_t m = 0; m < owner.size(); m++)//find and chek ip reciver
                        {
                            for (size_t n = 0; n < owner[m].get_ip_size(); n++)
                            {
                                if (owner[m].get_ip(n) == receiver_ip_name)
                                {
                                    owner[i].set_money(-currency);//decrease sender money
                                    owner[m].set_money(currency);//increase receiver money

                                    {//compelet information for report (class transaction)
                                        pro.stats_bank[pro.get_count_stats()].set_sender(sender_name);
                                        pro.stats_bank[pro.get_count_stats()].set_reciver(receiver_ip_name);
                                        pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                                        pro.stats_bank[pro.get_count_stats()].set_date(data);
                                        pro.stats_bank[pro.get_count_stats()].set_explantion("transfer");

                                        pro.set_count_stats();//increase count stats
                                    }
                                    break;
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
                
            }

        }
        
    }
}

void withdraw()
{
    string username;
    getline(cin, username, ':');//get username

    string ip;
    getline(cin, ip, ':');//get ip

    string temp;
    getline(cin, temp);//get money
    long double currency = stold(temp);
    while (currency < 0)//chek currency
    {
        cout << "the amount given is not valid, enter the correct amount--->";
        getline(cin, temp); 
        currency = stold(temp);
    }

    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }
        if (owner[i].get_username() == username)
        {
            string data = time_now();
            if (data > owner[i].get_expiration())//chek expiration account
            {
                cout << "this account has expiration please renwal account" << endl;
                break;
            }

            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == ip)
                {
                    if (owner[i].get_money() >= currency)//chek balance account
                    {
                        if (pro.get_total_money() >= currency)
                        {
                            owner[i].set_money(-currency);//decrease account balance
                            pro.set_total_money(-currency);//decrease bank balance

                            {//compelet information for report (class transaction)
                                pro.stats_bank[pro.get_count_stats()].set_sender(username);
                                pro.stats_bank[pro.get_count_stats()].set_reciver("...");
                                pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                                pro.stats_bank[pro.get_count_stats()].set_date(data);
                                pro.stats_bank[pro.get_count_stats()].set_explantion("withdraw");

                                pro.set_count_stats();//increase count stats
                            }
                            cout << "Money was withdrawn successfully" << endl;
                            break;
                        }
                        else
                        {
                            cout << "The bank has bankrupt" << endl;
                            pro.set_bankrupt(0);//set bank has bankrupt
                            break;
                        }
                        
                    }
                    else
                    {
                        cout << "not enough account balance!!!" << endl;
                        break;
                    }
                    
                }
                
            }
            
        }
        
    }
}

void add_profit()
{
    string username;
    getline(cin, username);

    for (size_t i = 0; i < owner.size(); i++)
    {
        string username;
        getline(cin, username);

        string data_now = time_now();

        time_t temp = time(NULL);//get time now
        tm *now = localtime(&temp);

        string data_next = to_string(now->tm_year+1900) + ".";//get year now
        string helper = to_string(now->tm_mon+2);
        if (helper > "12")
        {
            helper = to_string((now->tm_mon+2) - 12);
            data_next = to_string((now->tm_year+1900) + 1) + ".";
        }
        
        data_next += helper + ".";//get month
        data_next += to_string(now->tm_mday);//get day
        

        for (size_t i = 0; i < owner.size(); i++)
        {
            if (pro.get_bankrupt())
            {
                cout << "this bank is bankrupt!!!" << endl;
                break;
            }

            if (owner[i].get_username() == username)
            {
                if (data_now > owner[i].get_day_profit() && owner[i].get_loan() == 0)
                {
                    bool haswithdraw = true;

                    time_t temp = time(NULL);//get time now
                    tm *now = localtime(&temp);

                    string seven_day_ago = to_string(now->tm_year+1900) + ".";//get year now
                    
                    string help_day = to_string(now->tm_mday - 7);//get day
                    if (help_day < "0")
                    {
                        help_day = to_string(30 - stod(help_day));
                    }
                    seven_day_ago += to_string((now->tm_mon+1) - 1) + ".";//get month
                    seven_day_ago += help_day;
                        

                    for (size_t j = 0; j < owner[i].stats_customer.size(); j++)
                    {
                        if (owner[i].stats_customer[j]->get_date() > seven_day_ago
                                && owner[i].stats_customer[j]->get_explantion() == "withdraw")
                        {
                            haswithdraw = false;
                        }
                    
                    }

                    if (haswithdraw)
                    {//increase profit for not withdraw
                        if (owner[i].get_money() > 1000000)
                        {//balance more than 1.000.000$ and not withdraw in 7day ago profit = 18% 
                            owner[i].set_money((owner[i].get_money() * 0.18) / 12);//profit for account balance now
                            owner[i].set_date_profit(data_next);
                            haswithdraw = true;
                            break;
                        }
                        else
                        {//balance less than 1.000.000$ and not withdraw in 7day ago profit = 17%
                            owner[i].set_money((owner[i].get_money() * 0.17) / 12);//profit for account balance now
                            owner[i].set_date_profit(data_next);
                            haswithdraw = true;
                            break;
                        }
                    }
                    if (!haswithdraw)
                    {
                        if (owner[i].get_money() > 1000000)
                        {//balance more than 1.000.000$ and withdraw in 7day ago profit = 16% 
                            owner[i].set_money((owner[i].get_money() * 0.16) / 12);//profit for account balance now
                            owner[i].set_date_profit(data_next);
                            haswithdraw = true;
                            break;
                        }
                        else
                        {//balance less than 1.000.000$ and withdraw in 7day ago profit = 15%
                            owner[i].set_money((owner[i].get_money() * 0.15) / 12);//profit for account balance now
                            owner[i].set_date_profit(data_next);
                            break;
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
}

void get_loan()
{
    string username;
    getline(cin, username, ':');//get username

    string ip;
    getline(cin, ip, ':');//get ip

    string temp;
    getline(cin, temp);//get money
    long double currency = stold(temp);
    while (currency < 0)//chek currency
    {
        cout << "the amount given is not valid, enter the correct amount--->";
        getline(cin, temp); 
        currency = stold(temp);
    }

    for (size_t i = 0; i < owner.size(); i++)
    {
        if (pro.get_bankrupt())//chek bank is bankrupt or no 
        {
            cout << "this bank is bankrupt!!!" << endl;
            break;
        }
        
        if (owner[i].get_username() == username)//chek and find username
        {
            string data = time_now();
            if (data > owner[i].get_expiration())//chek expiration account
            {
                cout << "this account has expiration please renwal account" << endl;
                break;
            }

            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == ip)
                {
                    if (owner[i].get_money() * 0.75 >= currency && owner[i].get_loan() == 0)
                    {
                        if (pro.get_total_money() > currency)
                        {//profit loan = 20%
                            owner[i].set_loan(currency + (currency * 0.2));//set loan for account
                            pro.set_demands(currency);//set and increase demands 
                            pro.set_total_loans(currency);//save loan in bank
                            pro.set_profits_loan(currency*0.2);//save profit loan in bank

                            {//compelet information for report (class transaction)
                                pro.stats_bank[pro.get_count_stats()].set_sender("bank");
                                pro.stats_bank[pro.get_count_stats()].set_reciver(username);
                                pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                                pro.stats_bank[pro.get_count_stats()].set_date(data);
                                pro.stats_bank[pro.get_count_stats()].set_explantion("get_loan");

                                pro.set_count_stats();//increase count stats
                            }
                            cout << "Was given a loan" << endl;
                        }
                        else
                        {
                            cout << "The bank can not lend as much(bank balance is not enough)" << endl;
                        }
                        
                    }
                    else
                    {
                        cout << "your account balance is low for give this loan or "
                                << "You have an outstanding loan" << endl;
                                
                        char confirm = ' ';
                        cout << "do you want to know what is the maximum loan you can get?, Y/N --->";
                        cin >> confirm;

                        if ((confirm == 'y' || confirm == 'Y') && pro.get_total_money() >= owner[i].get_money()*0.75)
                        {
                            cout << "maximum loen: " << owner[i].get_money()*0.75 << endl;
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }
                
            }
        }
        
    }
}

void pay_loan()
{
    string username;
    getline(cin, username, ':');

    string temp;
    getline(cin, temp);
    long double currency = stold(temp);
    while (currency < 0)//chek currency
    {
        cout << "the amount given is not valid, enter the correct amount--->";
        getline(cin, temp); 
        currency = stold(temp);
    }

    for (size_t i = 0; i < owner.size(); i++)
    {
        //In this part, the bankruptcy of the bank does not prevent the payment 
                                            //of loans so that the bank may be able to
        if (owner[i].get_username() == username)//chek and find username
        {
            string data = time_now();

            if (owner[i].get_loan() >= currency)//chek loan account
            {
                owner[i].set_loan(-currency);//decrease loan

                pro.set_demands(-currency);//decrease demands

                {//compelet information for report (class transaction)
                    pro.stats_bank[pro.get_count_stats()].set_sender(username);
                    pro.stats_bank[pro.get_count_stats()].set_reciver("bank");
                    pro.stats_bank[pro.get_count_stats()].set_amount(currency);
                    pro.stats_bank[pro.get_count_stats()].set_date(data);
                    pro.stats_bank[pro.get_count_stats()].set_explantion("pay_loan");

                    pro.set_count_stats();//increase count stats
                }
            }
            else//currency > loan
            {
                currency -= owner[i].get_loan();
                owner[i].set_loan(-(owner[i].get_loan()));//loan = 0 (pay compelet loan)

                owner[i].set_money(currency);//increase money


                pro.set_demands(-(owner[i].get_loan()));//decrease demands
            } 
            cout << "payment was successful" << endl;
        }
    }
}

void info_bank()
{
    cout << "number of account      ---> " << pro.get_client() << endl
         << "bank balance           ---> " << pro.get_total_money() << endl
         << "loans given            ---> " << pro.get_total_loans() << endl
         << "loan interest          ---> " << pro.get_profits_loan() << endl
         << "unpaid loans           ---> " << pro.get_demands() << endl;
    cout << "bank status            ---> ";
    pro.get_bankrupt() ? cout << "bankrupt" : cout << "not bankrupt";
    cout << endl;
}

void report()
{
    string username;
    getline(cin, username);//get username

    for (size_t i = 0; i < owner.size(); i++)
    {
        if (owner[i].get_username() == username)//chek username is available
        {
            owner[i].stats_customer.shrink_to_fit();
            for (size_t j = owner[i].stats_customer.size(); j > owner[i].stats_customer.size() - 5
                                                                    && j >= 0; j--)
            {//printf 5 recent tranaction
                cout << "sender       ---> " << owner[i].stats_customer[j]->get_sender() << endl
                     << "reciver      ---> " << owner[i].stats_customer[j]->get_reciver() << endl
                     << "amount       ---> " << owner[i].stats_customer[j]->get_amount() << endl
                     << "date         ---> " << owner[i].stats_customer[j]->get_date() << endl
                     << "explanation  ---> " << owner[i].stats_customer[j]->get_explantion() << endl;
            }
            
        }
        
    }
}

void info_naccount(string get)
{
    if (get.find('.') < 10)//for serch by card number or ip
    {//get == ip
        for (size_t i = 0; i < owner.size(); i++)
        {
            for (size_t j = 0; j < owner[i].get_ip_size(); j++)
            {
                if (owner[i].get_ip(j) == get)
                {
                    cout << "username             ---> " << owner[i].get_username() << endl;
                    cout << "ips: ";
                    for (size_t k = 0; k < owner[i].get_ip_size(); k++)
                    {
                        cout << owner[i].get_ip(k) << " **** ";  
                    }
                    cout << endl;
                    cout << "account balance      ---> " << owner[i].get_money() << endl
                         << "card number          ---> " << owner[i].get_card_number() << endl
                         << "date opening         ---> " << owner[i].get_opening() << endl
                         << "date expiration      ---> " << owner[i].get_expiration() << endl
                         << "debtor for the loan  ---> " << owner[i].get_loan() << endl;
                    break;
                }
                
            }
            
        }

    }
    else
    {//get == card number
        for (size_t i = 0; i < owner.size(); i++)
        {
            if (owner[i].get_card_number() == stod(get))
            {
                cout << "username                ---> " << owner[i].get_username() << endl;
                cout << "ips: ";
                for (size_t k = 0; k < owner[i].get_ip_size(); k++)
                {
                    cout << owner[i].get_ip(k) << "-*-*-*";  
                }
                cout << endl;
                cout << "account balance         ---> " << owner[i].get_money() << endl
                        << "card number          ---> " << owner[i].get_card_number() << endl//can dont show card number again
                        << "date opening         ---> " << owner[i].get_opening() << endl
                        << "date expiration      ---> " << owner[i].get_expiration() << endl
                        << "debtor for the loan  ---> " << owner[i].get_loan() << endl;
                break;
            }
            
        }
        
    }
}

void info_aaccount(string get)
{
    for (size_t i = 0; i < owner.size(); i++)
    {
        if (owner[i].get_username() == get)
        {
            cout << "username             ---> " << owner[i].get_username() << endl;
            cout << "ips: ";
            for (size_t k = 0; k < owner[i].get_ip_size(); k++)
            {
                cout << owner[i].get_ip(k) << "-*-*-*";  
            }
            cout << endl;
            cout << "account balance      ---> " << owner[i].get_money() << endl
                 << "card number          ---> " << owner[i].get_card_number() << endl//can dont show card number again
                 << "date opening         ---> " << owner[i].get_opening() << endl
                 << "date expiration      ---> " << owner[i].get_expiration() << endl
                 << "debtor for the loan  ---> " << owner[i].get_loan() << endl;
            break;
        }
        
    }
}
