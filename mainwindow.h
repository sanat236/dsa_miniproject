#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QHeaderView>
#include <QApplication>

class BankQueue;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMainMenu();
    void showCreateAccount();
    void showQueue();
    void showDeposit();
    void showHistory();
    void showDeleteAccount();
    void showChangePassword();

    void onCreateAccount();
    void onAddToQueue();
    void onServeCustomer();
    void onDeposit();
    void onWithdraw();
    void onViewHistory();
    void onDeleteAccount();
    void onLogin();
    void onChangePassword();

private:
    // Stacked widget
    QStackedWidget* stackedWidget;

    // Admin credentials
    QString adminPassword = "admin123";

    // Login widgets
    QWidget* loginWidget;
    QLineEdit* usernameInput;
    QLineEdit* loginPasswordInput;
    QPushButton* btnLogin;

    // Main menu widgets
    QWidget* mainMenuWidget;
    QPushButton* btnCreateAccount;
    QPushButton* btnQueue;
    QPushButton* btnDeposit;
    QPushButton* btnHistory;
    QPushButton* btnDeleteAccount;
    QPushButton* btnChangePassword;
    QPushButton* btnLogout;
    QPushButton* btnExit;

    // Create account widgets
    QWidget* createAccountWidget;
    QLineEdit* nameInput;
    QLineEdit* passwordInput;
    QComboBox* accountTypeInput;
    QLineEdit* balanceInput;
    QPushButton* btnSubmitAccount;
    QPushButton* btnBackFromCreate;

    // Queue widgets
    QWidget* queueWidget;
    QLineEdit* queueAccInput;
    QLineEdit* queueNameInput;
    QComboBox* queueServiceInput;
    QPushButton* btnAddToQueue;
    QPushButton* btnServeCustomer;
    QTableWidget* queueTable;
    QPushButton* btnBackFromQueue;

    // Deposit/Withdraw widgets
    QWidget* depositWidget;
    QLineEdit* depositAccInput;
    QLineEdit* depositAmountInput;
    QPushButton* btnDeposit2;
    QPushButton* btnWithdraw;
    QLabel* balanceLabel;
    QPushButton* btnBackFromDeposit;

    // History widgets
    QWidget* historyWidget;
    QLineEdit* historyAccInput;
    QPushButton* btnViewHistory;
    QTableWidget* historyTable;
    QPushButton* btnBackFromHistory;

    // Delete account widgets
    QWidget* deleteWidget;
    QLineEdit* deleteAccInput;
    QPushButton* btnSubmitDelete;
    QPushButton* btnBackFromDelete;

    // Change password widgets
    QWidget* changePasswordWidget;
    QLineEdit* currentPasswordInput;
    QLineEdit* newPasswordInput;
    QLineEdit* confirmPasswordInput;
    QPushButton* btnSubmitChangePassword;
    QPushButton* btnBackFromChangePassword;

    // Helper functions
    void setupLogin();
    void setupMainMenu();
    void setupCreateAccount();
    void setupQueue();
    void setupDeposit();
    void setupHistory();
    void setupDeleteAccount();
    void setupChangePassword();
    void refreshQueueTable();

    BankQueue* bankQueue;
};

#endif
