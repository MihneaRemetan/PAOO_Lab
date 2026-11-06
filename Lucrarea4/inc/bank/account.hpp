#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <bank/uncopyable.hpp>

#include <string>
#include <type_traits>

namespace bank {

// ---------------------------------------------------------------------------
// Item 6, modern way (C++11): = delete.
// A bank account is unique (one IBAN, one balance). A copy would duplicate the
// money, so the compiler-generated copy functions must not exist.
// ---------------------------------------------------------------------------
class Account {
public:
    Account(const std::string& owner, double balance);
    ~Account();

    Account(const Account&) = delete;              // no copy constructor
    Account& operator=(const Account&) = delete;   // no copy assignment
    // Declaring the copy operations also means the move operations are NOT
    // generated (Item 5), so an Account cannot be moved either.

    void deposit(double amount);
    bool withdraw(double amount);
    bool transferTo(Account& destination, double amount);   // by reference: no copy

    const std::string& iban() const { return iban_; }
    double balance() const { return balance_; }
    void print() const;

private:
    static int nextNumber_;

    const std::string owner_;
    const std::string iban_;
    double balance_;
};

static_assert(!std::is_copy_constructible<Account>::value, "Account: no copy ctor");
static_assert(!std::is_copy_assignable<Account>::value,    "Account: no copy assignment");
static_assert(!std::is_move_constructible<Account>::value, "Account: no move ctor either");

// ---------------------------------------------------------------------------
// Item 6, C++98 way from the book (HomeForSale): declare the copy functions
// PRIVATE and never define them.
//  - outside code             -> compile error (they are private)
//  - members and friends      -> LINK error (no definition exists)
// ---------------------------------------------------------------------------
class SafeDepositBox {
public:
    explicit SafeDepositBox(int number);
    ~SafeDepositBox();

    int number() const { return number_; }

private:
    SafeDepositBox(const SafeDepositBox&);              // declared, never defined
    SafeDepositBox& operator=(const SafeDepositBox&);   // declared, never defined

    int number_;
};

static_assert(!std::is_copy_constructible<SafeDepositBox>::value, "SafeDepositBox: no copy ctor");
static_assert(!std::is_copy_assignable<SafeDepositBox>::value,    "SafeDepositBox: no copy assignment");

// ---------------------------------------------------------------------------
// Item 6, C++98 way, improved: inherit privately from Uncopyable.
// Vault declares nothing about copying; the compiler tries to generate the
// copy functions, but they would need Uncopyable's private ones -> deleted.
// ---------------------------------------------------------------------------
class Vault : private Uncopyable {
public:
    explicit Vault(const std::string& branch);
    ~Vault();

    void store(int bars) { goldBars_ += bars; }
    int goldBars() const { return goldBars_; }
    const std::string& branch() const { return branch_; }

private:
    std::string branch_;
    int goldBars_;
};

static_assert(!std::is_copy_constructible<Vault>::value, "Vault: no copy ctor");
static_assert(!std::is_copy_assignable<Vault>::value,    "Vault: no copy assignment");

} // namespace bank

#endif // BANK_ACCOUNT_HPP
