// ============================================
// PROJECT  : ATM Banking System
// LANGUAGE : C++
// AUTHOR   : Shivam Chaudhary
// DATE     : 2026-07-17
// ============================================

#include <iostream>   // Line 8  - For input/output operations
#include <string>     // Line 9  - For using string data type
#include <iomanip>    // Line 10 - For setprecision (decimal formatting)
using namespace std;

// ---- LINE 14: Structure to store account data ----
struct Account {
    string name;          // Line 16 - Account holder name
    string accountNumber; // Line 17 - Unique account number
    string pin;           // Line 18 - 4 digit secret PIN
    double balance;       // Line 19 - Account balance (Rs.)
};

// ---- LINE 22: Default account data (single user system) ----
Account userAccount = {"Shivam Chaudhary", "ACC123456", "1234", 10000000.00};

// ---- LINE 25: Function to clear the screen (Windows) ----
void clearScreen() {
    system("cls"); // Line 27 - Clears the console screen on Windows
}

// ---- LINE 30: Function to display ATM welcome header ----
void displayHeader() {
    cout << "========================================" << endl;
    cout << "          WELCOME TO MY BANK ATM        " << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// ---- LINE 37: Verifies PIN, blocks after 3 wrong attempts ----
bool verifyPIN() {
    string enteredPIN;
    int attempts = 3; // Line 40 - Maximum 3 attempts allowed

    while (attempts > 0) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPIN;

        if (enteredPIN == userAccount.pin) { // Line 46 - Check if PIN is correct
            cout << "\nPIN verified! Welcome, " << userAccount.name << "!" << endl;
            cout << "Account Number: " << userAccount.accountNumber << endl;
            cout << endl;
            return true; // Line 50 - Login successful
        } else {
            attempts--;  // Line 52 - Wrong PIN, reduce attempt count
            if (attempts > 0) {
                cout << "Wrong PIN! " << attempts << " attempt(s) remaining." << endl;
            }
        }
    }

    cout << "\nCard blocked! Too many wrong attempts." << endl;
    return false; // Line 59 - Login failed
}

// ---- LINE 62: Function to display account balance ----
void checkBalance() {
    cout << "\n--- BALANCE INQUIRY ---" << endl;
    cout << "Account Holder : " << userAccount.name << endl;
    cout << "Account Number : " << userAccount.accountNumber << endl;
    cout << fixed << setprecision(2); // Line 68 - Show 2 decimal places
    cout << "Available Balance: Rs. " << userAccount.balance << endl;
}

// ---- LINE 71: Function to deposit money into account ----
void depositMoney() {
    double amount;
    cout << "\n--- DEPOSIT MONEY ---" << endl;
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;

    if (amount <= 0) { // Line 78 - Amount must be positive
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > 100000) { // Line 83 - Max deposit limit Rs. 1 Lakh per transaction
        cout << "Maximum deposit limit is Rs. 1,00,000 per transaction." << endl;
        return;
    }

    userAccount.balance += amount; // Line 88 - Add amount to balance
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " deposited successfully!" << endl;
    cout << "New Balance: Rs. " << userAccount.balance << endl;
}

// ---- LINE 93: Function to withdraw money from account ----
void withdrawMoney() {
    double amount;
    cout << "\n--- WITHDRAW MONEY ---" << endl;
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;

    if (amount <= 0) { // Line 100 - Amount must be positive
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > userAccount.balance) { // Line 105 - Check for insufficient balance
        cout << "Insufficient balance!" << endl;
        cout << fixed << setprecision(2);
        cout << "Available Balance: Rs. " << userAccount.balance << endl;
        return;
    }

    if (amount > 20000) { // Line 112 - Max withdrawal Rs. 20,000 per transaction
        cout << "Maximum withdrawal limit is Rs. 20,000 per transaction." << endl;
        return;
    }

    userAccount.balance -= amount; // Line 117 - Deduct amount from balance
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " withdrawn successfully!" << endl;
    cout << "Remaining Balance: Rs. " << userAccount.balance << endl;
    cout << "Please collect your cash." << endl;
}

// ---- LINE 123: Function to change account PIN ----
void changePIN() {
    string oldPIN, newPIN, confirmPIN;

    cout << "\n--- CHANGE PIN ---" << endl;
    cout << "Enter current PIN: ";
    cin >> oldPIN;

    if (oldPIN != userAccount.pin) { // Line 131 - Verify old PIN is correct
        cout << "Incorrect current PIN!" << endl;
        return;
    }

    cout << "Enter new PIN (4 digits): ";
    cin >> newPIN;

    if (newPIN.length() != 4) { // Line 139 - PIN must be exactly 4 digits
        cout << "PIN must be exactly 4 digits!" << endl;
        return;
    }

    // Line 144 - Ensure PIN contains only numeric digits
    for (char c : newPIN) {
        if (!isdigit(c)) {
            cout << "PIN must contain only digits!" << endl;
            return;
        }
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPIN;

    if (newPIN != confirmPIN) { // Line 155 - Both PINs must match
        cout << "PINs do not match!" << endl;
        return;
    }

    userAccount.pin = newPIN; // Line 160 - Save the new PIN
    cout << "PIN changed successfully!" << endl;
}

// ---- LINE 163: Function to display the main menu ----
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

// ---- LINE 174: Main function - program execution starts here ----
int main() {
    clearScreen();   // Line 176 - Clear screen on startup
    displayHeader(); // Line 177 - Show ATM header

    // Line 179 - Verify PIN before allowing access
    if (!verifyPIN()) {
        cout << "\nThank you for using My Bank ATM. Goodbye!" << endl;
        return 0;
    }

    int choice;
    bool running = true; // Line 186 - ATM runs until user chooses to exit

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                checkBalance();  // Line 195 - Show balance
                break;
            case 2:
                depositMoney();  // Line 198 - Deposit money
                break;
            case 3:
                withdrawMoney(); // Line 201 - Withdraw money
                break;
            case 4:
                changePIN();     // Line 204 - Change PIN
                break;
            case 5:
                cout << "\nThank you for using My Bank ATM!" << endl;
                cout << "Please take your card. Goodbye!" << endl;
                running = false; // Line 209 - Stop the loop
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

    return 0; // Line 221 - Program ends successfully
}
