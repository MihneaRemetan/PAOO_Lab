#ifndef BANK_GENERATED_HPP
#define BANK_GENERATED_HPP

#include <bank/tracer.hpp>

#include <string>
#include <type_traits>

namespace bank {

// ---------------------------------------------------------------------------
// Item 5: a class that declares NO special member function.
// The compiler silently writes (only if they are used):
//   Wallet();                              default constructor
//   Wallet(const Wallet&);                 copy constructor
//   Wallet& operator=(const Wallet&);      copy assignment
//   Wallet(Wallet&&);                      move constructor   (C++11)
//   Wallet& operator=(Wallet&&);           move assignment    (C++11)
//   ~Wallet();                             destructor
// Each generated function simply calls the same function on every member
// (here: on the two Tracer members), in declaration order.
// ---------------------------------------------------------------------------
struct Wallet {
    Tracer owner{"owner"};
    Tracer currency{"RON"};
};

// ---------------------------------------------------------------------------
// Item 5: generated copies are MEMBERWISE. For a raw pointer member, only the
// address is copied (shallow copy), and the generated destructor does NOT
// delete what the pointer points to.
// (Lab 3 showed the fix: write the copy constructor and destructor yourself.)
// ---------------------------------------------------------------------------
struct RawCard {
    int* pin;
};

// ---------------------------------------------------------------------------
// Item 5: declaring ANY constructor stops the compiler from writing the
// default constructor.
// ---------------------------------------------------------------------------
class Iban {
public:
    explicit Iban(const std::string& code) : code_(code) {}
    const std::string& code() const { return code_; }
private:
    std::string code_;
};
static_assert(!std::is_default_constructible<Iban>::value,
              "Iban(): not generated, because Iban(const std::string&) was declared");
static_assert(std::is_copy_constructible<Iban>::value,
              "the copy constructor is still generated");

// ---------------------------------------------------------------------------
// Item 5 (C++11 extension): declaring a destructor (or copy operations)
// stops the compiler from writing the MOVE operations.
// std::move() then silently falls back to the COPY constructor.
// ---------------------------------------------------------------------------
struct LoggedWallet {
    Tracer owner{"logged-owner"};
    ~LoggedWallet() {}   // "harmless" empty destructor... disables moves
};

// ---------------------------------------------------------------------------
// Item 5: cases where the compiler REFUSES to write copy assignment.
// It still writes the copy constructor (initializing a reference / const is
// fine), but assigning would mean re-binding a reference or changing a const,
// so operator= is implicitly deleted.
// (Same thing happens if a base class makes its operator= private.)
// ---------------------------------------------------------------------------
class NamedValue {
public:
    NamedValue(std::string& name, int value) : name_(name), value_(value) {}
    const std::string& name() const { return name_; }
    int value() const { return value_; }
private:
    std::string& name_;   // reference member
    const int value_;     // const member
};
static_assert(std::is_copy_constructible<NamedValue>::value,
              "copy constructor: generated");
static_assert(!std::is_copy_assignable<NamedValue>::value,
              "copy assignment: NOT generated (reference + const members)");

} // namespace bank

#endif // BANK_GENERATED_HPP
