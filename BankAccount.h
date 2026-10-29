#pragma once

#include <iosfwd>

class BankAccount {
private:
    double* balance_;

    void setBalance(double balance);

public:
    BankAccount();
    explicit BankAccount(double balance);
    BankAccount(const BankAccount& other);
    BankAccount(BankAccount&& other) noexcept;
    ~BankAccount();

    BankAccount& operator=(const BankAccount& other);
    BankAccount& operator=(BankAccount&& other) noexcept;

    double getBalance() const noexcept;
    void deposit(double amount);
    void withdraw(double amount);
    void accrueInterest(double rate);

    friend std::istream& operator>>(std::istream& input, BankAccount& account);
    friend std::ostream& operator<<(std::ostream& output, const BankAccount& account);
};
