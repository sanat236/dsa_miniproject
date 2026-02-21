#include "transaction.h"
#include <QFile>
#include <QTextStream>
#include <QDate>

QVector<Transaction> transactions;
int transactionCounter = 0;

void addTransaction(int accountNumber, QString type, double amount) {
    Transaction t;
    transactionCounter++;
    t.transactionId = transactionCounter;
    t.accountNumber = accountNumber;
    t.type = type;
    t.amount = amount;
    t.date = QDate::currentDate().toString("yyyy-MM-dd");
    transactions.push_back(t);
    saveTransactions();
}

QVector<Transaction> getTransactions(int accountNumber) {
    QVector<Transaction> result;
    for (int i = 0; i < transactions.size(); i++) {
        if (transactions[i].accountNumber == accountNumber) {
            result.push_back(transactions[i]);
        }
    }
    return result;
}

void saveTransactions() {
    QFile file("transactions.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << transactionCounter << "\n";
        for (int i = 0; i < transactions.size(); i++) {
            out << transactions[i].transactionId << "\n";
            out << transactions[i].accountNumber << "\n";
            out << transactions[i].type << "\n";
            out << transactions[i].amount << "\n";
            out << transactions[i].date << "\n";
        }
        file.close();
    }
}

void loadTransactions() {
    QFile file("transactions.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> transactionCounter;
        while (!in.atEnd()) {
            Transaction t;
            in >> t.transactionId;
            if (t.transactionId == 0) break;
            in >> t.accountNumber;
            in.readLineInto(nullptr);
            t.type = in.readLine();
            in >> t.amount;
            in.readLineInto(nullptr);
            t.date = in.readLine();
            transactions.push_back(t);
        }
        file.close();
    }
}
