#include "account.h"
#include <QFile>
#include <QTextStream>

QVector<Account> accounts;
int accountCounter = 1000;

void createAccount(QString name, QString password, QString type, double balance) {
    Account newAccount;
    accountCounter++;
    newAccount.accountNumber = accountCounter;
    newAccount.name = name;
    newAccount.password = password;
    newAccount.accountType = type;
    newAccount.balance = balance;
    accounts.push_back(newAccount);
    saveAccounts();
}

Account* findAccount(int accountNumber) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return &accounts[i];
        }
    }
    return nullptr;
}

void deleteAccount(int accountNumber) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts.remove(i);
            saveAccounts();
            return;
        }
    }
}

void saveAccounts() {
    QFile file("accounts.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << accountCounter << "\n";
        for (int i = 0; i < accounts.size(); i++) {
            out << accounts[i].accountNumber << "\n";
            out << accounts[i].name << "\n";
            out << accounts[i].password << "\n";
            out << accounts[i].accountType << "\n";
            out << accounts[i].balance << "\n";
        }
        file.close();
    }
}

void loadAccounts() {
    QFile file("accounts.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> accountCounter;
        while (!in.atEnd()) {
            Account acc;
            in >> acc.accountNumber;
            if (acc.accountNumber == 0) break;
            in.readLineInto(nullptr);
            acc.name = in.readLine();
            acc.password = in.readLine();
            acc.accountType = in.readLine();
            in >> acc.balance;
            in.readLineInto(nullptr);
            accounts.push_back(acc);
        }
        file.close();
    }
}
