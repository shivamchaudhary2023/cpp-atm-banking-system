// ============================================
// PROJECT  : ATM Banking System
// LANGUAGE : C++
// AUTHOR   : Shivam Chaudhary
// DATE     : 2026-07-17
// ============================================

#include <iostream>   // Line 8  - Input/Output ke liye
#include <string>     // Line 9  - String use karne ke liye
#include <iomanip>    // Line 10 - setprecision (decimal) ke liye
using namespace std;

// ---- LINE 14: Account ka data store karne ke liye structure ----
struct Account {
    string name;          // Line 16 - Account holder ka naam
    string accountNumber; // Line 17 - Account number
    string pin;           // Line 18 - 4 digit PIN
    double balance;       // Line 19 - Account balance (Rs.)
};

// ---- LINE 22: Default account data (single user system) ----
Account userAccount = {"Shivam Chaudhary", "ACC123456", "1234", 10000000.00};

// ---- LINE 25: Screen clear karne ka function (Windows) ----
void clearScreen() {
    system("cls"); // Line 27 - Windows command se screen clear hogi
}

// ---- LINE 30: ATM ka welcome header print karta hai ----
void displayHeader() {
    cout << "========================================" << endl;
    cout << "          WELCOME TO MY BANK ATM        " << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// ---- LINE 37: PIN verify karta hai, 3 galat attempts ke baad block ----
bool verifyPIN() {
    string enteredPIN;
    int attempts = 3; // Line 40 - Maximum 3 baar try kar sakte hain

    while (attempts > 0) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPIN;

        if (enteredPIN == userAccount.pin) { // Line 46 - PIN sahi hai?
            cout << "\nPIN verified! Welcome, " << userAccount.name << "!" << endl;
            cout << "Account Number: " << userAccount.accountNumber << endl;
            cout << endl;
            return true; // Line 50 - Login successful
        } else {
            attempts--;  // Line 52 - Galat PIN, attempt kam karo
            if (attempts > 0) {
                cout << "Wrong PIN! " << attempts << " attempt(s) remaining." << endl;
            }
        }
    }

    cout << "\nCard blocked! Too many wrong attempts." << endl;
    return false; // Line 59 - Login failed
}

// ---- LINE 62: Balance dikhane ka function ----
void checkBalance() {
    cout << "\n--- BALANCE INQUIRY ---" << endl;
    cout << "Account Holder : " << userAccount.name << endl;
    cout << "Account Number : " << userAccount.accountNumber << endl;
    cout << fixed << setprecision(2); // Line 68 - 2 decimal places
    cout << "Available Balance: Rs. " << userAccount.balance << endl;
}

// ---- LINE 71: Paisa deposit karne ka function ----
void depositMoney() {
    double amount;
    cout << "\n--- DEPOSIT MONEY ---" << endl;
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;

    if (amount <= 0) { // Line 78 - Amount positive honi chahiye
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > 100000) { // Line 83 - Max limit Rs. 1 Lakh per transaction
        cout << "Maximum deposit limit is Rs. 1,00,000 per transaction." << endl;
        return;
    }

    userAccount.balance += amount; // Line 88 - Balance mein amount add karo
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " deposited successfully!" << endl;
    cout << "New Balance: Rs. " << userAccount.balance << endl;
}

// ---- LINE 93: Paisa withdraw karne ka function ----
void withdrawMoney() {
    double amount;
    cout << "\n--- WITHDRAW MONEY ---" << endl;
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;

    if (amount <= 0) { // Line 100 - Amount positive honi chahiye
        cout << "Invalid amount! Please enter a positive value." << endl;
        return;
    }

    if (amount > userAccount.balance) { // Line 105 - Insufficient balance check
        cout << "Insufficient balance!" << endl;
        cout << fixed << setprecision(2);
        cout << "Available Balance: Rs. " << userAccount.balance << endl;
        return;
    }

    if (amount > 20000) { // Line 112 - Max withdrawal Rs. 20,000 per transaction
        cout << "Maximum withdrawal limit is Rs. 20,000 per transaction." << endl;
        return;
    }

    userAccount.balance -= amount; // Line 117 - Balance se amount ghataao
    cout << fixed << setprecision(2);
    cout << "\nRs. " << amount << " withdrawn successfully!" << endl;
    cout << "Remaining Balance: Rs. " << userAccount.balance << endl;
    cout << "Please collect your cash." << endl;
}

// ---- LINE 123: PIN change karne ka function ----
void changePIN() {
    string oldPIN, newPIN, confirmPIN;

    cout << "\n--- CHANGE PIN ---" << endl;
    cout << "Enter current PIN: ";
    cin >> oldPIN;

    if (oldPIN != userAccount.pin) { // Line 131 - Purana PIN sahi hai?
        cout << "Incorrect current PIN!" << endl;
        return;
    }

    cout << "Enter new PIN (4 digits): ";
    cin >> newPIN;

    if (newPIN.length() != 4) { // Line 139 - PIN exactly 4 digits hona chahiye
        cout << "PIN must be exactly 4 digits!" << endl;
        return;
    }

    // Line 144 - Check karo ki PIN sirf numbers mein hai
    for (char c : newPIN) {
        if (!isdigit(c)) {
            cout << "PIN must contain only digits!" << endl;
            return;
        }
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPIN;

    if (newPIN != confirmPIN) { // Line 155 - Dono PIN match karte hain?
        cout << "PINs do not match!" << endl;
        return;
    }

    userAccount.pin = newPIN; // Line 160 - Naya PIN save karo
    cout << "PIN changed successfully!" << endl;
}

// ---- LINE 163: Main menu dikhane ka function ----
void showMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "  1. Check Balance" << endl;   // Line 166
    cout << "  2. Deposit Money" << endl;   // Line 167
    cout << "  3. Withdraw Money" << endl;  // Line 168
    cout << "  4. Change PIN" << endl;      // Line 169
    cout << "  5. Exit" << endl;            // Line 170
    cout << "================================" << endl;
    cout << "Enter your choice: ";
}

// ---- LINE 174: Main function - program yahan se start hota hai ----
int main() {
    clearScreen();   // Line 176 - Screen saaf karo
    displayHeader(); // Line 177 - ATM header dikhao

    // Line 179 - PIN verify karo, galat hone par exit
    if (!verifyPIN()) {
        cout << "\nThank you for using My Bank ATM. Goodbye!" << endl;
        return 0;
    }

    int choice;
    bool running = true; // Line 186 - ATM tab tak chalega jab tak user exit na kare

    while (running) {
        showMenu();   // Line 189 - Menu dikhao
        cin >> choice; // Line 190 - User ka choice lo

        // Line 192 - User ke choice ke hisaab se function call karo
        switch (choice) {
            case 1:
                checkBalance();  // Line 195 - Balance dekho
                break;
            case 2:
                depositMoney();  // Line 198 - Paisa daalo
                break;
            case 3:
                withdrawMoney(); // Line 201 - Paisa nikalo
                break;
            case 4:
                changePIN();     // Line 204 - PIN badlo
                break;
            case 5:
                cout << "\nThank you for using My Bank ATM!" << endl;
                cout << "Please take your card. Goodbye!" << endl;
                running = false; // Line 209 - Loop band karo
                break;
            default:
                cout << "Invalid choice! Please select 1-5." << endl; // Line 212
        }

        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get(); // Line 218 - Enter dabane ka wait karo
        }
    }

    return 0; // Line 221 - Program successfully khatam
}
