#include <bank/loan.hpp>

#include <iostream>

namespace bank {

// Same order as the declarations: principal_, annualRatePercent_, monthlyRate_.
Loan::Loan(double principal, double annualRatePercent)
    : principal_(principal),
      annualRatePercent_(annualRatePercent),
      monthlyRate_(annualRatePercent_ / 12 / 100)   // safe: already initialized
{
    std::cout << "  [ctor]  Loan of " << principal_ << " RON at "
              << annualRatePercent_ << "% per year\n";
}

Loan::~Loan()
{
    std::cout << "  [dtor]  Loan of " << principal_ << " RON\n";
}

void Loan::print() const
{
    std::cout << "  monthly rate = " << monthlyRate_
              << ", interest in the first month = " << firstMonthInterest() << " RON\n";
}

} // namespace bank
