#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define MIN_BALANCE 500

class InsufficientFunds {};
class InvalidLogin {};

class Account {
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    int pin;
    static long NextAccountNumber;

public:
    Account() {}

    Account(string fname, string lname, float bal, int p) {
        NextAccountNumber++;
        accountNumber = NextAccountNumber;
        firstName = fname;
        lastName = lname;
        balance = bal;
        pin = p;
    }

    long getAccNo() const { return accountNumber; }

    bool validatePIN(int p) const {
        return pin == p;
    }

    void Deposit(float amount) {
        balance += amount;
    }

    void Withdraw(float amount) {
        if (balance - amount < MIN_BALANCE)
            throw InsufficientFunds();
        balance -= amount;
    }

    static void setLastAccountNumber(long accNo) {
        NextAccountNumber = accNo;
    }

    // Save
    friend ofstream &operator<<(ofstream &ofs, const Account &acc) {
        ofs << acc.accountNumber << endl
            << acc.firstName << endl
            << acc.lastName << endl
            << acc.balance << endl
            << acc.pin << endl;
        return ofs;
    }

    // Load
    friend ifstream &operator>>(ifstream &ifs, Account &acc) {
        ifs >> acc.accountNumber >> acc.firstName >> acc.lastName >> acc.balance >> acc.pin;
        return ifs;
    }

    // Display
    friend ostream &operator<<(ostream &os, const Account &acc) {
        os << "\n---------------------------\n";
        os << "Account No: " << acc.accountNumber << endl;
        os << "Name: " << acc.firstName << " " << acc.lastName << endl;
        os << "Balance: " << acc.balance << endl;
        os << "---------------------------\n";
        return os;
    }
};

long Account::NextAccountNumber = 1000;

class Bank {
private:
    map<long, Account> accounts;

public:
    Bank() {
        ifstream infile("data/Bank.data");
        Account acc;
        long lastAccNo = 1000;

        while (infile >> acc) {
            accounts[acc.getAccNo()] = acc;
            lastAccNo = acc.getAccNo();
        }

        Account::setLastAccountNumber(lastAccNo);
        infile.close();
    }

    void save() {
        ofstream outfile("data/Bank.data");
        for (auto &p : accounts) {
            outfile << p.second;
        }
        outfile.close();
    }

    Account OpenAccount(string fname, string lname, float balance, int pin) {
        Account acc(fname, lname, balance, pin);
        accounts[acc.getAccNo()] = acc;
        save();
        return acc;
    }

    Account& getAccount(long accNo) {
        return accounts[accNo];
    }
};

int main() {
    Bank bank;
    int choice;

    cout << "🏦 Banking System\n";

    do {
        cout << "\n1. Open Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                string fname, lname;
                float balance;
                int pin;

                cin.ignore();

                cout << "Enter First Name: ";
                getline(cin, fname);

                cout << "Enter Last Name: ";
                getline(cin, lname);

                cout << "Enter Initial Balance: ";
                cin >> balance;

                cout << "Set 4-digit PIN: ";
                cin >> pin;

                Account acc = bank.OpenAccount(fname, lname, balance, pin);

                cout << "\nAccount Created!\n";
                cout << "Account Number: " << acc.getAccNo() << endl;
                cout << acc;
            }

            else if (choice == 2) {
                long accNo;
                int pin;

                cout << "Enter Account Number: ";
                cin >> accNo;

                cout << "Enter PIN: ";
                cin >> pin;

                Account &acc = bank.getAccount(accNo);

                if (!acc.validatePIN(pin))
                    throw InvalidLogin();

                int opt;
                do {
                    cout << "\n1. Balance\n2. Deposit\n3. Withdraw\n4. Logout\n";
                    cin >> opt;

                    if (opt == 1) {
                        cout << acc;
                    }
                    else if (opt == 2) {
                        float amt;
                        cout << "Enter Amount: ";
                        cin >> amt;
                        acc.Deposit(amt);
                        cout << "Deposited!\n";
                    }
                    else if (opt == 3) {
                        float amt;
                        cout << "Enter Amount: ";
                        cin >> amt;
                        acc.Withdraw(amt);
                        cout << "Withdrawn!\n";
                    }

                } while (opt != 4);

                bank.save();
            }

        } catch (InvalidLogin) {
            cout << "Invalid Account Number or PIN\n";
        } catch (InsufficientFunds) {
            cout << "Insufficient Balance\n";
        }

    } while (choice != 3);

    return 0;
}