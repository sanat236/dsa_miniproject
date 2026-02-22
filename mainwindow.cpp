//Admin Controlled Banking System
#include "mainwindow.h"
#include "account.h"
#include "transaction.h"
#include "queue.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Banking System");
    setMinimumSize(800, 600);

    loadAccounts();
    loadTransactions();

    bankQueue = new BankQueue();

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupLogin();
    setupMainMenu();
    setupCreateAccount();
    setupQueue();
    setupDeposit();
    setupHistory();
    setupDeleteAccount();
    setupChangePassword();

    stackedWidget->setCurrentWidget(loginWidget);
}

MainWindow::~MainWindow() {
    delete bankQueue;
}

// SETUP LOGIN
void MainWindow::setupLogin() {
    loginWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(loginWidget);

    QLabel* title = new QLabel("BANKING SYSTEM");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 32px; font-weight: bold; padding: 20px; color: #2196F3;");

    QLabel* subtitle = new QLabel("Admin Login");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 18px; padding: 10px; color: #666;");

    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Username");
    usernameInput->setStyleSheet("padding: 10px; font-size: 14px; border-radius: 8px;");
    usernameInput->setMaximumWidth(300);

    loginPasswordInput = new QLineEdit();
    loginPasswordInput->setPlaceholderText("Password");
    loginPasswordInput->setEchoMode(QLineEdit::Password);
    loginPasswordInput->setStyleSheet("padding: 10px; font-size: 14px; border-radius: 8px;");
    loginPasswordInput->setMaximumWidth(300);

    btnLogin = new QPushButton("LOGIN");
    btnLogin->setStyleSheet("QPushButton { font-size: 16px; padding: 12px; background-color: #2196F3; color: white; border-radius: 8px; min-width: 200px; }"
                            "QPushButton:hover { background-color: #1976D2; }");
    btnLogin->setMaximumWidth(300);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addSpacing(20);
    layout->addWidget(usernameInput, 0, Qt::AlignCenter);
    layout->addWidget(loginPasswordInput, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(btnLogin, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(btnLogin, &QPushButton::clicked, this, &MainWindow::onLogin);

    stackedWidget->addWidget(loginWidget);
}

// SETUP MAIN MENU
void MainWindow::setupMainMenu() {
    mainMenuWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(mainMenuWidget);

    QLabel* title = new QLabel("BANKING SYSTEM");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; padding: 20px;");

    btnCreateAccount = new QPushButton("Create Account");
    btnQueue = new QPushButton("Manage Queue");
    btnDeposit = new QPushButton("Deposit / Withdraw");
    btnHistory = new QPushButton("Transaction History");
    btnDeleteAccount = new QPushButton("Delete Account");
    btnChangePassword = new QPushButton("Change Password");
    btnLogout = new QPushButton("Logout");
    btnExit = new QPushButton("Exit");

    QString btnStyle = "QPushButton { font-size: 16px; padding: 12px; margin: 5px; border-radius: 8px; background-color: #2196F3; color: white; }"
                       "QPushButton:hover { background-color: #1976D2; }";

    btnCreateAccount->setStyleSheet(btnStyle);
    btnQueue->setStyleSheet(btnStyle);
    btnDeposit->setStyleSheet(btnStyle);
    btnHistory->setStyleSheet(btnStyle);
    btnDeleteAccount->setStyleSheet(btnStyle);
    btnChangePassword->setStyleSheet("QPushButton { font-size: 16px; padding: 12px; margin: 5px; border-radius: 8px; background-color: #9C27B0; color: white; }"
                                     "QPushButton:hover { background-color: #7B1FA2; }");
    btnLogout->setStyleSheet("QPushButton { font-size: 16px; padding: 12px; margin: 5px; border-radius: 8px; background-color: #FF9800; color: white; }"
                             "QPushButton:hover { background-color: #F57C00; }");
    btnExit->setStyleSheet("QPushButton { font-size: 16px; padding: 12px; margin: 5px; border-radius: 8px; background-color: #f44336; color: white; }"
                           "QPushButton:hover { background-color: #d32f2f; }");

    layout->addWidget(title);
    layout->addWidget(btnCreateAccount);
    layout->addWidget(btnQueue);
    layout->addWidget(btnDeposit);
    layout->addWidget(btnHistory);
    layout->addWidget(btnDeleteAccount);
    layout->addWidget(btnChangePassword);
    layout->addWidget(btnLogout);
    layout->addWidget(btnExit);
    layout->addStretch();

    connect(btnCreateAccount, &QPushButton::clicked, this, &MainWindow::showCreateAccount);
    connect(btnQueue, &QPushButton::clicked, this, &MainWindow::showQueue);
    connect(btnDeposit, &QPushButton::clicked, this, &MainWindow::showDeposit);
    connect(btnHistory, &QPushButton::clicked, this, &MainWindow::showHistory);
    connect(btnDeleteAccount, &QPushButton::clicked, this, &MainWindow::showDeleteAccount);
    connect(btnChangePassword, &QPushButton::clicked, this, &MainWindow::showChangePassword);
    connect(btnLogout, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(loginWidget);
    });
    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);

    stackedWidget->addWidget(mainMenuWidget);
}

// SETUP CREATE ACCOUNT
void MainWindow::setupCreateAccount() {
    createAccountWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(createAccountWidget);

    QLabel* title = new QLabel("Create Account");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter Name");
    nameInput->setStyleSheet("padding: 8px; font-size: 14px;");

    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet("padding: 8px; font-size: 14px;");

    accountTypeInput = new QComboBox();
    accountTypeInput->addItem("savings");
    accountTypeInput->addItem("checking");
    accountTypeInput->setStyleSheet("padding: 8px; font-size: 14px;");

    balanceInput = new QLineEdit();
    balanceInput->setPlaceholderText("Initial Deposit");
    balanceInput->setStyleSheet("padding: 8px; font-size: 14px;");

    btnSubmitAccount = new QPushButton("Create Account");
    btnSubmitAccount->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #4CAF50; color: white; border-radius: 8px; }"
                                    "QPushButton:hover { background-color: #388E3C; }");

    btnBackFromCreate = new QPushButton("Back");
    btnBackFromCreate->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                     "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(nameInput);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(passwordInput);
    layout->addWidget(new QLabel("Account Type:"));
    layout->addWidget(accountTypeInput);
    layout->addWidget(new QLabel("Initial Deposit:"));
    layout->addWidget(balanceInput);
    layout->addWidget(btnSubmitAccount);
    layout->addWidget(btnBackFromCreate);
    layout->addStretch();

    connect(btnSubmitAccount, &QPushButton::clicked, this, &MainWindow::onCreateAccount);
    connect(btnBackFromCreate, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(createAccountWidget);
}

// SETUP QUEUE
void MainWindow::setupQueue() {
    queueWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(queueWidget);

    QLabel* title = new QLabel("Queue Management");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    queueAccInput = new QLineEdit();
    queueAccInput->setPlaceholderText("Enter Account Number");
    queueAccInput->setStyleSheet("padding: 8px; font-size: 14px;");

    queueNameInput = new QLineEdit();
    queueNameInput->setPlaceholderText("Enter Name");
    queueNameInput->setStyleSheet("padding: 8px; font-size: 14px;");

    queueServiceInput = new QComboBox();
    queueServiceInput->addItem("deposit");
    queueServiceInput->addItem("withdrawal");
    queueServiceInput->addItem("inquiry");
    queueServiceInput->setStyleSheet("padding: 8px; font-size: 14px;");

    btnAddToQueue = new QPushButton("Add to Queue");
    btnAddToQueue->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #2196F3; color: white; border-radius: 8px; }"
                                 "QPushButton:hover { background-color: #1976D2; }");

    btnServeCustomer = new QPushButton("Serve Next Customer");
    btnServeCustomer->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #FF9800; color: white; border-radius: 8px; }"
                                    "QPushButton:hover { background-color: #F57C00; }");

    queueTable = new QTableWidget();
    queueTable->setColumnCount(4);
    queueTable->setHorizontalHeaderLabels({"Position", "Account No", "Name", "Service"});
    queueTable->horizontalHeader()->setStretchLastSection(true);
    queueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btnBackFromQueue = new QPushButton("Back");
    btnBackFromQueue->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                    "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Account Number:"));
    layout->addWidget(queueAccInput);
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(queueNameInput);
    layout->addWidget(new QLabel("Service Type:"));
    layout->addWidget(queueServiceInput);
    layout->addWidget(btnAddToQueue);
    layout->addWidget(btnServeCustomer);
    layout->addWidget(new QLabel("Current Queue:"));
    layout->addWidget(queueTable);
    layout->addWidget(btnBackFromQueue);

    connect(btnAddToQueue, &QPushButton::clicked, this, &MainWindow::onAddToQueue);
    connect(btnServeCustomer, &QPushButton::clicked, this, &MainWindow::onServeCustomer);
    connect(btnBackFromQueue, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(queueWidget);
}

// SETUP DEPOSIT
void MainWindow::setupDeposit() {
    depositWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(depositWidget);

    QLabel* title = new QLabel("Deposit / Withdraw");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    depositAccInput = new QLineEdit();
    depositAccInput->setPlaceholderText("Enter Account Number");
    depositAccInput->setStyleSheet("padding: 8px; font-size: 14px;");

    depositAmountInput = new QLineEdit();
    depositAmountInput->setPlaceholderText("Enter Amount");
    depositAmountInput->setStyleSheet("padding: 8px; font-size: 14px;");

    balanceLabel = new QLabel("Balance: $0.00");
    balanceLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding: 10px;");

    btnDeposit2 = new QPushButton("Deposit");
    btnDeposit2->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #4CAF50; color: white; border-radius: 8px; }"
                               "QPushButton:hover { background-color: #388E3C; }");

    btnWithdraw = new QPushButton("Withdraw");
    btnWithdraw->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #f44336; color: white; border-radius: 8px; }"
                               "QPushButton:hover { background-color: #d32f2f; }");

    btnBackFromDeposit = new QPushButton("Back");
    btnBackFromDeposit->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                      "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Account Number:"));
    layout->addWidget(depositAccInput);
    layout->addWidget(new QLabel("Amount:"));
    layout->addWidget(depositAmountInput);
    layout->addWidget(balanceLabel);
    layout->addWidget(btnDeposit2);
    layout->addWidget(btnWithdraw);
    layout->addWidget(btnBackFromDeposit);
    layout->addStretch();

    connect(btnDeposit2, &QPushButton::clicked, this, &MainWindow::onDeposit);
    connect(btnWithdraw, &QPushButton::clicked, this, &MainWindow::onWithdraw);
    connect(btnBackFromDeposit, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(depositWidget);
}

// SETUP HISTORY
void MainWindow::setupHistory() {
    historyWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(historyWidget);

    QLabel* title = new QLabel("Transaction History");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    historyAccInput = new QLineEdit();
    historyAccInput->setPlaceholderText("Enter Account Number");
    historyAccInput->setStyleSheet("padding: 8px; font-size: 14px;");

    btnViewHistory = new QPushButton("View History");
    btnViewHistory->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #2196F3; color: white; border-radius: 8px; }"
                                  "QPushButton:hover { background-color: #1976D2; }");

    historyTable = new QTableWidget();
    historyTable->setColumnCount(4);
    historyTable->setHorizontalHeaderLabels({"ID", "Type", "Amount", "Date"});
    historyTable->horizontalHeader()->setStretchLastSection(true);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btnBackFromHistory = new QPushButton("Back");
    btnBackFromHistory->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                      "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Account Number:"));
    layout->addWidget(historyAccInput);
    layout->addWidget(btnViewHistory);
    layout->addWidget(historyTable);
    layout->addWidget(btnBackFromHistory);

    connect(btnViewHistory, &QPushButton::clicked, this, &MainWindow::onViewHistory);
    connect(btnBackFromHistory, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(historyWidget);
}

// SETUP DELETE ACCOUNT
void MainWindow::setupDeleteAccount() {
    deleteWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(deleteWidget);

    QLabel* title = new QLabel("Delete Account");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    deleteAccInput = new QLineEdit();
    deleteAccInput->setPlaceholderText("Enter Account Number");
    deleteAccInput->setStyleSheet("padding: 8px; font-size: 14px;");

    btnSubmitDelete = new QPushButton("Delete Account");
    btnSubmitDelete->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #f44336; color: white; border-radius: 8px; }"
                                   "QPushButton:hover { background-color: #d32f2f; }");

    btnBackFromDelete = new QPushButton("Back");
    btnBackFromDelete->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                     "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Account Number:"));
    layout->addWidget(deleteAccInput);
    layout->addWidget(btnSubmitDelete);
    layout->addWidget(btnBackFromDelete);
    layout->addStretch();

    connect(btnSubmitDelete, &QPushButton::clicked, this, &MainWindow::onDeleteAccount);
    connect(btnBackFromDelete, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(deleteWidget);
}

// SETUP CHANGE PASSWORD
void MainWindow::setupChangePassword() {
    changePasswordWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(changePasswordWidget);

    QLabel* title = new QLabel("Change Password");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; padding: 15px;");

    currentPasswordInput = new QLineEdit();
    currentPasswordInput->setPlaceholderText("Current Password");
    currentPasswordInput->setEchoMode(QLineEdit::Password);
    currentPasswordInput->setStyleSheet("padding: 8px; font-size: 14px;");

    newPasswordInput = new QLineEdit();
    newPasswordInput->setPlaceholderText("New Password");
    newPasswordInput->setEchoMode(QLineEdit::Password);
    newPasswordInput->setStyleSheet("padding: 8px; font-size: 14px;");

    confirmPasswordInput = new QLineEdit();
    confirmPasswordInput->setPlaceholderText("Confirm New Password");
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setStyleSheet("padding: 8px; font-size: 14px;");

    btnSubmitChangePassword = new QPushButton("Change Password");
    btnSubmitChangePassword->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9C27B0; color: white; border-radius: 8px; }"
                                           "QPushButton:hover { background-color: #7B1FA2; }");

    btnBackFromChangePassword = new QPushButton("Back");
    btnBackFromChangePassword->setStyleSheet("QPushButton { font-size: 16px; padding: 10px; background-color: #9E9E9E; color: white; border-radius: 8px; }"
                                             "QPushButton:hover { background-color: #616161; }");

    layout->addWidget(title);
    layout->addWidget(new QLabel("Current Password:"));
    layout->addWidget(currentPasswordInput);
    layout->addWidget(new QLabel("New Password:"));
    layout->addWidget(newPasswordInput);
    layout->addWidget(new QLabel("Confirm New Password:"));
    layout->addWidget(confirmPasswordInput);
    layout->addWidget(btnSubmitChangePassword);
    layout->addWidget(btnBackFromChangePassword);
    layout->addStretch();

    connect(btnSubmitChangePassword, &QPushButton::clicked, this, &MainWindow::onChangePassword);
    connect(btnBackFromChangePassword, &QPushButton::clicked, this, &MainWindow::showMainMenu);

    stackedWidget->addWidget(changePasswordWidget);
}

// NAVIGATION
void MainWindow::showMainMenu() { stackedWidget->setCurrentWidget(mainMenuWidget); }
void MainWindow::showCreateAccount() { stackedWidget->setCurrentWidget(createAccountWidget); }
void MainWindow::showQueue() { refreshQueueTable(); stackedWidget->setCurrentWidget(queueWidget); }
void MainWindow::showDeposit() { stackedWidget->setCurrentWidget(depositWidget); }
void MainWindow::showHistory() { stackedWidget->setCurrentWidget(historyWidget); }
void MainWindow::showDeleteAccount() { stackedWidget->setCurrentWidget(deleteWidget); }
void MainWindow::showChangePassword() { stackedWidget->setCurrentWidget(changePasswordWidget); }

// LOGIN
void MainWindow::onLogin() {
    QString username = usernameInput->text();
    QString password = loginPasswordInput->text();

    if (username == "admin" && password == adminPassword) {
        usernameInput->clear();
        loginPasswordInput->clear();
        showMainMenu();
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password!");
    }
}

// CHANGE PASSWORD
void MainWindow::onChangePassword() {
    QString current = currentPasswordInput->text();
    QString newPass = newPasswordInput->text();
    QString confirm = confirmPasswordInput->text();

    if (current != adminPassword) {
        QMessageBox::warning(this, "Error", "Current password is incorrect!");
        return;
    }

    if (newPass.isEmpty()) {
        QMessageBox::warning(this, "Error", "New password cannot be empty!");
        return;
    }

    if (newPass != confirm) {
        QMessageBox::warning(this, "Error", "New passwords do not match!");
        return;
    }

    adminPassword = newPass;
    QMessageBox::information(this, "Success", "Password changed successfully!");

    currentPasswordInput->clear();
    newPasswordInput->clear();
    confirmPasswordInput->clear();

    showMainMenu();
}

// ACTIONS
void MainWindow::onCreateAccount() {
    QString name = nameInput->text();
    QString password = passwordInput->text();
    QString type = accountTypeInput->currentText();
    double balance = balanceInput->text().toDouble();

    if (name.isEmpty() || password.isEmpty() || balanceInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    createAccount(name, password, type, balance);
    QMessageBox::information(this, "Success", "Account Created!\nAccount Number: " + QString::number(accountCounter));

    nameInput->clear();
    passwordInput->clear();
    balanceInput->clear();
}

void MainWindow::onAddToQueue() {
    int accNum = queueAccInput->text().toInt();
    QString name = queueNameInput->text();
    QString service = queueServiceInput->currentText();

    if (name.isEmpty() || accNum == 0) {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    Customer customer;
    customer.accountNumber = accNum;
    customer.name = name;
    customer.serviceType = service;
    customer.position = 0;

    bankQueue->enqueue(customer);
    refreshQueueTable();

    queueAccInput->clear();
    queueNameInput->clear();

    QMessageBox::information(this, "Success", "Customer added to queue!\nPosition: " + QString::number(bankQueue->getSize()));
}

void MainWindow::onServeCustomer() {
    if (bankQueue->isEmpty()) {
        QMessageBox::warning(this, "Empty Queue", "No customers in queue!");
        return;
    }

    Customer served = bankQueue->dequeue();
    refreshQueueTable();
    QMessageBox::information(this, "Serving", "Now serving: " + served.name + "\nService: " + served.serviceType);
}

void MainWindow::onDeposit() {
    int accNum = depositAccInput->text().toInt();
    double amount = depositAmountInput->text().toDouble();

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        QMessageBox::warning(this, "Error", "Account not found!");
        return;
    }

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount!");
        return;
    }

    acc->balance += amount;
    addTransaction(accNum, "deposit", amount);
    saveAccounts();

    balanceLabel->setText("Balance: $" + QString::number(acc->balance, 'f', 2));
    QMessageBox::information(this, "Success", "Deposit Successful!\nNew Balance: $" + QString::number(acc->balance, 'f', 2));
    depositAmountInput->clear();
}

void MainWindow::onWithdraw() {
    int accNum = depositAccInput->text().toInt();
    double amount = depositAmountInput->text().toDouble();

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        QMessageBox::warning(this, "Error", "Account not found!");
        return;
    }

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount!");
        return;
    }

    if (amount > acc->balance) {
        QMessageBox::warning(this, "Error", "Insufficient funds!");
        return;
    }

    acc->balance -= amount;
    addTransaction(accNum, "withdrawal", amount);
    saveAccounts();

    balanceLabel->setText("Balance: $" + QString::number(acc->balance, 'f', 2));
    QMessageBox::information(this, "Success", "Withdrawal Successful!\nNew Balance: $" + QString::number(acc->balance, 'f', 2));
    depositAmountInput->clear();
}

void MainWindow::onViewHistory() {
    int accNum = historyAccInput->text().toInt();
    QVector<Transaction> history = getTransactions(accNum);

    if (history.isEmpty()) {
        QMessageBox::warning(this, "Error", "No transactions found!");
        return;
    }

    historyTable->setRowCount(history.size());
    for (int i = 0; i < history.size(); i++) {
        historyTable->setItem(i, 0, new QTableWidgetItem(QString::number(history[i].transactionId)));
        historyTable->setItem(i, 1, new QTableWidgetItem(history[i].type));
        historyTable->setItem(i, 2, new QTableWidgetItem("$" + QString::number(history[i].amount, 'f', 2)));
        historyTable->setItem(i, 3, new QTableWidgetItem(history[i].date));
    }
}

void MainWindow::onDeleteAccount() {
    int accNum = deleteAccInput->text().toInt();
    Account* acc = findAccount(accNum);

    if (acc == nullptr) {
        QMessageBox::warning(this, "Error", "Account not found!");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm", "Are you sure you want to delete this account?");
    if (reply == QMessageBox::Yes) {
        deleteAccount(accNum);
        QMessageBox::information(this, "Success", "Account deleted successfully!");
        deleteAccInput->clear();
    }
}

void MainWindow::refreshQueueTable() {
    queueTable->setRowCount(0);
    QueueNode* current = bankQueue->getFrontNode();
    int position = 1;
    while (current != nullptr) {
        int row = queueTable->rowCount();
        queueTable->insertRow(row);
        queueTable->setItem(row, 0, new QTableWidgetItem(QString::number(position)));
        queueTable->setItem(row, 1, new QTableWidgetItem(QString::number(current->customer.accountNumber)));
        queueTable->setItem(row, 2, new QTableWidgetItem(current->customer.name));
        queueTable->setItem(row, 3, new QTableWidgetItem(current->customer.serviceType));
        current = current->next;
        position++;
    }
}
