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
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/*
***  Class Building
 */


/*--------------------------------------- Account Class ---------------------------------------*/

class Transaction; // 전방선언

class Account {
protected:
    string accountNumber = "";
    string accountPw = "";
    string userName = "";
    double availableFunds = 0;
    vector<Transaction> transactionHistoryOfAccount;
public:
    Account() {}
    Account(string aNum, string aPW, string uName, string funds) {
        accountNumber = aNum;
        accountPw = aPW;
        userName = uName;
        availableFunds = double(stoi(funds));
    }
    ~Account() {}
    string getAccountNumber() { return accountNumber; }
    bool check_pw(string inPw) {
        if (accountPw.compare(inPw) == 0) return true;
        else return false;
    }
    void plusMoney(double amount) { availableFunds += amount; }
    void minusMoney(double amount) { availableFunds -= amount; }
    bool compareAccount(string account) {
        if (accountNumber.compare(account) == 0) return true;
        else return false;
    }
    void addTransaction(Transaction* trans) {transactionHistoryOfAccount.push_back(*trans);}
};





/*------------------------------------------------ Transaction Class ---------------------------------------------------*/
/*--------------거래내역 남기는 법: Session에서 거래 시작 시 Transaction* transaction 선언 후 거래 종료 시,--------------*/
/*---transaction = new {deposit, withdraw, transfer 중 1}Transaction(transaction, (dest account), account, amount)---*/

//class Transaction : public Account {
class Transaction {
protected:
    static double transactionCnt;
    double ID = transactionCnt;
    double Amount = 0;
    string description = "#";
//    Transaction* transaction = nullptr;
    Account account;
public:
    double getID() { return ID; }
    double getAmount() { return Amount; }
    string getInformation() {return description;}
//    virtual string getInformation() = 0;
//    virtual ~Transaction() = default;
};

double Transaction::transactionCnt{ 1 };


/*------------ Children Classes of Transaction Class ------------*/

/*-------- Deposit Transaction Class --------*/
class DepositTransaction : public Transaction {
public:
    DepositTransaction(Account acc, double amount);
//    string getInformation();
};
DepositTransaction::DepositTransaction(Account acc, double amount) {
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(int(ID)));
    description.append(". Account number '");
    description.append(account.getAccountNumber());
    description.append("' deposited ");
    description.append(to_string(amount));
    description.append(" $");
}

//string DepositTransaction::getInformation() {
//    return description;
//} /* ex. 1 1234 5678 deposited 100$ */
//  /* ex. 2 1234 5678 withdrew 50$ */

/*------- Withdrawal Transaction Class ------*/
class WithdrawalTransaction : public Transaction {
public:
    WithdrawalTransaction(Account acc, double amount);
//    string getInformation();
};

WithdrawalTransaction::WithdrawalTransaction(Account acc, double amount) {
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(int(ID)));
    description.append(". Account number '");
    description.append(account.getAccountNumber());
    description.append("' withdrew ");
    description.append(to_string(amount));
    description.append(" $");
}


//string WithdrawalTransaction::getInformation() {
//    return description;
//}

/*-------- Transfer Transaction Class -------*/
class TransferTransaction : public Transaction {
protected:
    Account destaccount;
};

class AccountTransferTransaction : public TransferTransaction {
public:
    AccountTransferTransaction(Account destacc, Account account, double amount);
//    string getInformation();
};
AccountTransferTransaction::AccountTransferTransaction(Account destacc, Account acc, double amount) {
    destaccount = destacc;
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(int(ID)));
    description.append(". Account number '");
    description.append(account.getAccountNumber());
    description.append("' transfer to ");
    description.append(destaccount.getAccountNumber()).append(" ");
    description.append(to_string(amount));
    description.append(" $");
}


//string AccountTransferTransaction::getInformation() {
//    return description;
//}

class CashTransferTransaction : public TransferTransaction {
public:
    CashTransferTransaction(Account destaccount, Account account, double amount);
//    string getInformation();
};
CashTransferTransaction::CashTransferTransaction(Account destacc, Account acc, double amount) {
    destaccount = destacc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(int(ID)));
    description.append(". Account number '");
    description.append(account.getAccountNumber());
    description.append("' transfer to ");
    description.append(destaccount.getAccountNumber()).append(" ");
    description.append(to_string(amount));
    description.append(" $");
}

//string CashTransferTransaction::getInformation() {
//    return description;
//}





/*----------------------------------------- Bank Class ----------------------------------------*/

class Bank {
private:
    string bankName;
    vector<Account> accounts;
public:
    Bank() {
        bankName = "unknown";
    }
    Bank(string name) {
        bankName = name;
    }
    string getBankName() {return bankName;}
    Account findAccount(string account);
    void addAccount(Account account) {accounts.push_back(account);}
};

Account Bank::findAccount(string account) {
    int i;
    for (i = 0; i < accounts.size(); i++) {
        if (accounts[i].compareAccount(account)) {
            break;
        }
    }
    return accounts[i];
}

vector<Bank> bankData;

Bank* findBank(string name) {
    int i;
    for (i = 0; i < bankData.size(); i++) {
        if (bankData[i].getBankName().compare(name) == 0) break;
    }
    return &bankData[i];
}





/*--------------------------------------- Session Class ---------------------------------------*/

class ATM;

class Session {
protected:
    Account account;
    vector<Transaction> transactionHistoryOfSession;
    bool authorizationSignal;
    int authorizationCount;
    int withdrawalCount;
public:
    Session() {}
    void Deposit(double amount);
    void Withdrawal(double amount);
    void CashTransfer(double amount, Account destination);
    void AccountTransfer(double amount, Account destination);
    bool Authorization(string password) {return account.check_pw(password);}
};

void Session::Deposit(double amount) {
    account.plusMoney(amount);
    DepositTransaction newTransaction(account, amount);
    account.addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout << newTransaction.getInformation() << endl;
}

void Session::Withdrawal(double amount) {
    account.minusMoney(amount);
    WithdrawalTransaction newTransaction(account, amount);
    account.addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout << newTransaction.getInformation() << endl;
}

void Session::CashTransfer(double amount, Account destination) {
    destination.plusMoney(amount);
    CashTransferTransaction newTransaction(destination, account, amount);
    destination.addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout << newTransaction.getInformation() << endl;
}

void Session::AccountTransfer(double amount, Account destination) {
    account.minusMoney(amount);
    destination.plusMoney(amount);
    AccountTransferTransaction newTransaction(destination, account, amount);
    destination.addTransaction(&newTransaction);
    account.addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout << newTransaction.getInformation() << endl;
}





/*----------------------------------------- ATM Class -----------------------------------------*/

class ATM {
protected:
    static int atmCnt;
    int serialNum; // ATM 시리얼 넘버
    Bank* primaryBank; // 주거래 은행
    unsigned long long cashAmount;  // ATM에 들어있는 현금
    vector<vector<Transaction>> transactionHistoryOfATM; // ATM 전체 transaction history (Admin에서 접근 가능)
    string AdminNum; // Admin 넘버
    Session session; // 세션
    int SingleOrMulti; // 0: Single , 1: Multi
public:
    ATM() {}
    string getPrimaryBankInfo() {return primaryBank->getBankName();}
    int getSerialNum() {return serialNum;}
    Bank* getPrimaryBank() {return primaryBank;}
    unsigned long long getCashAmount() {return cashAmount;}
    int getSingleInfo() {return SingleOrMulti;}
    void addTransaction(vector<Transaction> transac) {transactionHistoryOfATM.push_back(transac);}
    virtual void startSession() = 0;
    virtual string getClassName() = 0;
    virtual ~ATM() = default;
};

int ATM::atmCnt{ 1 };

vector<ATM*> atmData;





/*-------------- Children Classes of Session Class --------------*/

/*---------- Korean Session Class -----------*/

class KoreanSession : public Session {
public:
    KoreanSession(ATM* atm) {}
};

/*---------- English Session Class ----------*/

class EnglishSession : public Session {
public:
    EnglishSession(ATM* atm) {
        authorizationCount = 0;
        authorizationSignal = true;
        string inputAccount;
        cout << "Enter your Account Number\n" << endl;
        cout << "Account Number : ";
        cin >> inputAccount;
        if (atm->getSingleInfo() == 0) account = findBank(atm->getPrimaryBankInfo())->findAccount(inputAccount);
        else{
            cout << "\n--------------------------------------------------\n" << endl;
            cout << "Choose your bank number of this account" << endl;
            for (int i = 0; i < bankData.size(); i++) {
                if (i % 3 == 0) cout << "\n";
                cout << right << setfill('0') << setw(2) << i+1 << left << setfill(' ') << setw(8) << bankData[i].getBankName() << "    ";
            }
            cout << "\n";
            cout << "Enter the bank number : ";
            int bankNum;
            cin >> bankNum;
            account = bankData[bankNum-1].findAccount(inputAccount);
        }
        for (int i = 1; i < 4; i++) {
            string inputPassword;
            cout << "\n--------------------------------------------------\n" << endl;
            cout << "Enter your Account Password\n" << endl;
            cout << "Password : ";
            cin >> inputPassword;
            if (Authorization(inputPassword)) {
                authorizationSignal = true;
                break;
            }
            else {
                authorizationSignal = false;
                authorizationCount ++;
                cout << "\n" << authorizationCount << " Authorization Fail" << endl;
            }
        }
        if (authorizationSignal == false) {
            cout << "\n--------------------------------------------------\n" << endl;
            cout << "Authorization Fail, " << endl;
        }
        else {
            bool sessionExitSignal = true;
            while (sessionExitSignal) {
                cout << "\n--------------------------------------------------\n" << endl;
                cout << "Transaction List\n" << endl;
                cout << "1. Deposit" << endl;
                cout << "2. Withdrawal" << endl;
                cout << "3. Transfer" << endl;
                cout << "4. Session Exit" << endl;
                cout << "\n";
                cout << "Enter the transaction number which you want: ";
                int transactionNum;
                cin >> transactionNum;
                
                
                if (transactionNum == 1) { // Deposit
                    cout << "\n--------------------------------------------------\n" << endl;
                    cout << "You choose the Deposit Transaction." << endl;
                    cout << "Please enter the amount what you want to deposit." << endl;
                    cout << "Amount : ";
                    int inAmount;
                    cin >> inAmount;
                    Deposit(inAmount);
                    
                    
                } else if (transactionNum == 2) { // Withdrawal
                    cout << "\n--------------------------------------------------\n" << endl;
                    cout << "You choose the Withdrawal Transaction." << endl;
                    cout << "Please enter the amount what you want to withdrawal." << endl;
                    cout << "Amount : ";
                    int inAmount;
                    cin >> inAmount;
                    Withdrawal(inAmount);
                    
                    
                } else if (transactionNum == 3) { // Transfer
                    cout << "\n--------------------------------------------------\n" << endl;
                    cout << "You choose the Transfer Transaction.\n" << endl;
                    cout << "1. Account Transfer (Account to Account)" << endl;
                    cout << "2. Cash Transfer (Cash to Account)\n" << endl;
                    cout << "Please enter the kind of the Transfer : " << endl;
                    int transferNum;
                    cin >> transferNum;
                    
                    if (transferNum == 1) { // Account Transfer
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "You choose the Account Transfer Transaction." << endl;
                        cout << "Please enter the amount what you want to transfer." << endl;
                        cout << "Amount : ";
                        int inAmount;
                        cin >> inAmount;
                        cout << "Please enter the bank name of destination account : ";
                        string inDestName;
                        cin >> inDestName;
                        cout << "Please enter the destination account : ";
                        string inDest;
                        cin >> inDest;
                        AccountTransfer(inAmount, findBank(inDestName)->findAccount(inDest));
                        
                    } else if (transferNum == 2) { // Cash Transfer
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "You choose the Cash Transfer Transaction." << endl;
                        cout << "Please enter the amount what you want to transfer." << endl;
                        cout << "Amount : ";
                        int inAmount;
                        cin >> inAmount;
                        cout << "Please enter the bank name of destination account : ";
                        string inDestName;
                        cin >> inDestName;
                        cout << "Please enter the destination account : ";
                        string inDest;
                        cin >> inDest;
                        CashTransfer(inAmount, findBank(inDestName)->findAccount(inDest));
                        
                    }  else { // Exception
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "It's an invalid number. Please retry." << endl;
                    }
                    
                    
                } else if (transactionNum == 4) { // Session Exit
                    sessionExitSignal = false;
                }
                
                
                else { // Exception
                    cout << "\n--------------------------------------------------\n" << endl;
                    cout << "It's an invalid number. Please retry." << endl;
                }
            }
            atm->addTransaction(transactionHistoryOfSession);
        }
    }
};





/*---------------- Children Classes of ATM Class ----------------*/

/*---------- Single Bank ATM Class ----------*/

class SingleBankATM : public ATM {
public:
    SingleBankATM(string priName) {
        serialNum = atmCnt++;
        primaryBank = findBank(priName);
        cashAmount = 10000000;
        SingleOrMulti = 0;
    }
    void startSession() {}
    string getClassName() {return "Single";}
};

/*---------- Multi Bank ATM Class -----------*/

class MultiBankATM : public ATM {
public:
    MultiBankATM(string priName) {
        serialNum = atmCnt++;
        primaryBank = findBank(priName);
        cashAmount = 10000000;
        SingleOrMulti = 1;
    }
    void startSession() {}
    string getClassName() {return "Multi";}
};

/*---------- Unilingual ATM Class -----------*/

class UnilingualATM : public ATM {
public:
    UnilingualATM(ATM* atm) {
        serialNum = atm->getSerialNum();
        primaryBank = atm->getPrimaryBank();
        cashAmount = atm->getCashAmount();
        SingleOrMulti = atm->getSingleInfo();
    }
    string getClassName() {return "Unilingual";}
    void startSession() {
        EnglishSession newSession(this);
        session = newSession;
    }
};

/*----------- Bilingual ATM Class -----------*/

class BilingualATM : public ATM {
public:
    BilingualATM(ATM* atm) {
        serialNum = atm->getSerialNum();
        primaryBank = atm->getPrimaryBank();
        cashAmount = atm->getCashAmount();
        SingleOrMulti = atm->getSingleInfo();
    }
    string getClassName() {return "Bilingual";}
    void startSession() {
        while (true) {
            cout << "Choose the Language\n" << endl;
            cout << "1. English" << endl;
            cout << "2. Korean" << endl;
            cout << "3. Go to HOME\n" << endl;
            cout << "Please Enter the Number of Language : ";
            int languageNum;
            cin >> languageNum;
            if (languageNum == 1) {
                cout << "\n--------------------------------------------------\n" << endl;
                EnglishSession newSession(this);
                session = newSession;
            } else if (languageNum == 2) {
                cout << "\n--------------------------------------------------\n" << endl;
                KoreanSession newSession(this);
                session = newSession;
            } else if (languageNum == 3) {
                break;
            } else {
                cout << "It's an invalid number." << endl;
            }
        }
    }
};





/*------------------------------------- FILE Read Function ------------------------------------*/
vector<string> split(string input, char delimeter) {
    vector<string> result;
    stringstream in(input);
    string temp;
    
    while (getline(in, temp, delimeter)) {
        result.push_back(temp);
    }
    
    return result;
}

void readAtmData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(6);
    } else {
        while (!fin.eof()) {
            string str;
            getline(fin, str);
            vector<string> splitted = split(str, ' ');
            ATM* newAtm;
            if (splitted[1].compare("Single") == 0) {
                newAtm = new SingleBankATM(splitted[0]);
            } else if (splitted[1].compare("Multi") == 0) {
                newAtm = new MultiBankATM(splitted[0]);
            } else {
                cout << "입력 파일 오류" << endl;
                exit(7);
            }
            if (splitted[2].compare("Bi") == 0) {
                newAtm = new BilingualATM(newAtm);
            } else if (splitted[2].compare("Uni") == 0) {
                newAtm = new UnilingualATM(newAtm);
            } else {
                cout << "입력 파일 오류" << endl;
                exit(8);
            }
            atmData.push_back(newAtm);
        }
    }
}

void readBankData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(9);
    } else {
        while (!fin.eof()) {
            string str;
            getline(fin, str);
            Bank newBank(str);
            bankData.push_back(newBank);
        }
    }
}

void readAccountData(ifstream& fin) {
    if (!fin) {
        cout << "해당 파일이 존재하지 않습니다." << endl;
        exit(10);
    } else {
        while (!fin.eof()) {
            string str;
            getline(fin, str);
            vector<string> splitted = split(str, ' ');
            Account newAccount(splitted[1], splitted[2], splitted[3], splitted[4]);
            findBank(splitted[0])->addAccount(newAccount);
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
     argv[1] ~ argv[3] : Bank.txt, ATM.txt, Account.txt
     -> 따라서 argc는 4
    */
    
    
    /*
     자신의 환경에 따라 두 가지 조건 중 자신이 해당되는 것을 골라 그렇지 않은 케이스의 코드 주석 처리하여 사용하시오.
     1. Xcode(Mac OS) 이거나 VScode(Window OS) 에서 코드를 실행할 경우 --->>> Case 1 사용
     2. Terminal 에서 코드를 직접 컴파일하여 사용할 경우 --->>> Case 2 사용
     */
    
    /*------------------------------------------------------- Case 1 Start -------------------------------------------------------*/
    // 해당 파일이 동일한 디렉토리에 있어야 됨.
        /*
         Xcode의 경우, "Product" -> "Scheme" -> "Edit Scheme" -> "Run" -> "Options"
         -> "Working Directory"에서 "Use custom working directory" 체크
        */
    ifstream f2("Bank.txt");
    readBankData(f2);
    ifstream f1("ATM.txt");
    readAtmData(f1);
    ifstream f3("Account.txt");
    readAccountData(f3);
    /*-------------------------------------------------------- Case 1 End --------------------------------------------------------*/
    
    
    /*------------------------------------------------------- Case 2 Start -------------------------------------------------------*/
//    // 해당 파일이 동일한 디렉토리에 있어야 됨.
//    int atmArgCount = 0;
//    int bankArgCount = 0;
//    int accountArgCount = 0;
//
//    if (argc != 4) { // Argument 수가 맞지 않을때
//        cout << "Argument 부족" << endl;
//        return 1;
//    } else { // 정상 실행
//        for (int i = 1; i < argc; i++) {
//            if (strncmp(argv[i], "ATM.txt", 7) == 0) { // Argument 가 ATM.txt 일 경우
//                if (atmArgCount != 0) { // ATM argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
//                    cout << "Too many ATM arguments..." << endl;
//                    return 2;
//                } else { // 정상 실행
//                    ifstream fin(argv[i]); // 파일 read
//                    readAtmData(fin);
//                    atmArgCount ++;
//                }
//            } else if (strncmp(argv[i], "Bank.txt", 8) == 0) { // Argument 가 Bank.txt 일 경우
//                if (bankArgCount != 0) { // Bank argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
//                    cout << "Too many Bank arguments..." << endl;
//                    return 3;
//                } else { // 정상 실행
//                    ifstream fin(argv[i]); // 파일 read
//                    readBankData(fin);
//                    bankArgCount ++;
//                }
//            } else if (strncmp(argv[i], "Account.txt", 11) == 0) { // Argument 가 Account.txt 일 경우
//                if (accountArgCount != 0) { // Account argument 가 이미 한 번 나왔는데 또 나왔을 경우, Error 발생
//                    cout << "Too many Account arguments..." << endl;
//                    return 4;
//                } else { // 정상 실행
//                    ifstream fin(argv[i]); // 파일 read
//                    readAccountData(fin);
//                    accountArgCount ++;
//                }
//            } else { // Exception
//                cout << argv[i] << "의 파일명이 invalid 합니다..." << endl;
//                return 5;
//            }
//        }
//    }
    /*-------------------------------------------------------- Case 2 End --------------------------------------------------------*/
    
    bool programEndSignal = true;
    
    while (programEndSignal) {
        cout << "Choose the ATM" << endl;
        for (int i = 0; i < atmData.size(); i++) {
            if (i % 2 == 0) {
                cout << "\n";
            }
            cout << right << setfill('0') << setw(2) << i+1 << ". " << right << setfill(' ') << setw(8) << atmData[i]->getPrimaryBankInfo() << " ";
            if (atmData[i]->getSingleInfo() == 0) {
                cout << "Single  ";
            } else cout << "Multi   ";
            cout << left << setw(10) << atmData[i]->getClassName() << " ATM      ";
        }
        cout << "\n";
        cout << atmData.size()+1 << ".  Program Exit\n" << endl;
        cout << "Please Enter the Number of ATM : ";
        int choiceAtm;
        cin >> choiceAtm;
        cout << "\n--------------------------------------------------\n" << endl;
        if (choiceAtm == atmData.size()+1) {
            programEndSignal = false;
        }
        else {
            atmData[choiceAtm-1]->startSession();
        }
    }
    
    return 0;
}
