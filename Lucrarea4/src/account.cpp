#include <bank/account.hpp>

#include <iostream>
#include <stdexcept>

namespace bank {

int Account::nextNumber_ = 1;   // static member: defined (and initialized) once

static std::string makeIban(int number)
{
    std::string digits = std::to_string(number);
    return "RO49PAOO" + std::string(16 - digits.size(), '0') + digits;
}

// --------------------------------------------------------------------- Account
Account::Account(const std::string& owner, double balance)
    : owner_(owner),
      iban_(makeIban(nextNumber_++)),
      balance_(balance)
{
    std::cout << "  [ctor]  Account " << iban_ << " (" << owner_ << ")\n";
}

Account::~Account()
{
    std::cout << "  [dtor]  Account " << iban_ << " (" << owner_ << ")\n";
}

void Account::deposit(double amount)
{
    if (amount <= 0)
        throw std::invalid_argument("deposit must be positive");
    balance_ += amount;
}

bool Account::withdraw(double amount)
{
    if (amount <= 0 || amount > balance_)
        return false;
    balance_ -= amount;
    return true;
}

bool Account::transferTo(Account& destination, double amount)
{
    if (&destination == this || !withdraw(amount))
        return false;
    destination.deposit(amount);
    return true;
}

void Account::print() const
{
    std::cout << "  " << iban_ << "  " << owner_ << ": " << balance_ << " RON\n";
}

// -------------------------------------------------------------- SafeDepositBox
SafeDepositBox::SafeDepositBox(int number) : number_(number)
{
    std::cout << "  [ctor]  SafeDepositBox #" << number_ << "\n";
}

SafeDepositBox::~SafeDepositBox()
{
    std::cout << "  [dtor]  SafeDepositBox #" << number_ << "\n";
}

// The copy constructor and operator= are intentionally NOT defined here.

// ----------------------------------------------------------------------- Vault
Vault::Vault(const std::string& branch)
    : Uncopyable(),
      branch_(branch),
      goldBars_(0)
{
    std::cout << "  [ctor]  Vault \"" << branch_ << "\"\n";
}

Vault::~Vault()
{
    std::cout << "  [dtor]  Vault \"" << branch_ << "\" (" << goldBars_ << " bars)\n";
}

} // namespace bank
