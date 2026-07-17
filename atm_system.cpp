#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Account structure
struct Account {
    string name;
    string accountNumber;
    string pin;
    double balance;
};

// Global account (simple single account system)
Account userAccount = {"Shivam ", "ACC123456", "1234", 50000.00};

// Function to clear screen (Windows compatible)
void clearScreen() {
    system("cls");
}

// Function to display header
void displayHeader() {
    cout << "========================================" << endl;
    cout << "          WELCOME TO MY BANK ATM        " << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// Function to check PIN
bool verifyPIN() {
    string enteredPIN;
    int attempts = 3;

    while (attempts > 0) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPIN;

        if (enteredPIN == userAccount.pin) {
            cout << "\nPIN verified! Welcome, " << userAccount.name << "!" << endl;
            cout << "Account Number: " << userAccount.accountNumber << endl;
            cout << endl;
            return true;
        } else {
            attempts--;
            if (attempts > 0) {
                cout << "Wrong PIN! " << attempts << " attempt(s) remaining." << endl;
            }
        }
    }

    cout << "\nCard blocked! Too many wrong attempts." << endl;
    return false;
}

// Function to check balance
void checkBalance() {
    cout << "\n--- BALANCE INQUIRY ---" << endl;
    cout << "Account Holder : " << userAccount.name << endl;
    cout << "Account Number : " << userAccount.accountNumber << endl;
    cout << fixed << setprecision(2);
    cout << "Available Balance: Rs. " << userAccount.balance << endl;
}

// Function to deposit money
void depositMoney() {
    double amount;
    cout << "\n--- DEPOSIT MONEY ---" << endl;
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > 100000) {
        cout << "Maximum deposit limit is Rs. 1,00,000 per transaction." << endl;
        return;
    }

    userAccount.balance += amount;
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " deposited successfully!" << endl;
    cout << "New Balance: Rs. " << userAccount.balance << endl;
}

// Function to withdraw money
void withdrawMoney() {
    double amount;
    cout << "\n--- WITHDRAW MONEY ---" << endl;
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > userAccount.balance) {
        cout << "Insufficient balance!" << endl;
        cout << fixed << setprecision(2);
        cout << "Available Balance: Rs. " << userAccount.balance << endl;
        return;
    }

    if (amount > 20000) {
        cout << "Maximum withdrawal limit is Rs. 20,000 per transaction." << endl;
        return;
    }

    userAccount.balance -= amount;
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " withdrawn successfully!" << endl;
    cout << "Remaining Balance: Rs. " << userAccount.balance << endl;
    cout << "Please collect your cash." << endl;
}

// Function to change PIN
void changePIN() {
    string oldPIN, newPIN, confirmPIN;

    cout << "\n--- CHANGE PIN ---" << endl;
    cout << "Enter current PIN: ";
    cin >> oldPIN;

    if (oldPIN != userAccount.pin) {
        cout << "Incorrect current PIN!" << endl;
        return;
    }

    cout << "Enter new PIN (4 digits): ";
    cin >> newPIN;

    if (newPIN.length() != 4) {
        cout << "PIN must be exactly 4 digits!" << endl;
        return;
    }

    // Check if all characters are digits
    for (char c : newPIN) {
        if (!isdigit(c)) {
            cout << "PIN must contain only digits!" << endl;
            return;
        }
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPIN;

    if (newPIN != confirmPIN) {
        cout << "PINs do not match!" << endl;
        return;
    }

    userAccount.pin = newPIN;
    cout << "PIN changed successfully!" << endl;
}

// Main menu
void showMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "  1. Check Balance" << endl;
    cout << "  2. Deposit Money" << endl;
    cout << "  3. Withdraw Money" << endl;
    cout << "  4. Change PIN" << endl;
    cout << "  5. Exit" << endl;
    cout << "================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    clearScreen();
    displayHeader();

    // Verify PIN before access
    if (!verifyPIN()) {
        cout << "\nThank you for using My Bank ATM. Goodbye!" << endl;
        return 0;
    }

    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                changePIN();
                break;
            case 5:
                cout << "\nThank you for using My Bank ATM!" << endl;
                cout << "Please take your card. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice! Please select 1-5." << endl;
        }

        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
