#include <bank/customer.hpp>

#include <iostream>

namespace bank {

// -------------------------------------------------- body assignment (bad)
// Before the opening brace, name_ and address_ are default-constructed.
// Inside the body: build a temporary, assign it, destroy the temporary.
CustomerAssigned::CustomerAssigned(const std::string& name, const std::string& address)
{
    std::cout << "  [ctor body] CustomerAssigned - members already exist, now assigning:\n";
    name_ = Tracer(name);
    address_ = Tracer(address);
    visits_ = 0;
}

CustomerAssigned::~CustomerAssigned()
{
    std::cout << "  [dtor]  CustomerAssigned \"" << name_.label() << "\"\n";
}

// -------------------------------------------------- initializer list (good)
Customer::Customer(const std::string& name, const std::string& address, const std::string& cnp)
    : name_(name),
      address_(address),
      cnp_(cnp),         // cnp_ = cnp; in the body would not compile (const)
      visits_(0)         // built-in: must be initialized explicitly
{
    std::cout << "  [ctor body] Customer - nothing left to do, everything is initialized\n";
}

Customer::~Customer()
{
    std::cout << "  [dtor]  Customer \"" << name_.label() << "\"\n";
}

void Customer::print() const
{
    std::cout << "  Customer " << name_.label() << ", " << address_.label()
              << ", CNP " << cnp_ << ", visits " << visits_ << "\n";
}

} // namespace bank
