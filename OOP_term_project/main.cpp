/*
***   ********************************************************
***   *                                                      *
***   *   Object-Oriented Programming Course Term Project    *
***   *                                                      *
***   *   201511047 Kim,Jong-Soo    201611030 Kim,San-Ha     *
***   *   201911012 Kong,Young-Jae  201911088 An,Sang-Jun    *
***   *                                                      *
***   ********************************************************
 */

#include <iostream>

using namespace std;

/*
***  Class Building
 */

/*-- Account Class --*/
class Account {
private:
    string accountNumber;
    string accountPw;
    string cardNum;
    string userName;
public:
    Account() {}
    ~Account() {}
    int check_pw(string inPw) {
        if (accountPw == inPw) return 0;
        else return 1;
    }
    
};

/*-- Bank Class --*/
class Bank {
private:
    string bankName;
    Account* accounts;
public:
    
};

/*-- Bank Class --*/
class ATM {
private:
    string serialNum;
    Bank primaryBank;
    int atmType;    // 0: Single-Bank ATM,    1: Multi-Bank ATM
    int lingualType;    // 0: unilingual(only English), 1: bilingual(English or Korean)
    int language;   // 0: Korean,    1: English
    unsigned long long inCash;  // ATM에 들어있는 현금
public:
    
};

/*----- Main Function -----*/
int main() {
    
    return 0;
}
