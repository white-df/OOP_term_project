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

/*------------------------------------- Transaction Class -------------------------------------*/

class Transaction {
protected:
    static double ID;
    double Amount;
public:
    Transaction();
    double getID() {return ID;}
    double getAmount() {return Amount;}
};

double Transaction::ID {1};


/*------------ Children Classes of Transaction Class ------------*/

/*-------- Deposit Transaction Class --------*/
class DepositTransaction : public Transaction {
    
};


/*------- Withdrawal Transaction Class ------*/
class WithdrawalTransaction : public Transaction {
    
};


/*-------- Transfer Transaction Class -------*/
class TransferTransaction : public Transaction {
    
};





/*--------------------------------------- Account Class ---------------------------------------*/

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





/*----------------------------------------- Bank Class ----------------------------------------*/

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

Bank KbBank("KB");
Bank KakaoBank("KAKAO");
Bank DaeguBank("DGB");
Bank ShinhanBank("SHB");
Bank WooriBank("WOORI");
Bank IbkBank("IBK");
Bank NonghyupBank("NH");
Bank BusanBank("BNK");
Bank HanaBank("HANA");
Bank KwangjuBank("JB");
Bank JejuBank("JEJU");
Bank bankList[11] = {KbBank, KakaoBank, DaeguBank, ShinhanBank,
                    WooriBank, IbkBank, NonghyupBank, BusanBank,
                    HanaBank, KwangjuBank, JejuBank};


Bank findBank(string name) {
    int i;
    for (i = 0; i < 11; i++) {
        if (bankList[i].getBankName().compare(name) == 0) break;
    }
    return bankList[i];
}





/*--------------------------------------- Session Class ---------------------------------------*/

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


/*-------------- Children Classes of Session Class --------------*/

/*---------- Korean Session Class -----------*/

class KoreanSession : public Session {
    
};

/*---------- English Session Class ----------*/

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





/*----------------------------------------- ATM Class -----------------------------------------*/

class ATM {
protected:
    string serialNum; // ATM 시리얼 넘버
    Bank primaryBank; // 주거래 은행
    unsigned long long cashAmount;  // ATM에 들어있는 현금
    Transaction* transactionHistoryOfATM; // ATM 전체 transaction history (Admin에서 접근 가능)
    string AdminNum; // Admin 넘버
    Session session; // 세션
public:
    ATM(string priName) {
        serialNum = "000001";
        primaryBank = findBank(priName);
        cashAmount = 10000000;
    }
    string getPrimaryBankInfo() {return primaryBank.getBankName();}
};


/*---------------- Children Classes of ATM Class ----------------*/

/*---------- Single Bank ATM Class ----------*/

class SingleBankATM : public ATM {
public:
    
};

/*---------- Multi Bank ATM Class -----------*/

class MultiBankATM : public ATM {
public:
    
};

/*---------- Unilingual ATM Class -----------*/

class UnilingualATM : public ATM {
private:
    string language;
public:
    UnilingualATM() {
        
    }
};

/*----------- Bilingual ATM Class -----------*/

class BilingualATM : public ATM {
public:
    BilingualATM() {
        
    }
    void startSession() {
        Session newSession;
        session = newSession;
    }
};





/*--------------------------------------- Main Function ---------------------------------------*/

int main() {
    
    bool programEndSignal = true;
    ATM atm1("KB");
    
    while (programEndSignal) {
        
    }
    
    return 0;
}
