#include "BankAccount.h"

#include <cmath>
#include <istream>
#include <ostream>
#include <stdexcept>

BankAccount::BankAccount() : BankAccount(0.0) {}

BankAccount::BankAccount(double balance) : balance_(nullptr) {
    setBalance(balance);
}

BankAccount::BankAccount(const BankAccount& other)
    : BankAccount(other.getBalance()) {}

BankAccount::BankAccount(BankAccount&& other) noexcept
    : balance_(other.balance_) {
    other.balance_ = nullptr;
}

BankAccount::~BankAccount() {
    delete balance_;
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        setBalance(other.getBalance());
    }
    return *this;
}

BankAccount& BankAccount::operator=(BankAccount&& other) noexcept {
    if (this != &other) {
        delete balance_;
        balance_ = other.balance_;
        other.balance_ = nullptr;
    }
    return *this;
}

double BankAccount::getBalance() const noexcept {
    return balance_ ? *balance_ : 0.0;
}

void BankAccount::setBalance(double balance) {
    if (!std::isfinite(balance) || balance < 0.0) {
        throw std::invalid_argument("Invalid balance");
    }
    if (balance_) {
        *balance_ = balance;
    } else {
        balance_ = new double(balance);
    }
}

void BankAccount::deposit(double amount) {
    if (!std::isfinite(amount) || amount <= 0.0) {
        throw std::invalid_argument("Invalid deposit amount");
    }
    setBalance(getBalance() + amount);
}

void BankAccount::withdraw(double amount) {
    if (!std::isfinite(amount) || amount <= 0.0) {
        throw std::invalid_argument("Invalid withdrawal amount");
    }
    if (amount > getBalance()) {
        throw std::invalid_argument("Insufficient funds");
    }
    setBalance(getBalance() - amount);
}

void BankAccount::accrueInterest(double rate) {
    if (!std::isfinite(rate) || rate < 0.0) {
        throw std::invalid_argument("Invalid interest rate");
    }
    const double interest = getBalance() * (rate / 100.0);
    setBalance(getBalance() + interest);
}

std::istream& operator>>(std::istream& input, BankAccount& account) {
    double balance{};
    if (!(input >> balance)) {
        return input;
    }
    if (!std::isfinite(balance) || balance < 0.0) {
        input.setstate(std::ios::failbit);
        return input;
    }
    account.setBalance(balance);
    return input;
}

std::ostream& operator<<(std::ostream& output, const BankAccount& account) {
    return output << account.getBalance();
}
