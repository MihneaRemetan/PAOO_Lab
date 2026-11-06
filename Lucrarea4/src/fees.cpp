#include <bank/fees.hpp>
#include <bank/exchange_rates.hpp>

#include <iostream>

namespace bank {

FeeSchedule::FeeSchedule(const char* name, double transferFeeEur, const ExchangeRates& rates)
    : name_(name),
      transferFeeEur_(transferFeeEur),
      transferFeeRon_(transferFeeEur * rates.eurToRon()),
      ratesWereReady_(rates.ready())
{
    std::cout << "  [ctor]  FeeSchedule \"" << name_ << "\" reads rates at " << &rates
              << (ratesWereReady_ ? " (already constructed)\n"
                                  : " (NOT constructed yet!)\n");
}

// Both objects are initialized before main, in this translation unit.
// globalRates lives in exchange_rates.cpp: if that file's globals are
// initialized later, brokenFees reads an object whose constructor has not run.
// Its memory is only zero-filled, so eurToRon() == 0 and ready() == false.
FeeSchedule brokenFees("broken (global)", 2.0, globalRates);

// rates() constructs the ExchangeRates on demand: always correct.
FeeSchedule safeFees("safe (local static)", 2.0, rates());

} // namespace bank
