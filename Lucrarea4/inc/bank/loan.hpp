#ifndef BANK_LOAN_HPP
#define BANK_LOAN_HPP

namespace bank {

// Item 4: members are initialized in the order they are DECLARED in the class,
// not in the order they are written in the member initializer list.
//
// WRONG (do not do this):
//     class BadLoan {
//         double monthlyRate_;          // declared first -> initialized first
//         double annualRatePercent_;
//     public:
//         BadLoan(double annual)
//             : annualRatePercent_(annual),
//               monthlyRate_(annualRatePercent_ / 12 / 100)   // reads garbage!
//         {}
//     };
// monthlyRate_ is built first and reads annualRatePercent_ before it has a
// value: undefined behavior. g++ -Wall warns with -Wreorder.
// Reordering the list does not help: the DECLARATIONS must be reordered.
//
// RIGHT: a member that depends on another is declared after it.
class Loan {
public:
    Loan(double principal, double annualRatePercent);
    ~Loan();

    double monthlyRate() const { return monthlyRate_; }
    double firstMonthInterest() const { return principal_ * monthlyRate_; }
    void print() const;

private:
    double principal_;
    double annualRatePercent_;   // declared BEFORE monthlyRate_ ...
    double monthlyRate_;         // ... because it is computed from it
};

} // namespace bank

#endif // BANK_LOAN_HPP
