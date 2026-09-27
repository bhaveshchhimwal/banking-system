# Banking System in C++

A console-based banking system implemented in C++ using Object-Oriented
Programming principles. The project simulates core banking operations
such as account management, secure login, and transactions, with
persistent data storage using file handling.

## Features

-   Create a new bank account
-   Secure login using Account Number and PIN
-   Balance enquiry
-   Deposit money
-   Withdraw money with minimum balance constraint
-   Persistent data storage using file handling

## Tech Stack

-   Language: C++
-   Concepts: Object-Oriented Programming (OOP)
-   Data Structures: std::map
-   File Handling: fstream
-   Exception Handling

## How It Works

The system is menu-driven and allows users to perform the following
operations:

1.  Open Account
2.  Login using Account Number and PIN
3.  Check Balance
4.  Deposit Money
5.  Withdraw Money
6.  Logout

All account data is stored in a file (data/Bank.data) to ensure
persistence across program runs.

## Getting Started

### Prerequisites

-   C++ compiler (g++, clang, etc.)

### Compilation

g++ main.cpp -o bank

### Execution

./bank

## Data Storage

-   Account data is stored in data/Bank.data
-   The file is automatically created and updated during execution

## Limitations

-   Console-based interface
-   No encryption for PIN storage
-   Single-user system
-   Limited validation and error handling

## Future Improvements

-   Password hashing for secure authentication
-   Graphical User Interface (GUI)
-   Transaction history tracking
-   Multi-user and concurrent access support
# banking-system
