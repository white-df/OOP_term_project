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
    unsigned long long availableFunds = 0;
    vector<Transaction> transactionHistoryOfAccount;
public:
    Account() {}
    Account(string aNum, string aPW, string uName, string funds) {
        accountNumber = aNum;
        accountPw = aPW;
        userName = uName;
        availableFunds = stoull(funds);
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
    unsigned long long getFundInfo() {return availableFunds;}
    vector<Transaction> getTransactionHistoryOfAccount() {return transactionHistoryOfAccount;}
};





/*------------------------------------------------ Transaction Class ---------------------------------------------------*/
/*--------------거래내역 남기는 법: Session에서 거래 시작 시 Transaction* transaction 선언 후 거래 종료 시,--------------*/
/*---transaction = new {deposit, withdraw, transfer 중 1}Transaction(transaction, (dest account), account, amount)---*/

//class Transaction : public Account {
class Transaction {
protected:
    static unsigned long long transactionCnt;
    unsigned long long ID = transactionCnt;
    unsigned long long Amount = 0;
    string description = "#";
    Account* account;
public:
    unsigned long long getID() { return ID; }
    unsigned long long getAmount() { return Amount; }
    string getInformation() {return description;}
};

unsigned long long Transaction::transactionCnt{ 1 };


/*------------ Children Classes of Transaction Class ------------*/

/*-------- Deposit Transaction Class --------*/
class DepositTransaction : public Transaction {
public:
    DepositTransaction(Account* acc, unsigned long long amount);
//    string getInformation();
};
DepositTransaction::DepositTransaction(Account* acc, unsigned long long amount) {
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(ID));
    description.append(". Account number '");
    description.append(account->getAccountNumber());
    description.append("' deposited ");
    description.append(to_string(amount));
    description.append(" won");
}

//string DepositTransaction::getInformation() {
//    return description;
//} /* ex. 1 1234 5678 deposited 100$ */
//  /* ex. 2 1234 5678 withdrew 50$ */

/*------- Withdrawal Transaction Class ------*/
class WithdrawalTransaction : public Transaction {
public:
    WithdrawalTransaction(Account* acc, unsigned long long amount);
//    string getInformation();
};

WithdrawalTransaction::WithdrawalTransaction(Account* acc, unsigned long long amount) {
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(ID));
    description.append(". Account number '");
    description.append(account->getAccountNumber());
    description.append("' withdrew ");
    description.append(to_string(amount));
    description.append(" won");
}


//string WithdrawalTransaction::getInformation() {
//    return description;
//}

/*-------- Transfer Transaction Class -------*/
class TransferTransaction : public Transaction {
protected:
    Account* destaccount;
};

class AccountTransferTransaction : public TransferTransaction {
public:
    AccountTransferTransaction(Account* destacc, Account* account, unsigned long long amount);
//    string getInformation();
};
AccountTransferTransaction::AccountTransferTransaction(Account* destacc, Account* acc, unsigned long long amount) {
    destaccount = destacc;
    account = acc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(ID));
    description.append(". Account number '");
    description.append(account->getAccountNumber());
    description.append("' transfer to ");
    description.append(destaccount->getAccountNumber()).append(" ");
    description.append(to_string(amount));
    description.append(" won");
}


//string AccountTransferTransaction::getInformation() {
//    return description;
//}

class CashTransferTransaction : public TransferTransaction {
public:
    CashTransferTransaction(Account* destaccount, Account* account, unsigned long long amount);
//    string getInformation();
};
CashTransferTransaction::CashTransferTransaction(Account* destacc, Account* acc, unsigned long long amount) {
    destaccount = destacc;
    Amount = amount;
    ID = transactionCnt++;
    description.append(to_string(ID));
    description.append(". Account number '");
    description.append(account->getAccountNumber());
    description.append("' transfer to ");
    description.append(destaccount->getAccountNumber()).append(" ");
    description.append(to_string(amount));
    description.append(" won");
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
    Account* findAccountOfBank(string account);
    void addAccount(Account account) {accounts.push_back(account);}
};

Account* Bank::findAccountOfBank(string account) {
    int i;
    for (i = 0; i < accounts.size(); i++) {
        if (accounts[i].compareAccount(account)) {
            return &accounts[i];
            break;
        }
    }
    return nullptr;
}

vector<Bank> bankData;

Bank* findBank(string name) {
    int i;
    for (i = 0; i < bankData.size(); i++) {
        if (bankData[i].getBankName().compare(name) == 0) {
            return &bankData[i];
            break;
        }
    }
    return nullptr;
}

Bank* findAccount(string account) {
    for (int i = 0; i < bankData.size(); i++) {
        if (bankData[i].findAccountOfBank(account) != nullptr) {
            return &bankData[i];
            break;
        }
    }
    return nullptr;
}



/*--------------------------------------- Session Class ---------------------------------------*/

class ATM;

class Session {
protected:
    ATM* atm;
    Account* account;
    vector<Transaction> transactionHistoryOfSession;
    bool authorizationSignal;
    int authorizationCount;
    int withdrawalCount;
    bool primarySignal; // 현재 account의 은행 정보와 ATM의 주거래 은행이 동일하면 true
public:
    Session() {}
    void CashDeposit(unsigned long long amount);
    void CheckDeposit(unsigned long long amount);
    void Withdrawal(unsigned long long amount);
    void CashTransfer(unsigned long long amount, Account* destination);
    void AccountTransfer(unsigned long long amount, Account* destination);
    bool Authorization(string password) {return account->check_pw(password);}
};





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
    void plusMoney(unsigned long long amount) {cashAmount += amount;}
    void minusMoney(unsigned long long amount) {cashAmount -= amount;}
    void startKoreanAdminSession();
    void startEnglishAdminSession();
    virtual void startSession() = 0;
    virtual string getClassName() = 0;
    virtual ~ATM() = default;
};

int ATM::atmCnt{ 1 };

vector<ATM*> atmData;





/*-------------- Methods of Session Class --------------*/

void Session::CashDeposit(unsigned long long amount) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 500;
    atm->plusMoney(amount);
    account->plusMoney(amount - fee);
    DepositTransaction newTransaction(account, amount);
    account->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout <<"\n";
    cout << newTransaction.getInformation() << endl;
    cout << "Current Available Funds : " << account->getFundInfo() << " won" << endl;
}

void Session::CheckDeposit(unsigned long long amount) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 500;
    account->plusMoney(amount - fee);
    DepositTransaction newTransaction(account, amount);
    account->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout <<"\n";
    cout << newTransaction.getInformation() << endl;
    cout << "Current Available Funds : " << account->getFundInfo() << " won" << endl;
}

void Session::Withdrawal(unsigned long long amount) {
    unsigned long long fee = 500;
    if (!primarySignal) fee = 1000;
    if (atm->getCashAmount() < amount) {
        cout << "\nOur ATM doesn't have enough money." << endl;
    }
    else if (amount + fee > account->getFundInfo()) {
        cout << "\nYou don't have enough money." << endl;
    }
    else {
        account->minusMoney(amount + fee);
        WithdrawalTransaction newTransaction(account, amount);
        account->addTransaction(&newTransaction);
        transactionHistoryOfSession.push_back(newTransaction);
        cout <<"\n";
        cout << newTransaction.getInformation() << endl;
        withdrawalCount ++;
        cout << "Current Available Funds : " << account->getFundInfo() << " won" << endl;
    }
}

void Session::CashTransfer(unsigned long long amount, Account* destination) {
    atm->plusMoney(amount);
    destination->plusMoney(amount);
    CashTransferTransaction newTransaction(destination, account, amount);
    destination->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    cout <<"\n";
    cout << newTransaction.getInformation() << endl;
}

void Session::AccountTransfer(unsigned long long amount, Account* destination) {
    unsigned long long fee;
    string accountNum = findBank(account->getAccountNumber())->getBankName();
    string destNum = findBank(destination->getAccountNumber())->getBankName();
    if ( (accountNum.compare(destNum) == 0) && (primarySignal == true) ) fee = 1500;
    else if ( (accountNum.compare(destNum) == 0) && (primarySignal == false) ) fee = 2500;
    else fee = 2000;
    if (amount + fee > account->getFundInfo()) {
        cout << "You don't have enough money." << endl;
    } else {
        account->minusMoney(amount + fee);
        destination->plusMoney(amount);
        AccountTransferTransaction newTransaction(destination, account, amount);
        destination->addTransaction(&newTransaction);
        account->addTransaction(&newTransaction);
        transactionHistoryOfSession.push_back(newTransaction);
        cout <<"\n";
        cout << newTransaction.getInformation() << endl;
        cout << "Current Available Funds : " << account->getFundInfo() << " won" << endl;
    }
}


/*-------------- Children Classes of Session Class --------------*/

/*---------- Korean Session Class -----------*/

class KoreanSession : public Session {
public:
    KoreanSession(ATM* atm) {}
};

/*---------- English Session Class ----------*/

class EnglishSession : public Session {
public:
    EnglishSession(ATM* iatm) {
        atm = iatm;
        primarySignal = true;
        authorizationCount = 0;
        withdrawalCount = 0;
        authorizationSignal = true;
        bool validAccount = true;
        string inputAccount;
        cout << "Enter your Account Number\n" << endl;
        cout << "Account Number : ";
        cin >> inputAccount;
        
        if (findAccount(inputAccount) == nullptr) {
            cout << "Do not exist this account number\n" << endl;
        }
        else {
            Bank* temp = findAccount(inputAccount);
            if ( (atm->getPrimaryBankInfo()).compare(temp->getBankName()) == 0 ) {
                account = temp->findAccountOfBank(inputAccount);
            } else {
                if (atm->getSingleInfo() == 0) {
                    cout << "You cannot use this account in here." << endl;
                } else {
                    primarySignal = false;
                    account = temp->findAccountOfBank(inputAccount);
                }
            }
        }
        if (validAccount) {
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
                    cout << "4. Transaction History" << endl;
                    cout << "5. Session Exit" << endl;
                    cout << "\n";
                    cout << "Enter the transaction number which you want: ";
                    int transactionNum;
                    cin >> transactionNum;
                    
                    
                    if (transactionNum == 1) { // Deposit
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "You select the Deposit Transaction." << endl;
                        cout << "You can use Cash / Check.\n" << endl;
                        cout << "Service List\n" << endl;
                        cout << "1. Cash  Deposit Service" << endl;
                        cout << "2. Check Deposit Service\n" << endl;
                        cout << "Please enter the number of service : ";
                        int x;
                        cin >> x;
                        unsigned long long inAmount;
                        if (x == 1) {
                            while (true) {
                                cout << "\nPlease enter the number of 10,000 won bills.\n" << endl;
                                cout << "The number of bills : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 50) {inAmount = 10000 * numBill; break;}
                                else {cout << "\nYou over a limit in the number of cash that can be deposited per transaction." << endl;}
                            }
                            CashDeposit(inAmount);
                        } else if (x == 2) {
                            while (true) {
                                cout << "\nPlease enter the number of 100,000 won checks.\n" << endl;
                                cout << "The number of checks : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 30) {inAmount = 100000 * numBill; break;}
                                else {cout << "\nYou over a limit in the number of check that can be deposited per transaction." << endl;}
                            }
                            CheckDeposit(inAmount);
                        } else {cout << "\nIt's an invalid number. Please retry." << endl;}
                        
                        
                    } else if (transactionNum == 2) { // Withdrawal
                        if (withdrawalCount == 3) cout << "\nYou over a limit in the number of withdrawal of fund per session." << endl;
                        else {
                            unsigned long long inAmount;
                            int aNum;
                            while (true) {
                                cout << "\n--------------------------------------------------\n" << endl;
                                cout << "You select the Withdrawal Transaction.\n" << endl;
                                cout << "Select the amount what you want to withdrawal.\n" << endl;
                                cout << "1. 10,000 won     2. 20,000 won     3. 30,000 won" << endl;
                                cout << "4. 40,000 won     5. 50,000 won     6. 100,000 won" << endl;
                                cout << "7. Other Amount\n" << endl;
                                cout << "Enter the number : ";
                                cin >> aNum;
                                if (aNum == 1) {inAmount = 10000;}
                                else if (aNum == 2) {inAmount = 20000; break;}
                                else if (aNum == 3) {inAmount = 30000; break;}
                                else if (aNum == 4) {inAmount = 40000; break;}
                                else if (aNum == 5) {inAmount = 50000; break;}
                                else if (aNum == 6) {inAmount = 100000; break;}
                                else if (aNum == 7) {
                                    while (true) {
                                        cout << "Enter the amount in units of 10,000 won : ";
                                        cin >> inAmount;
                                        if ((inAmount % 10000 == 0) && (inAmount <= 500000)) break;
                                        if (inAmount > 500000) cout << "You over a limit in the amount of withdrawal of fund per transaction.\n" << endl;
                                        if (inAmount % 10000 != 0) cout << "You should enter the amount in units of 10,000 won.\n" << endl;
                                    }
                                    break;
                                }
                                cout << "It's an invalid number. Please retry." << endl;
                            }
                            Withdrawal(inAmount);
                        }
                        
                        
                        
                    } else if (transactionNum == 3) { // Transfer
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "You select the Transfer Transaction.\n" << endl;
                        cout << "1. Account Transfer (Account to Account)" << endl;
                        cout << "2. Cash Transfer (Cash to Account)\n" << endl;
                        cout << "Please enter the kind of the Transfer : " << endl;
                        int transferNum;
                        cin >> transferNum;
                        
                        if (transferNum == 1) { // Account Transfer
                            cout << "\n--------------------------------------------------\n" << endl;
                            cout << "You select the Account Transfer Transaction." << endl;
                            cout << "Please enter the amount what you want to transfer." << endl;
                            cout << "Amount : ";
                            unsigned long long inAmount;
                            cin >> inAmount;
                            cout << "Please enter the bank name of destination account : ";
                            string inDestName;
                            cin >> inDestName;
                            cout << "Please enter the destination account : ";
                            string inDest;
                            cin >> inDest;
                            AccountTransfer(inAmount, findBank(inDestName)->findAccountOfBank(inDest));
                            
                        } else if (transferNum == 2) { // Cash Transfer
                            unsigned long long inAmount;
                            int aNum;
                            while (true) {
                                cout << "\n--------------------------------------------------\n" << endl;
                                cout << "You select the Cash Transfer Transaction.\n" << endl;
                                cout << "Select the amount what you want to transfer.\n" << endl;
                                cout << "1. 10,000 won     2. 20,000 won     3. 30,000 won" << endl;
                                cout << "4. 40,000 won     5. 50,000 won     6. 100,000 won" << endl;
                                cout << "7. Other Amount\n" << endl;
                                cout << "Enter the number : ";
                                cin >> aNum;
                                if (aNum == 1) {inAmount = 10000;}
                                else if (aNum == 2) {inAmount = 20000; break;}
                                else if (aNum == 3) {inAmount = 30000; break;}
                                else if (aNum == 4) {inAmount = 40000; break;}
                                else if (aNum == 5) {inAmount = 50000; break;}
                                else if (aNum == 6) {inAmount = 100000; break;}
                                else if (aNum == 7) {
                                    while (true) {
                                        cout << "Enter the amount in units of 10,000 won : ";
                                        cin >> inAmount;
                                        if ((inAmount % 10000 == 0) && (inAmount <= 500000)) break;
                                        if (inAmount > 500000) cout << "You over a limit in the amount of transfer of fund per transaction.\n" << endl;
                                        if (inAmount % 10000 != 0) cout << "You should enter the amount in units of 10,000 won.\n" << endl;
                                    }
                                    break;
                                }
                                cout << "It's an invalid number. Please retry." << endl;
                            }
                            cout << "Please enter the bank name of destination account : ";
                            string inDestName;
                            cin >> inDestName;
                            cout << "Please enter the destination account : ";
                            string inDest;
                            cin >> inDest;
                            CashTransfer(inAmount, findBank(inDestName)->findAccountOfBank(inDest));
                            
                        }  else { // Exception
                            cout << "\n--------------------------------------------------\n" << endl;
                            cout << "It's an invalid number. Please retry." << endl;
                        }
                        
                        
                    } else if (transactionNum == 4) { // Transaction History
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "You select the Transaction History.\n" << endl;
                        cout << "Transaction History of yout account\n" << endl;
                        vector<Transaction> temp =account->getTransactionHistoryOfAccount();
                        if (temp.size() == 0) {
                            cout << "This account doesn't have any transaction history.\n" << endl;
                        } else {
                            for (int i = 0; i < temp.size(); i++) {
                                cout << temp[i].getInformation() << endl;
                            }
                            cout << "\nEnd of List\n\n" << endl;
                        }
                        
                    } else if (transactionNum == 5) { // Session Exit
                        sessionExitSignal = false;
                    }
                    
                    
                    else { // Exception
                        cout << "\n--------------------------------------------------\n" << endl;
                        cout << "It's an invalid number. Please retry." << endl;
                    }
                }
                cout << "\n--------------------------------------------------\n" << endl;
                cout << "Session End. Thank you for using our ATM\n" << endl;
                cout << "Transaction History of Session\n" << endl;
                if (transactionHistoryOfSession.size() == 0) {
                    cout << "This session doesn't have any transaction history.\n" << endl;
                } else {
                    atm->addTransaction(transactionHistoryOfSession);
                    for (int i = 0; i < transactionHistoryOfSession.size(); i++) {
                        cout << transactionHistoryOfSession[i].getInformation() << endl;
                    }
                    cout << "\nEnd of List\n\n" << endl;
                }
            }
        }
    }
};





/*---------------- Method of ATM Class ----------------*/

void ATM::startEnglishAdminSession() {
    cout << "\n--------------------------------------------------\n" << endl;
    cout << "You select the Admin Menu.\n" << endl;
    cout << "Please enter the Admin Card Number." << endl;
    cout << "=> : ";
    string inAdmin;
    cin >> inAdmin;
    if (inAdmin.compare(AdminNum) == 0) {
        while (true) {
            cout << "\n--------------------------------------------------\n" << endl;
            cout << "Select the admin service\n" << endl;
            cout << "Service List" << endl;
            cout << "1. Transaction History of ATM" << endl;
            cout << "2. Admin Session Exit" << endl;
            cout << "\nEnter the number : ";
            int num;
            cin >> num;
            if (num == 1) {
                if (transactionHistoryOfATM.size() == 0) {
                    cout << "\nIt does not exist any transaction history in the ATM.\n" << endl;
                } else {
                    ofstream fout;
                    fout.open("Transaction History of ATM.txt");
                    if (!fout) cout << "File Error" << endl;
                    else {
                        fout << "Admin Serial No. : " << this->getSerialNum() << endl;
                        for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                            for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                                fout << transactionHistoryOfATM[i][j].getInformation();
                                fout << "\n";
                            }
                        }
                    }
                    for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                        for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                            cout << transactionHistoryOfATM[i][j].getInformation() << endl;
                        }
                    }
                }
            } else if (num == 2) {
                cout << "\nAdmin Session Exit\n" << endl;
                break;
            } else {
                cout << "\nIt's an invalid number. Please Re-try.\n" << endl;
            }
        }
    } else {
        cout << "\nIt's an invalid admin card number. Please Re-try.\n" << endl;
    }
}

void ATM::startKoreanAdminSession() {
    cout << "\n--------------------------------------------------\n" << endl;
    cout << "관리자 모드에 접근하셨습니다.\n" << endl;
    cout << "관리자 카드 번호를 입력해주세요." << endl;
    cout << "=> : ";
    string inAdmin;
    cin >> inAdmin;
    if (inAdmin.compare(AdminNum) == 0) {
        while (true) {
            cout << "\n--------------------------------------------------\n" << endl;
            cout << "관리자 모드에 오신 것을 환영합니다.e\n" << endl;
            cout << "서비스 목록" << endl;
            cout << "1. ATM 기기에 저장된 전체 거래 기록 출력" << endl;
            cout << "2. 관리자 모드 종료" << endl;
            cout << "\n번호를 입력해주세요 : ";
            int num;
            cin >> num;
            if (num == 1) {
                if (transactionHistoryOfATM.size() == 0) {
                    cout << "\n현재 해당 ATM 기기에는 저장된 거래 기록이 존재하지 않습니다..\n" << endl;
                } else {
                    ofstream fout;
                    fout.open("Transaction History of ATM.txt");
                    if (!fout) cout << "출력 파일 오류" << endl;
                    else {
                        fout << "Admin Serial No. : " << this->getSerialNum() << endl;
                        for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                            for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                                fout << transactionHistoryOfATM[i][j].getInformation();
                                fout << "\n";
                            }
                        }
                    }
                    for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                        for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                            cout << transactionHistoryOfATM[i][j].getInformation() << endl;
                        }
                    }
                }
            } else if (num == 2) {
                cout << "\n관리자 모드 종료\n" << endl;
                break;
            } else {
                cout << "\n유효하지 않은 번호입니다. 다시 한 번 시도해주시길 바랍니다.\n" << endl;
            }
        }
    } else {
        cout << "\n유효하지 않은 번호입니다. 다시 한 번 시도해주시길 바랍니다.\n" << endl;
    }
}


/*---------------- Children Classes of ATM Class ----------------*/

/*---------- Single Bank ATM Class ----------*/

class SingleBankATM : public ATM {
public:
    SingleBankATM(string priName) {
        serialNum = atmCnt++;
        primaryBank = findBank(priName);
        cashAmount = 100000000000000;
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
        cashAmount = 100000000000000;
        SingleOrMulti = 1;
    }
    void startSession() {}
    string getClassName() {return "Multi";}
};

/*---------- Unilingual ATM Class -----------*/

class UnilingualATM : public ATM {
public:
    UnilingualATM(ATM* atm, string admin) {
        serialNum = atm->getSerialNum();
        primaryBank = atm->getPrimaryBank();
        cashAmount = atm->getCashAmount();
        SingleOrMulti = atm->getSingleInfo();
        AdminNum = admin;
    }
    string getClassName() {return "Unilingual";}
    void startSession() {
        while (true) {
            cout << "Menu\n" << endl;
            cout << "1. Transaction" << endl;
            cout << "2. Admin" << endl;
            cout << "3. Go to HOME\n" << endl;
            cout << "Please Enter the Number of Language : ";
            int languageNum;
            cin >> languageNum;
            if (languageNum == 1) {
                cout << "\n--------------------------------------------------\n" << endl;
                EnglishSession newSession(this);
                session = newSession;
            } else if (languageNum == 2) {
                startEnglishAdminSession();
            } else if (languageNum == 3) {
                break;
            } else {
                cout << "It's an invalid number." << endl;
            }
        }
    }
};

/*----------- Bilingual ATM Class -----------*/

class BilingualATM : public ATM {
public:
    BilingualATM(ATM* atm, string admin) {
        serialNum = atm->getSerialNum();
        primaryBank = atm->getPrimaryBank();
        cashAmount = atm->getCashAmount();
        SingleOrMulti = atm->getSingleInfo();
        AdminNum = admin;
    }
    string getClassName() {return "Bilingual";}
    void startSession() {
        int sign = startEnglishSession();
        cout << "Sign : " << sign << endl;
        if (sign != 0) {
            do {
                if (sign == 1) sign = startKoreanSession();
                else sign = startEnglishSession();
            } while (sign != 0);
        }
    }
    int startEnglishSession() {
        while (true) {
            cout << "Menu\n" << endl;
            cout << "1. Transaction" << endl;
            cout << "2. Korean" << endl;
            cout << "3. Admin" << endl;
            cout << "4. Go to HOME\n" << endl;
            cout << "Please Enter the Number of Language : ";
            int languageNum;
            cin >> languageNum;
            if (languageNum == 1) {
                cout << "\n--------------------------------------------------\n" << endl;
                EnglishSession newSession(this);
                session = newSession;
            } else if (languageNum == 2) {
                cout << "\n--------------------------------------------------\n" << endl;
                return 1;
            } else if (languageNum == 3) {
                startEnglishAdminSession();
            } else if (languageNum == 4) {
                return 0;
            } else {
                cout << "It's an invalid number." << endl;
            }
        }
    }
    int startKoreanSession() {
        while (true) {
            cout << "메뉴\n" << endl;
            cout << "1. 서비스 이용" << endl;
            cout << "2. 영어 (English)" << endl;
            cout << "3. 관리자 접근" << endl;
            cout << "4. ATM 서비스 종료\n" << endl;
            cout << "희망하시는 번호를 입려해주세요 : ";
            int languageNum;
            cin >> languageNum;
            if (languageNum == 1) {
                cout << "\n--------------------------------------------------\n" << endl;
                KoreanSession newSession(this);
                session = newSession;
            } else if (languageNum == 2) {
                cout << "\n--------------------------------------------------\n" << endl;
                return 2;
            } else if (languageNum == 3) {
                startKoreanAdminSession();
            } else if (languageNum == 4) {
                return 0;
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
                newAtm = new BilingualATM(newAtm, splitted[3]);
            } else if (splitted[2].compare("Uni") == 0) {
                newAtm = new UnilingualATM(newAtm, splitted[3]);
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
        cout << "Select the ATM" << endl;
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
