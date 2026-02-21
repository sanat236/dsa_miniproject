#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QVector>

struct Transaction {
    int transactionId;
    int accountNumber;
    QString type;
    double amount;
    QString date;
};

void addTransaction(int accountNumber, QString type, double amount);
QVector<Transaction> getTransactions(int accountNumber);
void saveTransactions();
void loadTransactions();

extern QVector<Transaction> transactions;
extern int transactionCounter;

#endif
