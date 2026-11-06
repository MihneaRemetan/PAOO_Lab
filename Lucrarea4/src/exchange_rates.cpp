#include <bank/exchange_rates.hpp>

#include <iostream>

namespace bank {

ExchangeRates::ExchangeRates()
    : eurToRon_(4.97),
      ready_(true)
{
    std::cout << "  [ctor]  ExchangeRates at " << this << " (before main)\n";
}

// Non-local static: constructed "sometime" before main, order vs. other
// translation units is unspecified.
ExchangeRates globalRates;

// Local static: constructed on the first call (thread-safe since C++11).
ExchangeRates& rates()
{
    static ExchangeRates instance;
    return instance;
}

} // namespace bank
