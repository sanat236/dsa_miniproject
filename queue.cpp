#include "queue.h"

BankQueue::BankQueue() {
    front = nullptr;
    rear = nullptr;
    size = 0;
}

BankQueue::~BankQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void BankQueue::enqueue(Customer customer) {
    QueueNode* newNode = new QueueNode();
    newNode->customer = customer;
    newNode->next = nullptr;
    customer.position = size + 1;

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

Customer BankQueue::dequeue() {
    if (isEmpty()) {
        return Customer{-1, "", "", -1};
    }

    QueueNode* temp = front;
    Customer served = front->customer;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;
    return served;
}

bool BankQueue::isEmpty() {
    return size == 0;
}

int BankQueue::getSize() {
    return size;
}

Customer BankQueue::getFront() {
    return front->customer;
}

QueueNode* BankQueue::getFrontNode() {
    return front;
}
