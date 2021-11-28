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
class Transaction {
private:
    static double ID;
    double Amount;
public:
    Transaction();
    double getID() {return ID;}
    double getAmount() {return Amount;}
};

double Transaction::ID {1};

/*-- Account Class --*/
class Account {
private:
    string accountNumber;
    string accountPw;
    string userName;
    double availabeFunds;
    Transaction *transactionHistoryOfAccount;
public:
    Account() {}
    ~Account() {}
    bool check_pw(string inPw) {
        if (accountPw == inPw) return true;
        else return false;
    }
    void plusMoney(double amount) {availabeFunds += amount;}
    void minusMoney(double amount) {availabeFunds -= amount;}
    bool compareAccount(string account) {
        if (accountNumber.compare(account) == 0) return true;
        else return false;
    }
};

/*-- Bank Class --*/
class Bank {
private:
    string bankName;
    Account* accounts;
    int numOfAccounts;
public:
    Bank() {
        bankName = "unknown";
    }
    Bank(string name) {
        bankName = name;
    }
    string getBankName() {return bankName;}
    Account findAccount(string account) {
        int i;
        for (i = 0; i < numOfAccounts; i++) {
            if (accounts[i].compareAccount(account)) {
                break;
            }
        }
        return accounts[i];
    }
};

Bank kbBank;
Bank kakaoBank;
Bank bankList[2] = {kbBank, kakaoBank};


Bank findBank(string name) {
    int i;
    for (i = 0; i < 2; i++) {
        if (bankList[i].getBankName().compare(name) == 0) break;
    }
    return bankList[i];
}

/*-- Session Class --*/
class Session {
protected:
    Account account;
    Transaction* transactionHistoryOfSession;
    bool authorizationSignal;
    int authorizationCount;
    int withdrawalCount;
public:
    Session() {}
    void Deposit(double amount);
    void Withdrawal(double amount);
    void Transfer(double amount, Account destination);
    bool Authorization(string password) {return account.check_pw(password);}
};

void Session::Deposit(double amount) {
    account.plusMoney(amount);
}

void Session::Withdrawal(double amount) {
    account.minusMoney(amount);
}

void Session::Transfer(double amount, Account destination) {
    destination.plusMoney(amount);
}

class KoreanSession : public Session {
    
};

class EnglishSession : public Session {
public:
    EnglishSession() {
        authorizationCount = 0;
        authorizationSignal = true;
        string inputAccount;
        cout << "Enter your Account Number" << endl;
        cout << "Account Number : ";
        cin >> inputAccount;
        for (int i = 1; i < 3; i++) {
            string inputPassword;
            cout << "Enter your Account Password" << endl;
            cout << "Password : ";
            cin >> inputPassword;
            if (Authorization(inputPassword)) break;
            else {
                authorizationSignal = false;
                authorizationCount ++;
                cout << authorizationCount << " Authorization Fail" << endl;
            }
        }
        if (authorizationSignal == false) {
            cout << "Authorization Fail, " << endl;
        }
        else {
            bool sessionExitSignal = true;
            while (sessionExitSignal) {
                cout << "Transaction List" << endl;
                cout << "1. Deposit" << endl;
                cout << "2. Withdrawal" << endl;
                cout << "3. Transfer" << endl;
                cout << "\n";
                cout << "Enter the transaction number which you want: ";
                int transactionNum;
                cin >> transactionNum;
                if (transactionNum == 1) { // Deposit
                    cout << "You choose the Deposit Transaction." << endl;
                    cout << "Please enter the amount what you want to deposit." << endl;
                    cout << "Amount : ";
                    int inAmount;
                    cin >> inAmount;
                    Deposit(inAmount);
                } else if (transactionNum == 2) { // Withdrawal
                    cout << "You choose the Withdrawal Transaction." << endl;
                    cout << "Please enter the amount what you want to withdrawal." << endl;
                    cout << "Amount : ";
                    int inAmount;
                    cin >> inAmount;
                    Withdrawal(inAmount);
                } else if (transactionNum == 3) { // Transfer
                    cout << "You choose the Transfer Transaction." << endl;
                    cout << "1. Account Transfer (Account to Account)" << endl;
                    cout << "2. Cash Transfer (Cash to Account)" << endl;
                    cout << "Please enter the kind of the Transfer : " << endl;
                    int transferNum;
                    cin >> transferNum;
                    if (transferNum == 1) { // Account Transfer
                        cout << "You choose the Account Transfer Transaction." << endl;
                        cout << "Please enter the amount what you want to transfer." << endl;
                        cout << "Amount : ";
                        int inAmount;
                        cin >> inAmount;
                        cout << "Please enter the bank name of destination account : " << endl;
                        string inDestName;
                        cin >> inDestName;
                        cout << "Please enter the destination account : ";
                        string inDest;
                        cin >> inDest;
                        Transfer(inAmount, findBank(inDestName).findAccount(inDest));
                    } else if (transferNum == 2) { // Cash Transfer
                        cout << "You choose the Cash Transfer Transaction." << endl;
                        cout << "Please enter the amount what you want to transfer." << endl;
                        cout << "Amount : ";
                        int inAmount;
                        cin >> inAmount;
                        cout << "Please enter the bank name of destination account : " << endl;
                        string inDestName;
                        cin >> inDestName;
                        cout << "Please enter the destination account : ";
                        string inDest;
                        cin >> inDest;
                        Transfer(inAmount, findBank(inDestName).findAccount(inDest));
                    } else { // Exception
                        cout << "It's an invalid number. Please retry." << endl;
                    }
                } else { // Exception
                    cout << "It's an invalid number. Please retry." << endl;
                }
            }
        }
    }
};

/*-- Bank Class --*/
class ATM {
protected:
    string serialNum;
    Bank primaryBank;
    unsigned long long cashAmount;  // ATM에 들어있는 현금
    Transaction* transactionHistoryOfATM;
    string AdminNum;
    Session session;
public:
    ATM(string priName) {
        serialNum = "000001";
        Bank bank = Bank(priName);
        primaryBank = bank;
        cashAmount = 10000000;
    }
    string getPrimaryBankInfo() {return primaryBank.getBankName();}
};

class SingleBankATM : public ATM {
public:
    
};

class MultiBankATM : public ATM {
public:
    
};

class UnilingualATM : public ATM {
private:
    string language;
public:
    UnilingualATM() {
        
    }
};

class BilingualATM : public ATM {
public:
    BilingualATM() {
        
    }
    void startSession() {
        Session newSession;
        session = newSession;
    }
};


/*----- Main Function -----*/
int main() {
    
    bool programEndSignal = true;
    ATM atm1("KB");
    
    while (programEndSignal) {
        
    }
    
    return 0;
}
