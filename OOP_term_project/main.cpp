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
    string englishDescription = "#";
    string koreanDescription = "#";
    Account* account;
public:
    unsigned long long getID() { return ID; }
    unsigned long long getAmount() { return Amount; }
    string getEnglishInformation() {return englishDescription;}
    string getKoreanInformation() {return koreanDescription;}
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
    englishDescription.append(to_string(ID));
    englishDescription.append(". Account number '");
    englishDescription.append(account->getAccountNumber());
    englishDescription.append("' deposited ");
    englishDescription.append(to_string(amount));
    englishDescription.append(" won");
    
    koreanDescription.append(to_string(ID));
    koreanDescription.append(". 계좌번호 '");
    koreanDescription.append(account->getAccountNumber());
    koreanDescription.append("'에 ");
    koreanDescription.append(to_string(amount));
    koreanDescription.append(" 원이 입금되었습니다");
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
    englishDescription.append(to_string(ID));
    englishDescription.append(". Account number '");
    englishDescription.append(account->getAccountNumber());
    englishDescription.append("' withdrew ");
    englishDescription.append(to_string(amount));
    englishDescription.append(" won");
    
    koreanDescription.append(to_string(ID));
    koreanDescription.append(". 계좌번호 '");
    koreanDescription.append(account->getAccountNumber());
    koreanDescription.append("'에서 ");
    koreanDescription.append(to_string(amount));
    koreanDescription.append(" 원이 출금되었습니다");
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
    englishDescription.append(to_string(ID));
    englishDescription.append(". Account number '");
    englishDescription.append(account->getAccountNumber());
    englishDescription.append("' transfer to account number '");
    englishDescription.append(destaccount->getAccountNumber()).append("' ");
    englishDescription.append(to_string(amount));
    englishDescription.append(" won");
    
    koreanDescription.append(to_string(ID));
    koreanDescription.append(". 계좌번호 '");
    koreanDescription.append(account->getAccountNumber());
    koreanDescription.append("' 에서 계좌번호 '");
    koreanDescription.append(destaccount->getAccountNumber()).append("' 로 ");
    koreanDescription.append(to_string(amount));
    koreanDescription.append(" 원을 송금하였습니다");
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
    englishDescription.append(to_string(ID));
    englishDescription.append(". Account number '");
    englishDescription.append(account->getAccountNumber());
    englishDescription.append("' transfer to account number '");
    englishDescription.append(destaccount->getAccountNumber()).append("' ");
    englishDescription.append(to_string(amount));
    englishDescription.append(" won");
    
    koreanDescription.append(to_string(ID));
    koreanDescription.append(". 계좌번호 '");
    koreanDescription.append(account->getAccountNumber());
    koreanDescription.append("' 에서 계좌번호 '");
    koreanDescription.append(destaccount->getAccountNumber()).append("' 로 ");
    koreanDescription.append(to_string(amount));
    koreanDescription.append(" 원을 송금하였습니다");
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
    void CashDeposit(unsigned long long amount, int x);
    void CheckDeposit(unsigned long long amount, int x);
    void Withdrawal(unsigned long long amount, int x);
    void CashTransfer(unsigned long long amount, Account* destination, int x);
    void AccountTransfer(unsigned long long amount, Account* destination, int x);
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
    void mainEnglishDisplay() {
        cout << "\n==================================================" << endl;
        cout << "                     " << this->getPrimaryBankInfo() << " BANK" << endl;
        cout << "                     <";
        if (this->getSingleInfo() == 0) cout << "SINGLE>" << endl;
        else cout << "MULTI>" << endl;
        cout << "--------------------------------------------------\n" << endl;
    }
    void mainKoreanDisplay() {
        cout << "\n==================================================" << endl;
        cout << "                     " << this->getPrimaryBankInfo() << " 은행" << endl;
        cout << "                  <";
        if (this->getSingleInfo() == 0) cout << "주거래 은행 전용>" << endl;
        else cout << "타은행 거래 가능>" << endl;
        cout << "--------------------------------------------------\n" << endl;
    }
    void invalidEnglishDisplay() {
        cout << "\n ----------------------------------------------- " << endl;
        cout << "             It's an INVALID number." << endl;
        cout << " ----------------------------------------------- \n" << endl;
        cout << "==================================================" << endl;
    }
    void invalidKoreanDisplay() {
        cout << "\n ----------------------------------------------- " << endl;
        cout << "               유효하지 않은 번호입니다." << endl;
        cout << " ----------------------------------------------- \n" << endl;
        cout << "==================================================" << endl;
    }
    virtual void startSession() = 0;
    virtual string getClassName() = 0;
    virtual ~ATM() = default;
};

int ATM::atmCnt{ 1 };

vector<ATM*> atmData;





/*-------------- Methods of Session Class --------------*/

void Session::CashDeposit(unsigned long long amount, int x) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 500;
    atm->plusMoney(amount);
    account->plusMoney(amount - fee);
    DepositTransaction newTransaction(account, amount);
    account->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
    else cout << newTransaction.getEnglishInformation() << endl;
    if (x == 0) cout << "\n현재 잔액 : ";
    else cout << "\nCurrent Available Funds : ";
    cout << account->getFundInfo();
    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;
    cout << "\n";
}

void Session::CheckDeposit(unsigned long long amount, int x) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 500;
    account->plusMoney(amount - fee);
    DepositTransaction newTransaction(account, amount);
    account->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
    else cout << newTransaction.getEnglishInformation() << endl;
    if (x == 0) cout << "\n현재 잔액 : ";
    else cout << "\nCURRENT BALANCE : ";
    cout << account->getFundInfo();
    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;
    cout << "\n";
}

void Session::Withdrawal(unsigned long long amount, int x) {
    unsigned long long fee = 500;
    if (!primarySignal) fee = 1000;
    if (atm->getCashAmount() < amount) {
        if (x == 0) cout << "               현재 기기 내 현금이 부족합니다\n" << endl;
        else cout << "        OUR ATM DOESN'T HAVE ENOUGH MONEY\n" << endl;
        
    }
    else if (amount + fee > account->getFundInfo()) {
        if (x == 0) cout << "                      잔액 부족\n" << endl;
        else cout << "           YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    }
    else {
        atm->minusMoney(amount);
        account->minusMoney(amount + fee);
        WithdrawalTransaction newTransaction(account, amount);
        account->addTransaction(&newTransaction);
        transactionHistoryOfSession.push_back(newTransaction);
        if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
        else cout << newTransaction.getEnglishInformation() << endl;
        withdrawalCount ++;
        if (x == 0) cout << "\n현재 잔액 : ";
        else cout << "\nCURRENT BALANCE : ";
        cout << account->getFundInfo();
        if (x == 0) cout << " 원" << endl;
        else cout << " won" << endl;
        cout << "\n";
    }
}

void Session::CashTransfer(unsigned long long amount, Account* destination, int x) {
    atm->plusMoney(amount);
    destination->plusMoney(amount);
    CashTransferTransaction newTransaction(destination, account, amount);
    destination->addTransaction(&newTransaction);
    transactionHistoryOfSession.push_back(newTransaction);
    if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
    else cout << newTransaction.getEnglishInformation() << endl;
    if (x == 0) cout << "\n현재 잔액 : ";
    else cout << "\nCURRENT BALANCE : ";
    cout << account->getFundInfo();
    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;
    cout << "\n";
}

void Session::AccountTransfer(unsigned long long amount, Account* destination, int x) {
    unsigned long long fee;
    string accountNum = (findAccount(account->getAccountNumber()))->getBankName();
    string destNum = (findAccount(destination->getAccountNumber()))->getBankName();
    if ( (accountNum.compare(destNum) == 0) && (primarySignal == true) ) fee = 1500;
    else if ( (accountNum.compare(destNum) == 0) && (primarySignal == false) ) fee = 2500;
    else fee = 2000;
    if (amount + fee > account->getFundInfo()) {
        if (x == 0) cout << "                      잔액 부족\n" << endl;
        else cout << "           YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    } else {
        account->minusMoney(amount + fee);
        destination->plusMoney(amount);
        AccountTransferTransaction newTransaction(destination, account, amount);
        destination->addTransaction(&newTransaction);
        account->addTransaction(&newTransaction);
        transactionHistoryOfSession.push_back(newTransaction);
        if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
        else cout << newTransaction.getEnglishInformation() << endl;
        if (x == 0) cout << "\n현재 잔액 : ";
        else cout << "\nCURRENT BALANCE : ";
        cout << account->getFundInfo();
        if (x == 0) cout << " 원" << endl;
        else cout << " won" << endl;
        cout << "\n";
    }
}


/*-------------- Children Classes of Session Class --------------*/

/*---------- Korean Session Class -----------*/

class KoreanSession : public Session {
public:
    KoreanSession(ATM* iatm) {
        atm = iatm;
        primarySignal = true;
        authorizationCount = 0;
        withdrawalCount = 0;
        authorizationSignal = true;
        bool validAccount = true;
        string inputAccount;
        atm->mainKoreanDisplay();
        cout << "                계좌 번호를 입력해주세요\n" << endl;
        cout << "==================================================" << endl;
        cout << "계좌 번호 : ";
        cin >> inputAccount;
        
        if (findAccount(inputAccount) == nullptr) {
            atm->mainKoreanDisplay();
            cout << "           입력한 계좌번호가 존재하지 않습니다\n" << endl;
            cout << "==================================================" << endl;
            validAccount = false;
        }
        else {
            Bank* temp = findAccount(inputAccount);
            if ( (atm->getPrimaryBankInfo()).compare(temp->getBankName()) == 0 ) {
                account = temp->findAccountOfBank(inputAccount);
            } else {
                if (atm->getSingleInfo() == 0) {
                    atm->mainKoreanDisplay();
                    cout << "            타은행 계좌는 사용하실 수 없습니다\n" << endl;
                    cout << "==================================================" << endl;
                    validAccount = false;
                } else {
                    primarySignal = false;
                    account = temp->findAccountOfBank(inputAccount);
                }
            }
        }
        if (validAccount) {
            for (int i = 1; i < 4; i++) {
                string inputPassword;
                atm->mainKoreanDisplay();
                cout << "                비밀번호를 입력해주세요\n" << endl;
                cout << "==================================================" << endl;
                cout << "비밀번호 : ";
                cin >> inputPassword;
                if (Authorization(inputPassword)) {
                    authorizationSignal = true;
                    break;
                }
                else {
                    authorizationSignal = false;
                    authorizationCount ++;
                    atm->mainKoreanDisplay();
                    cout << "               비밀번호를 " << authorizationCount << "회 틀렸습니다\n" << endl;
                    cout << "==================================================" << endl;
                }
            }
            if (authorizationSignal == false) {
                atm->mainKoreanDisplay();
                cout << "       비밀번호 입력을 3회 실패하여 세션이 종료됩니다\n" << endl;
                cout << "==================================================" << endl;
            }
            else {
                bool sessionExitSignal = true;
                while (sessionExitSignal) {
                    atm->mainKoreanDisplay();
                    cout << "             원하시는 서비스를 선택해주세요\n" << endl;
                    cout << "            1. 입금    2. 출금" << endl;
                    cout << "            3. 송금    4. 거래 내역 조회" << endl;
                    cout << "            5. 서비스 종료\n" << endl;
                    cout << "==================================================" << endl;
                    cout << "번호 입력 : ";
                    int transactionNum;
                    cin >> transactionNum;
                    
                    
                    if (transactionNum == 1) { // Deposit
                        atm->mainKoreanDisplay();
                        cout << "              입금 서비스를 선택하셨습니다\n" << endl;
                        cout << "            현금과 수표 중 하나를 선택하십시오\n" << endl;
                        cout << "            1. 현금 입금     2. 수표 입금\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "번호 입력 : ";
                        int x;
                        cin >> x;
                        unsigned long long inAmount;
                        if (x == 1) {
                            while (true) {
                                atm->mainKoreanDisplay();
                                cout << "        입금하실 1만원권 지폐의 장 수를 입력해주세요\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "1만원권 지폐 장 수 : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 50) {inAmount = 10000 * numBill; break;}
                                else {
                                    atm->mainKoreanDisplay();
                                    cout << "       거래 1회 당 입금 가능한 장 수를 초과하셨습니다\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainKoreanDisplay();
                            CashDeposit(inAmount, 0);
                            cout << "==================================================" << endl;
                        } else if (x == 2) {
                            while (true) {
                                cout << "       입금하실 10만원권 수표의 장 수를 입력해주세요\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "10만원권 수표 장 수 : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 30) {inAmount = 100000 * numBill; break;}
                                else {
                                    atm->mainKoreanDisplay();
                                    cout << "       거래 1회 당 입금 가능한 장 수를 초과하셨습니다\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainKoreanDisplay();
                            CheckDeposit(inAmount, 0);
                            cout << "==================================================" << endl;
                        } else atm->invalidKoreanDisplay();
                        
                        
                    } else if (transactionNum == 2) { // Withdrawal
                        if (withdrawalCount == 3) {
                            atm->mainKoreanDisplay();
                            cout << "       세션 1회 당 출금 가능한 액수를 초과하셨습니다\n" << endl;
                            cout << "==================================================" << endl;
                        }
                        else {
                            unsigned long long inAmount;
                            int aNum;
                            while (true) {
                                atm->mainKoreanDisplay();
                                cout << "              출금 서비스를 선택하셨습니다\n" << endl;
                                cout << "             출금하실 금액을 선택해주십시오\n" << endl;
                                cout << "1. 10,000 원       2. 20,000 원      3. 30,000 원" << endl;
                                cout << "4. 40,000 원       5. 50,000 원      6. 100,000 원" << endl;
                                cout << "7. 직접 입력\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "번호 입력 : ";
                                cin >> aNum;
                                if (aNum == 1) {inAmount = 10000; break;}
                                else if (aNum == 2) {inAmount = 20000; break;}
                                else if (aNum == 3) {inAmount = 30000; break;}
                                else if (aNum == 4) {inAmount = 40000; break;}
                                else if (aNum == 5) {inAmount = 50000; break;}
                                else if (aNum == 6) {inAmount = 100000; break;}
                                else if (aNum == 7) {
                                    while (true) {
                                        atm->mainKoreanDisplay();
                                        cout << "       희밍하는 출금 금액을 1만원 단위를 입력해주십시오\n";
                                        cout << "==================================================" << endl;
                                        cout << "출금 금액 : ";
                                        cin >> inAmount;
                                        if ((inAmount % 10000 == 0) && (inAmount <= 500000)) break;
                                        if (inAmount > 500000) {
                                            atm->mainKoreanDisplay();
                                            cout << "       거래 1회 당 출금 가능한 액수를 초과하셨습니다\n" << endl;
                                            cout << "==================================================" << endl;
                                        }
                                        if (inAmount % 10000 != 0) {
                                            atm->mainKoreanDisplay();
                                            cout << "           반드시 1만원 단위로 입력하셔야 합니다\n" << endl;
                                            cout << "==================================================" << endl;
                                        }
                                    }
                                    break;
                                }
                                atm->invalidKoreanDisplay();
                            }
                            atm->mainKoreanDisplay();
                            Withdrawal(inAmount, 0);
                            cout << "==================================================" << endl;
                        }
                        
                        
                        
                    } else if (transactionNum == 3) { // Transfer
                        atm->mainKoreanDisplay();
                        cout << "              송금 서비스를 선택하셨습니다\n" << endl;
                        cout << "             1. 계좌 송금 (계좌 -> 계좌)" << endl;
                        cout << "             2. 현금 송금 (현금 -> 계좌)\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "번호 입력 : " << endl;
                        int transferNum;
                        cin >> transferNum;
                        
                        if (transferNum == 1) { // Account Transfer
                            atm->mainKoreanDisplay();
                            cout << "            계좌 송금 서비스를 선택하셨습니다\n" << endl;
                            cout << "             송금하실 금액을 입력해주십시오\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "송금 금액 : ";
                            unsigned long long inAmount;
                            cin >> inAmount;
                            atm->mainKoreanDisplay();
                            cout << "          받으실 분의 계좌 번호를 입력해주십시오\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "받으실 분 계좌 번호 : ";
                            string inDest;
                            cin >> inDest;
                            if (findAccount(inDest) == nullptr) {
                                atm->mainKoreanDisplay();
                                cout << "           입력한 계좌번호가 존재하지 않습니다\n" << endl;
                                cout << "==================================================" << endl;
                            } else {
                                atm->mainKoreanDisplay();
                                AccountTransfer(inAmount, findAccount(inDest)->findAccountOfBank(inDest), 0);
                                cout << "==================================================" << endl;
                            }
                            
                        } else if (transferNum == 2) { // Cash Transfer
                            unsigned long long inAmount;
                            while (true) {
                                atm->mainKoreanDisplay();
                                cout << "        송금하실 1만원권 지폐의 장 수를 입력해주세요\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "1만원권 지폐 장 수 : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 50) {inAmount = 10000 * numBill; break;}
                                else {
                                    atm->mainKoreanDisplay();
                                    cout << "       거래 1회 당 송금 가능한 장 수를 초과하셨습니다\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainKoreanDisplay();
                            cout << "          받으실 분의 계좌 번호를 입력해주십시오\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "받으실 분 계좌 번호 : ";
                            string inDest;
                            cin >> inDest;
                            if (findAccount(inDest) == nullptr) {
                                atm->mainKoreanDisplay();
                                cout << "           입력한 계좌번호가 존재하지 않습니다\n" << endl;
                                cout << "==================================================" << endl;
                            } else {
                                atm->mainKoreanDisplay();
                                AccountTransfer(inAmount, findAccount(inDest)->findAccountOfBank(inDest), 0);
                                cout << "==================================================" << endl;
                            }
                            
                        }  else { // Exception
                            atm->invalidKoreanDisplay();
                        }
                        
                        
                    } else if (transactionNum == 4) { // Transaction History
                        atm->mainKoreanDisplay();
                        cout << "             거래 내역 조회를 선택하셨습니다\n" << endl;
                        cout << "          해당 계좌의 거래내역은 다음과 같습니다\n" << endl;
                        vector<Transaction> temp = account->getTransactionHistoryOfAccount();
                        if (temp.size() == 0) {
                            cout << "--------------------------------------------------\n" << endl;
                            cout << "            현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                            cout << "            해당 계좌에는 거래 내역이 업습니다\n" << endl;
                            cout << "==================================================" << endl;
                        } else {
                            for (int i = 0; i < temp.size(); i++) {
                                cout << temp[i].getKoreanInformation() << endl;
                            }
                            cout << "\n현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                            cout << "==================================================" << endl;
                        }
                        
                    } else if (transactionNum == 5) { // Session Exit
                        sessionExitSignal = false;
                    }
                    
                    
                    else { // Exception
                        atm->invalidKoreanDisplay();
                    }
                }
                atm->mainKoreanDisplay();
                cout << "                     세션 종료" << endl;
                cout << "           저희 ATM을 이용해주셔서 감사합니다\n" << endl;
                if (transactionHistoryOfSession.size() == 0) {
                    cout << "            해당 세션에는 거래 내역이 업습니다\n" << endl;
                } else {
                    cout << "==================================================" << endl;
                    cout << "               해당 세션 내 총 거래 내역" << endl;
                    cout << "==================================================" << endl;
                    atm->addTransaction(transactionHistoryOfSession);
                    for (int i = 0; i < transactionHistoryOfSession.size(); i++) {
                        cout << transactionHistoryOfSession[i].getKoreanInformation() << endl;
                    }
                }
            }
        }
    }
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
        atm->mainEnglishDisplay();
        cout << "        PLEASE ENTER YOUR ACCOUNT NUMBER\n" << endl;
        cout << "==================================================" << endl;
        cout << "Account Number : ";
        cin >> inputAccount;
        
        if (findAccount(inputAccount) == nullptr) {
            atm->mainEnglishDisplay();
            cout << "  THE ACCOUNT NUMBER YOU ENTERED DOES NOT EXIST\n" << endl;
            cout << "==================================================" << endl;
            validAccount = false;
        }
        else {
            Bank* temp = findAccount(inputAccount);
            if ( (atm->getPrimaryBankInfo()).compare(temp->getBankName()) == 0 ) {
                account = temp->findAccountOfBank(inputAccount);
            } else {
                if (atm->getSingleInfo() == 0) {
                    atm->mainEnglishDisplay();
                    cout << "           YOU CAN'T USE OTHER BANK CARDS\n" << endl;
                    cout << "==================================================" << endl;
                    validAccount = false;
                } else {
                    primarySignal = false;
                    account = temp->findAccountOfBank(inputAccount);
                }
            }
        }
        if (validAccount) {
            for (int i = 1; i < 4; i++) {
                string inputPassword;
                atm->mainEnglishDisplay();
                cout << "            PLEASE ENTER THE PASSWORD.\n" << endl;
                cout << "==================================================" << endl;
                cout << "Password : ";
                cin >> inputPassword;
                if (Authorization(inputPassword)) {
                    authorizationSignal = true;
                    break;
                }
                else {
                    authorizationSignal = false;
                    authorizationCount ++;
                    atm->mainEnglishDisplay();
                    cout << "              " << authorizationCount << " AUTHORIZATION FAIL\n" << endl;
                    cout << "==================================================" << endl;
                }
            }
            if (authorizationSignal == false) {
                atm->mainEnglishDisplay();
                cout << "       3 AUTHORIZATION FAIL, SESSION EXIT\n" << endl;
                cout << "==================================================" << endl;
            }
            else {
                bool sessionExitSignal = true;
                while (sessionExitSignal) {
                    atm->mainEnglishDisplay();
                    cout << "        PLEASE CHOOSE THE SERVICE YOU WANT\n" << endl;
                    cout << "       1. DEPOSIT     2. WITHDRAWAL" << endl;
                    cout << "       3. TRANSFER    4. TRANSACTION HISTORY" << endl;
                    cout << "       5. SESSION EXIT\n" << endl;
                    cout << "==================================================" << endl;
                    cout << "Enter the number : ";
                    int transactionNum;
                    cin >> transactionNum;
                    
                    
                    if (transactionNum == 1) { // Deposit
                        atm->mainEnglishDisplay();
                        cout << "       You select the Deposit Transaction.\n" << endl;
                        cout << "              SELECT CASH or CHECK\n" << endl;
                        cout << "      1. CASH DEPOSIT     2. CHECK DEPOSIT\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "Enter the number : ";
                        int x;
                        cin >> x;
                        unsigned long long inAmount;
                        if (x == 1) {
                            while (true) {
                                atm->mainEnglishDisplay();
                                cout << "   PLEASE ENTER THE NUMBER OF 10,000 WON BILLS\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "The Number of Bills : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 50) {inAmount = 10000 * numBill; break;}
                                else {
                                    atm->mainEnglishDisplay();
                                    cout << "    IT'S OVER THE LIMIT IN THE NUMBER OF CASH" << endl;
                                    cout << "      THAT CAN BE DEPOSITED PER TRANSACTION\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainEnglishDisplay();
                            CashDeposit(inAmount, 1);
                            cout << "==================================================" << endl;
                        } else if (x == 2) {
                            while (true) {
                                atm->mainEnglishDisplay();
                                cout << "  PLEASE ENTER THE NUMBER OF 100,000 WON CHECKS\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "The Number of Checks : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 30) {inAmount = 100000 * numBill; break;}
                                else {
                                    atm->mainEnglishDisplay();
                                    cout << "    IT'S OVER THE LIMIT IN THE NUMBER OF CHECK" << endl;
                                    cout << "      THAT CAN BE DEPOSITED PER TRANSACTION\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainEnglishDisplay();
                            CheckDeposit(inAmount, 1);
                            cout << "==================================================" << endl;
                        } else atm->invalidEnglishDisplay();
                        
                        
                    } else if (transactionNum == 2) { // Withdrawal
                        if (withdrawalCount == 3) {
                            atm->mainEnglishDisplay();
                            cout << "      IT'S OVER THE LIMIT IN THE NUMBER OF" << endl;
                            cout << "         WITHDRAWAL OF FUND PER SESSION\n" << endl;
                            cout << "==================================================" << endl;
                        }
                        else {
                            unsigned long long inAmount;
                            int aNum;
                            while (true) {
                                atm->mainEnglishDisplay();
                                cout << "      You select the Withdrawal Transaction\n" << endl;
                                cout << "         SELECT THE AMOUNT TO WITHDRAWAL\n" << endl;
                                cout << "1. 10,000 won     2. 20,000 won    3. 30,000 won" << endl;
                                cout << "4. 40,000 won     5. 50,000 won    6. 100,000 won" << endl;
                                cout << "                 7. OTHER AMOUNT\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "Enter the number : ";
                                cin >> aNum;
                                if (aNum == 1) {inAmount = 10000; break;}
                                else if (aNum == 2) {inAmount = 20000; break;}
                                else if (aNum == 3) {inAmount = 30000; break;}
                                else if (aNum == 4) {inAmount = 40000; break;}
                                else if (aNum == 5) {inAmount = 50000; break;}
                                else if (aNum == 6) {inAmount = 100000; break;}
                                else if (aNum == 7) {
                                    while (true) {
                                        atm->mainEnglishDisplay();
                                        cout << "     ENTER THE AMOUNT IN UNITS OF 10,000 won\n";
                                        cout << "==================================================" << endl;
                                        cout << "Amount : ";
                                        cin >> inAmount;
                                        if ((inAmount % 10000 == 0) && (inAmount <= 500000)) break;
                                        if (inAmount > 500000) {
                                            atm->mainEnglishDisplay();
                                            cout << "      IT'S OVER THE LIMIT IN THE AMOUNT OF" << endl;
                                            cout << "       WITHDRAWAL OF FUND PER TRANSACTION\n" << endl;
                                            cout << "==================================================" << endl;
                                        }
                                        if (inAmount % 10000 != 0) {
                                            atm->mainEnglishDisplay();
                                            cout << "           YOU SHOULD ENTER THE AMOUNT" << endl;
                                            cout << "             IN UNITS OF 10,000 won\n" << endl;
                                            cout << "==================================================" << endl;
                                        }
                                    }
                                    break;
                                }
                                atm->invalidEnglishDisplay();
                            }
                            atm->mainEnglishDisplay();
                            Withdrawal(inAmount, 1);
                            cout << "==================================================" << endl;
                        }
                        
                        
                        
                    } else if (transactionNum == 3) { // Transfer
                        atm->mainEnglishDisplay();
                        cout << "       You select the Transfer Transaction\n" << endl;
                        cout << "    1. Account Transfer (Account to Account)" << endl;
                        cout << "    2. Cash Transfer (Cash to Account)\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "Enter the number : " << endl;
                        int transferNum;
                        cin >> transferNum;
                        
                        if (transferNum == 1) { // Account Transfer
                            atm->mainEnglishDisplay();
                            cout << "   You select the Account Transfer Transaction\n" << endl;
                            cout << "       PLEASE ENTER THE AMOUNT TO TRANSFER\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "Amount : ";
                            unsigned long long inAmount;
                            cin >> inAmount;
                            atm->mainEnglishDisplay();
                            cout << "       PLEASE ENTER THE AMOUNT TO TRANSFER\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "Destination Account Number : ";
                            string inDest;
                            cin >> inDest;
                            if (findAccount(inDest) == nullptr) {
                                atm->mainEnglishDisplay();
                                cout << "  THE ACCOUNT NUMBER YOU ENTERED DOES NOT EXIST\n" << endl;
                                cout << "==================================================" << endl;
                            } else {
                                atm->mainEnglishDisplay();
                                AccountTransfer(inAmount, findAccount(inDest)->findAccountOfBank(inDest), 1);
                                cout << "==================================================" << endl;
                            }
                            
                        } else if (transferNum == 2) { // Cash Transfer
                            unsigned long long inAmount;
                            while (true) {
                                atm->mainEnglishDisplay();
                                cout << "   PLEASE ENTER THE NUMBER OF 10,000 WON BILLS\n" << endl;
                                cout << "==================================================" << endl;
                                cout << "The Number of Bills : ";
                                int numBill;
                                cin >> numBill;
                                if (numBill <= 50) {inAmount = 10000 * numBill; break;}
                                else {
                                    atm->mainEnglishDisplay();
                                    cout << "    IT'S OVER THE LIMIT IN THE NUMBER OF CASH" << endl;
                                    cout << "     THAT CAN BE TRANSFERED PER TRANSACTION\n" << endl;
                                    cout << "==================================================" << endl;
                                }
                            }
                            atm->mainEnglishDisplay();
                            cout << "      PLEASE ENTER THE ACCOUNT TO TRANSFER\n" << endl;
                            cout << "==================================================" << endl;
                            cout << "Destination Account Number : ";
                            string inDest;
                            cin >> inDest;
                            if (findAccount(inDest) == nullptr) {
                                atm->mainEnglishDisplay();
                                cout << "  THE ACCOUNT NUMBER YOU ENTERED DOES NOT EXIST\n" << endl;
                                cout << "==================================================" << endl;
                            } else {
                                atm->mainEnglishDisplay();
                                AccountTransfer(inAmount, findAccount(inDest)->findAccountOfBank(inDest), 1);
                                cout << "==================================================" << endl;
                            }
                            
                        }  else { // Exception
                            atm->invalidEnglishDisplay();
                        }
                        
                        
                    } else if (transactionNum == 4) { // Transaction History
                        atm->mainEnglishDisplay();
                        cout << "       You select the Transaction History\n" << endl;
                        cout << "            THE TRANSACTION DETAILS OF" << endl;
                        cout << "            THE ACCOUNT ARE AS FOLLOWS\n" << endl;
                        vector<Transaction> temp =account->getTransactionHistoryOfAccount();
                        if (temp.size() == 0) {
                            cout << "==================================================\n" << endl;
                            cout << "CURRENT BALANCE : " << account->getFundInfo() << " won\n" << endl;
                            cout << "THIS ACCOUNT DOESN'T HAVE ANY TRANSACTION HISTORY\n" << endl;
                        } else {
                            for (int i = 0; i < temp.size(); i++) {
                                cout << temp[i].getEnglishInformation() << endl;
                            }
                            cout << "\nCURRENT BALANCE : " << account->getFundInfo() << " won\n" << endl;
                            cout << "==================================================" << endl;
                        }
                        
                    } else if (transactionNum == 5) { // Session Exit
                        sessionExitSignal = false;
                    }
                    
                    
                    else { // Exception
                        atm->invalidEnglishDisplay();
                    }
                }
                atm->mainEnglishDisplay();
                cout << "                   SESSION END" << endl;
                cout << "           THANK YOU FOR USING OUR ATM\n" << endl;
                if (transactionHistoryOfSession.size() == 0) {
                    cout << "THIS SESSION DOESN'T HAVE ANY TRANSACTION HISTORY\n" << endl;
                } else {
                    cout << "==================================================" << endl;
                    cout << "         TRANSACTION HISTORY OF SESSION" << endl;
                    cout << "==================================================" << endl;
                    atm->addTransaction(transactionHistoryOfSession);
                    for (int i = 0; i < transactionHistoryOfSession.size(); i++) {
                        cout << transactionHistoryOfSession[i].getEnglishInformation() << endl;
                    }
                }
            }
        }
    }
};





/*---------------- Method of ATM Class ----------------*/

void ATM::startEnglishAdminSession() {
    this->mainEnglishDisplay();
    cout << "            You select the Admin Menu" << endl;
    cout << "       PLEASE ENTER THE ADMIN CARD NUMBER\n" << endl;
    cout << "==================================================" << endl;
    cout << "Admin Card Number : ";
    string inAdmin;
    cin >> inAdmin;
    if (inAdmin.compare(AdminNum) == 0) {
        while (true) {
            this->mainEnglishDisplay();
            cout << "            SELECT THE ADMIN SERVICE\n" << endl;
            cout << "          1. TRANSACTION HISTORY OF ATM" << endl;
            cout << "          2. ADMIN SESSION EXIT\n" << endl;
            cout << "==================================================" << endl;
            cout << "Enter the number : ";
            int num;
            cin >> num;
            if (num == 1) {
                this->mainEnglishDisplay();
                if (transactionHistoryOfATM.size() == 0) {
                    cout << "       THIS ATM HAS NO TRANSACTION HISTORY" << endl;
                } else {
                    ofstream fout;
                    fout.open("Transaction History of ATM.txt");
                    if (!fout) cout << "                   File Error" << endl;
                    else {
                        fout << "ATM Serial No. : " << this->getSerialNum() << endl;
                        for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                            for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                                fout << transactionHistoryOfATM[i][j].getEnglishInformation();
                                fout << "\n";
                            }
                        }
                    }
                    cout << "==================================================" << endl;
                    cout << "         TRANSACTION HISTORY OF THIS ATM" << endl;
                    cout << "==================================================" << endl;
                    for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                        for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                            cout << transactionHistoryOfATM[i][j].getEnglishInformation() << endl;
                        }
                    }
                }
            } else if (num == 2) {
                this->mainEnglishDisplay();
                cout << "                ADMIN SESSION END" << endl;
                break;
            } else this->invalidEnglishDisplay();
        }
    } else this->invalidEnglishDisplay();
}

void ATM::startKoreanAdminSession() {
    this->mainKoreanDisplay();
    cout << "             관리자 모드를 선택하셨습니다" << endl;
    cout << "           관리자 카드 번호를 입력해주십시오\n" << endl;
    cout << "==================================================" << endl;
    cout << "관리자 카드 번호 : ";
    string inAdmin;
    cin >> inAdmin;
    if (inAdmin.compare(AdminNum) == 0) {
        while (true) {
            this->mainKoreanDisplay();
            cout << "             이용하실 서비스를 선택해주십시오\n" << endl;
            cout << "                 1. ATM 총 거래 내역" << endl;
            cout << "                 2. 관리자 모드 종료\n" << endl;
            cout << "==================================================" << endl;
            cout << "번호 입력 : ";
            int num;
            cin >> num;
            if (num == 1) {
                this->mainKoreanDisplay();
                if (transactionHistoryOfATM.size() == 0) {
                    cout << "          해당 ATM 기기에는 거래 내역이 없습니다" << endl;
                } else {
                    ofstream fout;
                    fout.open("Transaction History of ATM.txt");
                    if (!fout) cout << "                   출력 파일 오류" << endl;
                    else {
                        fout << "ATM 고유식별 번호 : " << this->getSerialNum() << endl;
                        for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                            for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                                fout << transactionHistoryOfATM[i][j].getKoreanInformation();
                                fout << "\n";
                            }
                        }
                    }
                    cout << "==================================================" << endl;
                    cout << "                해당 ATM 총 거래 내역" << endl;
                    cout << "==================================================" << endl;
                    for (int i = 0; i < transactionHistoryOfATM.size(); i++) {
                        for (int j = 0; j < transactionHistoryOfATM[i].size(); j++) {
                            cout << transactionHistoryOfATM[i][j].getKoreanInformation() << endl;
                        }
                    }
                }
            } else if (num == 2) {
                this->mainKoreanDisplay();
                cout << "                   관리자 모드 종료" << endl;
                break;
            } else this->invalidKoreanDisplay();
        }
    } else this->invalidKoreanDisplay();
}


/*---------------- Children Classes of ATM Class ----------------*/

/*---------- Single Bank ATM Class ----------*/

class SingleBankATM : public ATM {
public:
    SingleBankATM(string priName, string amount) {
        serialNum = atmCnt++;
        primaryBank = findBank(priName);
        cashAmount = stoull(amount);
        SingleOrMulti = 0;
    }
    void startSession() {}
    string getClassName() {return "Single";}
};

/*---------- Multi Bank ATM Class -----------*/

class MultiBankATM : public ATM {
public:
    MultiBankATM(string priName, string amount) {
        serialNum = atmCnt++;
        primaryBank = findBank(priName);
        cashAmount = stoull(amount);
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
            this->mainEnglishDisplay();
            cout << "                     WELCOME                     \n" << endl;
            cout << "                      MENU\n" << endl;
            cout << "         1. TRANSACTION      2. ADMIN" << endl;
            cout << "         3. Go to HOME\n" << endl;
            cout << "==================================================" << endl;
            cout << "번호 입력 : ";
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
            } else this->invalidEnglishDisplay();
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
            this->mainEnglishDisplay();
            cout << "                     WELCOME                     \n" << endl;
            cout << "                      MENU\n" << endl;
            cout << "       1. TRANSACTION      2. 한국어(KOREAN)" << endl;
            cout << "       3. ADMIN            4. Go to HOME\n" << endl;
            cout << "==================================================" << endl;
            cout << "Enter the number : ";
            int languageNum;
            cin >> languageNum;
            if (languageNum == 1) {
                EnglishSession newSession(this);
                session = newSession;
            } else if (languageNum == 2) {
                return 1;
            } else if (languageNum == 3) {
                startEnglishAdminSession();
            } else if (languageNum == 4) {
                return 0;
            } else this->invalidEnglishDisplay();
        }
    }
    int startKoreanSession() {
        while (true) {
            this->mainKoreanDisplay();
            cout << "                     환영합니다                     \n" << endl;
            cout << "                       메뉴\n" << endl;
            cout << "          1. 서비스 이용     2. ENGLISH(영어)" << endl;
            cout << "          3. 관리자 모드     4. ATM 나가기\n" << endl;
            cout << "==================================================" << endl;
            cout << "번호 입력 : ";
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
            } else this->invalidKoreanDisplay();
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
                newAtm = new SingleBankATM(splitted[0], splitted[3]);
            } else if (splitted[1].compare("Multi") == 0) {
                newAtm = new MultiBankATM(splitted[0], splitted[3]);
            } else {
                cout << "입력 파일 오류" << endl;
                exit(7);
            }
            if (splitted[2].compare("Bi") == 0) {
                newAtm = new BilingualATM(newAtm, splitted[4]);
            } else if (splitted[2].compare("Uni") == 0) {
                newAtm = new UnilingualATM(newAtm, splitted[4]);
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
        cout << "이용하실 ATM을 선택해주십시오\n" << endl;
        for (int i = 0; i < atmData.size(); i++) {
            cout << right << setfill('0') << setw(2) << i+1 << ". " << left << setfill(' ') << setw(8) << atmData[i]->getPrimaryBankInfo() << "  ";
            if (atmData[i]->getSingleInfo() == 0) {
                cout << "Single  ";
            } else cout << "Multi   ";
            cout << left << setw(10) << atmData[i]->getClassName() << " ATM" <<endl;
        }
        cout << atmData.size()+1 << ". Program   Exit    프로그램 종료\n" << endl;
        cout << "Enter the Number (번호 입력) : ";
        int choiceAtm;
        cin >> choiceAtm;
        if (choiceAtm == atmData.size()+1) {
            programEndSignal = false;
        }
        else {
            atmData[choiceAtm-1]->startSession();
        }
    }
    
    return 0;
}
