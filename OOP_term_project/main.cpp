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
#include <fstream>

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

Account* accountData;





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

Bank* bankData;

Bank findBank(string name) {
    int i;
    for (i = 0; i < 11; i++) {
        if (bankData[i].getBankName().compare(name) == 0) break;
    }
    return bankData[i];
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
    ATM() {}
    ATM(string priName) {
        serialNum = "000001";
        primaryBank = findBank(priName);
        cashAmount = 10000000;
    }
    string getPrimaryBankInfo() {return primaryBank.getBankName();}
};

ATM* atmData;


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





/*------------------------------------- FILE Read Function ------------------------------------*/
void readAtmData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(2);
    } else { // 좀 더 수정해야됨
        string str;
        getline(fin, str);
        int numAtm = stoi(str);
        ATM atmList[numAtm];
        atmData = atmList;
        for (int i = 0; i < numAtm; i++) {
            getline(fin, str);
            ATM newAtm(str);
            atmData[i] = newAtm;
        }
    }
}

void readBankData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(2);
    } else {
        string str;
        getline(fin, str);
        int numBank = stoi(str);
        Bank bankList[numBank];
        bankData = bankList;
        for (int i = 0; i < numBank; i++) {
            getline(fin, str);
            Bank newBank(str);
            bankData[i] = newBank;
        }
    }
}

void readAccountData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(2);
    } else { // 좀 더 수정해야됨.
        string str;
        getline(fin, str);
        int numAccount = stoi(str);
        Account accountList[numAccount];
        accountData = accountList;
        for (int i = 0; i < numAccount; i++) {
            getline(fin, str);
            Account newAccount(str);
            accountData[i] = newAccount;
        }
    }
}





/*--------------------------------------- Main Function ---------------------------------------*/

int main(int argc, char* argv[]) {
    /*
     argc 는 인자 개수
     argv 는 인자 리스트 (문자열로 저장됨)
     for 구문을 통해 ATM, Bank, Account 데이터를 읽어들일 거임
     .txt 파일을 읽어들일 거며 .txt 파일은 ATM, Bank, Account 총 3개
     argv[0] : 프로그램명
     argv[1] ~ argv[3] : ATM.txt, Bank.txt, Account.txt
     -> 따라서 argc는 4
     각 .txt 파일의 첫째줄은 데이터의 개수
    */
    
    int atmArgCount = 0;
    int bankArgCount = 0;
    int accountArgCount = 0;
    
    if (argc != 4) { // Argument 수가 맞지 않을때
        cout << "Argument 부족" << endl;
        return 1;
    } else { // 정상 실행
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], "ATM.txt", 7) == 0) { // Argument 가 ATM.txt 일 경우
                if (atmArgCount != 0) { // ATM argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
                    cout << "Too many ATM arguments..." << endl;
                    return 2;
                } else { // 정상 실행
                    ifstream fin(argv[i]); // 파일 read
                    readAtmData(fin);
                    atmArgCount ++;
                }
            } else if (strncmp(argv[i], "Bank.txt", 8) == 0) { // Argument 가 Bank.txt 일 경우
                if (bankArgCount != 0) { // Bank argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
                    cout << "Too many Bank arguments..." << endl;
                    return 3;
                } else { // 정상 실행
                    ifstream fin(argv[i]); // 파일 read
                    readBankData(fin);
                    bankArgCount ++;
                }
            } else if (strncmp(argv[i], "Account.txt", 11) == 0) { // Argument 가 Account.txt 일 경우
                if (accountArgCount != 0) { // Account argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
                    cout << "Too many Account arguments..." << endl;
                    return 4;
                } else { // 정상 실행
                    ifstream fin(argv[i]); // 파일 read
                    readAccountData(fin);
                    accountArgCount ++;
                }
            } else { // Exception
                cout << argv[i] << "의 파일명이 invalid 합니다..." << endl;
                return 5;
            }
        }
    }
    
    bool programEndSignal = true;
    ATM atm1("KB");
    
    while (programEndSignal) {
        
    }
    
    return 0;
}
