#include "BankAccount.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    BankAccount account;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Initial balance: ";

    while (!(std::cin >> account)) {
        if (std::cin.eof()) {
            return 0;
        }
        clearInput();
        std::cout << "Invalid balance. Try again: ";
    }

    while (true) {
        std::cout << "\nBalance: " << account
                  << "\n1. Deposit\n2. Withdraw\n3. Accrue interest\n0. Exit\nChoice: ";

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            clearInput();
            std::cout << "Invalid choice\n";
            continue;
        }

        if (choice == 0) {
            break;
        }
        if (choice < 1 || choice > 3) {
            std::cout << "Invalid choice\n";
            continue;
        }

        std::cout << (choice == 3 ? "Interest rate (%): " : "Amount: ");
        double value;
        if (!(std::cin >> value)) {
            if (std::cin.eof()) {
                break;
            }
            clearInput();
            std::cout << "Invalid value\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    account.deposit(value);
                    break;
                case 2:
                    account.withdraw(value);
                    break;
                case 3:
                    account.accrueInterest(value);
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }
}
