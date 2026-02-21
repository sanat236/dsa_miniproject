#ifndef QUEUE_H
#define QUEUE_H

#include <QString>

struct Customer {
    int accountNumber;
    QString name;
    QString serviceType;
    int position;
};

struct QueueNode {
    Customer customer;
    QueueNode* next;
};

class BankQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    BankQueue();
    ~BankQueue();

    void enqueue(Customer customer);
    Customer dequeue();
    bool isEmpty();
    int getSize();
    Customer getFront();
    QueueNode* getFrontNode();
};

#endif
