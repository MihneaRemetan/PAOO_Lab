#ifndef BANK_TRACER_HPP
#define BANK_TRACER_HPP

#include <string>

namespace bank {

// Helper used as a data member in the demos: every special member function
// prints a message, so we can SEE which functions the compiler calls
// (and which ones it silently wrote for the class that contains a Tracer).
class Tracer {
public:
    Tracer();                                   // default constructor
    explicit Tracer(const std::string& label);  // "real" constructor
    Tracer(const Tracer& other);                // copy constructor
    Tracer(Tracer&& other) noexcept;            // move constructor
    Tracer& operator=(const Tracer& other);     // copy assignment
    Tracer& operator=(Tracer&& other) noexcept; // move assignment
    ~Tracer();

    const std::string& label() const { return label_; }

private:
    std::string label_;
};

} // namespace bank

#endif // BANK_TRACER_HPP
