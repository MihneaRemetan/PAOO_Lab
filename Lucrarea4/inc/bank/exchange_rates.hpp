#ifndef BANK_EXCHANGE_RATES_HPP
#define BANK_EXCHANGE_RATES_HPP

namespace bank {

// A non-trivial object meant to live for the whole program.
// Its constructor runs at dynamic initialization time (before main).
class ExchangeRates {
public:
    ExchangeRates();
    double eurToRon() const { return eurToRon_; }
    bool ready() const { return ready_; }

private:
    double eurToRon_;
    bool ready_;
};

// PROBLEM (Item 4): a non-local static object defined in exchange_rates.cpp.
// Another translation unit that uses it while initializing its OWN globals
// has no guarantee that it was already constructed.
extern ExchangeRates globalRates;

// FIX (Item 4): replace the non-local static with a function that returns a
// reference to a LOCAL static. The local static is constructed the first time
// the function is called, so it is always initialized before it is used.
ExchangeRates& rates();

} // namespace bank

#endif // BANK_EXCHANGE_RATES_HPP
