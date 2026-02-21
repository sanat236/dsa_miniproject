#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>

struct Account {
    int accountNumber;
    QString name;
    QString password;
    double balance;
    QString accountType;
};

void createAccount(QString name, QString password, QString type, double balance);
Account* findAccount(int accountNumber);
void deleteAccount(int accountNumber);
void saveAccounts();
void loadAccounts();

extern QVector<Account> accounts;
extern int accountCounter;

#endif
