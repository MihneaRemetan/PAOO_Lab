#include <bank/bank_config.hpp>
#include <bank/account.hpp>
#include <bank/customer.hpp>
#include <bank/exchange_rates.hpp>
#include <bank/fees.hpp>
#include <bank/generated.hpp>
#include <bank/loan.hpp>

#include <iostream>
#include <string>
#include <utility>

using namespace bank;

static void section(const char* title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// ============================================================== Item 4
// A plain struct (C part of C++): its members are NOT initialized
// when an object is defined as a local variable.
struct Point {
    int x;
    int y;
};

static void builtinInitDemo()
{
    section("Item 4.1 - Built-in types are not always initialized");

    // int counter;            // local built-in: indeterminate value,
    // std::cout << counter;   // reading it is undefined behavior
    // Point p;                // p.x and p.y: indeterminate as well

    int counter = 0;           // always initialize manually...
    double rate{};             // ...or value-initialize: {} -> 0.0
    Point p{};                 // {} -> x = 0, y = 0
    Point q{3, 4};             // aggregate initialization

    static int calls;          // static storage: zero-initialized automatically
    ++calls;

    std::cout << "  counter = " << counter << ", rate = " << rate
              << ", p = (" << p.x << ", " << p.y << ")"
              << ", q = (" << q.x << ", " << q.y << ")"
              << ", static calls = " << calls << "\n"
              << "  Rule: initialize every object before using it - built-ins\n"
              << "  manually, everything else in the constructors.\n";
}

static void initializerListDemo()
{
    section("Item 4.2 - Assignment in the body vs. member initializer list");

    std::cout << "  a) assignment in the constructor body:\n";
    {
        CustomerAssigned slow("Ana", "Timisoara");
    }

    std::cout << "\n  b) member initializer list:\n";
    {
        Customer fast("Ana", "Timisoara", "6000101350011");
        fast.print();
    }
    std::cout << "  -> the initializer list builds each member once; the body version\n"
              << "     default-constructs, builds a temporary, assigns and destroys it.\n";
}

static void memberOrderDemo()
{
    section("Item 4.3 - Members are initialized in declaration order");
    Loan loan(100000, 6.0);   // monthlyRate_ is computed from annualRatePercent_
    loan.print();
    std::cout << "  -> correct only because annualRatePercent_ is DECLARED before\n"
              << "     monthlyRate_ (see the BadLoan counter-example in loan.hpp).\n";
}

static void staticInitOrderDemo()
{
    section("Item 4.4 - Initialization order of non-local statics (other .cpp files)");
    std::cout << "  (the FeeSchedule/ExchangeRates messages above main() show the order)\n";

    const FeeSchedule* schedules[] = { &brokenFees, &safeFees };
    for (const FeeSchedule* f : schedules) {
        std::cout << "  " << f->name() << ": " << f->transferFeeEur() << " EUR = "
                  << f->transferFeeRon() << " RON"
                  << (f->ratesWereReady() ? "" : "   <- used ExchangeRates before its constructor ran")
                  << "\n";
    }
    std::cout << "  globalRates is constructed now: 1 EUR = " << globalRates.eurToRon()
              << " RON, but brokenFees was computed too early.\n"
              << "  Fix: return a reference to a local static (rates()).\n";
}

// ============================================================== Item 5
static void generatedFunctionsDemo()
{
    section("Item 5.1 - Functions the compiler writes for Wallet");

    std::cout << "  Wallet a;                    (generated default ctor)\n";
    Wallet a;

    std::cout << "  Wallet b(a);                 (generated copy ctor)\n";
    Wallet b(a);

    std::cout << "  b = a;                       (generated copy assignment)\n";
    b = a;

    std::cout << "  Wallet c(std::move(a));      (generated move ctor)\n";
    Wallet c(std::move(a));

    std::cout << "  c = Wallet();                (default ctor + generated move assignment + dtor)\n";
    c = Wallet();

    std::cout << "  Leaving scope                (generated dtor, for c, b, a):\n";
}

static void memberwiseCopyDemo()
{
    section("Item 5.2 - Generated copies are memberwise (pointers: shallow)");

    RawCard original{new int(1234)};
    RawCard copy = original;           // generated copy ctor: copies the ADDRESS
    *copy.pin = 9999;                  // change the PIN through the copy

    std::cout << "  original.pin -> " << original.pin << " = " << *original.pin << "\n"
              << "  copy.pin     -> " << copy.pin << " = " << *copy.pin << "\n"
              << "  -> same address: the copy did not get its own int.\n"
              << "  The generated ~RawCard() does not delete the pointer either,\n"
              << "  so without the line below the int would leak. It is deleted\n"
              << "  exactly once (deleting it through both objects = double delete).\n";
    delete original.pin;
}

static void suppressedFunctionsDemo()
{
    section("Item 5.3 - When the compiler does NOT write them");

    // Iban none;                  // error: no default constructor (Iban(string) declared)
    Iban iban("RO49PAOO0000000000000001");
    Iban ibanCopy = iban;          // copy constructor is still generated
    std::cout << "  Iban: no default ctor, copy ctor OK -> " << ibanCopy.code() << "\n";

    std::cout << "\n  LoggedWallet has a user-declared destructor -> no move operations.\n"
              << "  LoggedWallet moved(std::move(original)) calls... the COPY ctor:\n";
    {
        LoggedWallet original;
        LoggedWallet moved(std::move(original));
    }

    std::string first = "first";
    std::string second = "second";
    NamedValue n1(first, 1);
    NamedValue n2(second, 2);
    NamedValue n3 = n1;            // copy constructor: generated, fine
    // n2 = n1;                    // error: copy assignment implicitly deleted
                                   // (cannot re-bind a reference / change a const)
    std::cout << "\n  NamedValue (reference + const members): copy ctor OK -> "
              << n3.name() << "=" << n3.value()
              << ", copy assignment does not exist (n2 stays "
              << n2.name() << "=" << n2.value() << ")\n";
}

// ============================================================== Item 6
static void disallowCopyDemo()
{
    section("Item 6 - Disallowing the generated functions we do not want");
    std::cout << "  C++11 style - Account with = delete:\n";

    Account ana("Ana", 1000);
    Account dan("Dan", 250);

    // Account copy = ana;         // error: use of deleted function Account(const Account&)
    // dan = ana;                  // error: use of deleted operator=
    // Account moved(std::move(ana));  // error: move ctor not generated -> copy -> deleted

    std::cout << "  Transfer 300 RON Ana -> Dan (passed by reference, nothing copied):\n";
    ana.transferTo(dan, 300);
    ana.print();
    dan.print();
    std::cout << "  Transfer 5000 RON Dan -> Ana: "
              << (dan.transferTo(ana, 5000) ? "ok" : "rejected (insufficient funds)") << "\n";

    std::cout << "\n  C++98 style (book) - private, never defined:\n";
    SafeDepositBox box(17);
    // SafeDepositBox other(box);  // error: SafeDepositBox(const SafeDepositBox&) is private
    std::cout << "  Box #" << box.number() << " cannot be copied by client code.\n";

    std::cout << "\n  C++98 style - Vault : private Uncopyable:\n";
    Vault vault("Timisoara Centru");
    vault.store(12);
    // Vault other = vault;        // error: Uncopyable(const Uncopyable&) is private
    // vault = Vault("Arad");      // error: Uncopyable::operator= is private
    std::cout << "  Vault \"" << vault.branch() << "\" holds " << vault.goldBars()
              << " bars and can never be duplicated.\n";

    std::cout << "  Leaving scope:\n";
}

int main()
{
    std::cout << "\nApplication " << APP_NAME << "\n"
              << "Version " << APP_VERSION << "\n"
              << APP_LAB << "\n";

    builtinInitDemo();
    initializerListDemo();
    memberOrderDemo();
    staticInitOrderDemo();

    generatedFunctionsDemo();
    memberwiseCopyDemo();
    suppressedFunctionsDemo();

    disallowCopyDemo();

    std::cout << "\nGood bye!\n";
    return 0;
}
