#include <bank/tracer.hpp>

#include <iostream>
#include <utility>

namespace bank {

Tracer::Tracer() : label_("<default>")
{
    std::cout << "    [Tracer] default ctor        -> \"" << label_ << "\"\n";
}

Tracer::Tracer(const std::string& label) : label_(label)
{
    std::cout << "    [Tracer] ctor(string)        -> \"" << label_ << "\"\n";
}

Tracer::Tracer(const Tracer& other) : label_(other.label_)
{
    std::cout << "    [Tracer] copy ctor           -> \"" << label_ << "\"\n";
}

Tracer::Tracer(Tracer&& other) noexcept : label_(std::move(other.label_))
{
    other.label_ = "<moved-from>";
    std::cout << "    [Tracer] move ctor           -> \"" << label_ << "\"\n";
}

Tracer& Tracer::operator=(const Tracer& other)
{
    label_ = other.label_;
    std::cout << "    [Tracer] copy assignment     -> \"" << label_ << "\"\n";
    return *this;
}

Tracer& Tracer::operator=(Tracer&& other) noexcept
{
    label_ = std::move(other.label_);
    other.label_ = "<moved-from>";
    std::cout << "    [Tracer] move assignment     -> \"" << label_ << "\"\n";
    return *this;
}

Tracer::~Tracer()
{
    std::cout << "    [Tracer] dtor                -> \"" << label_ << "\"\n";
}

} // namespace bank
