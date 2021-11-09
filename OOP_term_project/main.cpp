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
    Bank() {
        bankName = "unknown";
    }
    Bank(string name) {
        bankName = name;
    }
    string getBankName() {return bankName;}
};

/*-- Bank Class --*/
class ATM {
protected:
    string serialNum;
    Bank primaryBank;
    int language;   // 0: Korean,    1: English
    unsigned long long inCash;  // ATM에 들어있는 현금
public:
    ATM(string priName) {
        serialNum = "000001";
        Bank bank = Bank(priName);
        primaryBank = bank;
        inCash = 10000000;
    }
    string getPrimaryBankInfo() {return primaryBank.getBankName();}
};

class SingleBankATM : public ATM {
    
};

class MultiBankATM : public ATM {
    
};

class UnilingualATM : public ATM {
    
};

class BilingualATM : public ATM {
    
};



/*----- Main Function -----*/
int main() {
    
    bool endSignal = true;
    ATM atm1("KB");
    
    while (endSignal) {
        // 기본 ATM 디스플레이 출력 (ex. English)
        cout << "***************************************************************" << endl;
        cout << "*                           WELCOME                           *" << endl;
        cout << "*        To Start, Please Enter Your Debit Card Number        *" << endl;
        cout << "***************************************************************" << endl;
        cout << "*                       Select Service!                       *" << endl;
        cout << "*        1. Deposit                                           *" << endl;
        cout << "*        2. Withdrawal                                        *" << endl;
        cout << "*        3. Transfer                                          *" << endl;
        cout << "***************************************************************" << endl;
        cout << "Our Primary Bank is " << atm1.getPrimaryBankInfo() << " bank" << endl;
        cout << "\n";
        cout << "Select Service : " << endl;
        int serviceNum;
        cin >> serviceNum;
        cout << "\n";
        
        if (serviceNum == 1) { // 입금
            cout << "***************************************************************" << endl;
            cout << "*        To Start, Please Enter Your Debit Card Number        *" << endl;
            cout << "***************************************************************" << endl;
            cout << "You select the Deposit Service." << endl;
        }
        else if (serviceNum == 2) { // 인출
            cout << "***************************************************************" << endl;
            cout << "*        To Start, Please Enter Your Debit Card Number        *" << endl;
            cout << "***************************************************************" << endl;
            cout << "You select the Withdrawal Service." << endl;
        }
        else if (serviceNum == 3) { // 송금
            cout << "***************************************************************" << endl;
            cout << "*        To Start, Please Enter Your Debit Card Number        *" << endl;
            cout << "***************************************************************" << endl;
            cout << "You select the Transfer Service." << endl;
        }
        
        
        cout << "If you want to continue, please enter '1'." << endl;
        cout << "To stop, enter '0'." << endl;
        cout << "Continue? : ";
        int temp;
        cin >> temp;
        if (temp == 0) endSignal = false;
        cout << "\n";
        
    }
    
    return 0;
}
