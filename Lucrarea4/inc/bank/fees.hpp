#ifndef BANK_FEES_HPP
#define BANK_FEES_HPP

namespace bank {

class ExchangeRates;

// A global fee schedule whose constructor needs the exchange rates.
class FeeSchedule {
public:
    FeeSchedule(const char* name, double transferFeeEur, const ExchangeRates& rates);

    const char* name() const { return name_; }
    double transferFeeEur() const { return transferFeeEur_; }
    double transferFeeRon() const { return transferFeeRon_; }
    bool ratesWereReady() const { return ratesWereReady_; }

private:
    const char* name_;
    double transferFeeEur_;
    double transferFeeRon_;
    bool ratesWereReady_;
};

extern FeeSchedule brokenFees;   // built from globalRates (non-local static)
extern FeeSchedule safeFees;     // built from rates()     (local static)

} // namespace bank

#endif // BANK_FEES_HPP
