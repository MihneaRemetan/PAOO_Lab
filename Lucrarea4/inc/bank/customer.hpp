#ifndef BANK_CUSTOMER_HPP
#define BANK_CUSTOMER_HPP

#include <bank/tracer.hpp>

#include <string>

namespace bank {

// Item 4: assignment in the constructor body is NOT initialization.
// By the time the body runs, every member has already been default-constructed;
// the body then assigns over them (two steps instead of one).
class CustomerAssigned {
public:
    CustomerAssigned(const std::string& name, const std::string& address);
    ~CustomerAssigned();

private:
    Tracer name_;
    Tracer address_;
    int visits_;        // built-in type: holds garbage until the body sets it
};

// Item 4: the right way - member initializer list.
// Each member is constructed directly with its final value (one step).
// const members, references and members without a default constructor
// can ONLY be initialized here.
class Customer {
public:
    Customer(const std::string& name, const std::string& address, const std::string& cnp);
    ~Customer();

    void print() const;

private:
    // Members are ALWAYS initialized in declaration order, no matter the order
    // written in the initializer list (GCC/Clang warn with -Wreorder).
    // So keep the list in the same order as the declarations below.
    Tracer name_;
    Tracer address_;
    const std::string cnp_;   // const: impossible to assign in the body
    int visits_;
};

} // namespace bank

#endif // BANK_CUSTOMER_HPP
