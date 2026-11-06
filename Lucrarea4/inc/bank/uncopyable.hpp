#ifndef BANK_UNCOPYABLE_HPP
#define BANK_UNCOPYABLE_HPP

namespace bank {

// Item 6, the C++98 technique from the book:
// copy constructor and copy assignment are declared PRIVATE and never defined.
//  - code outside the class    -> compile error (private)
//  - members / friends         -> would get a LINK error (no definition)...
// ...so they are moved into this base class: any attempt to copy a derived
// class needs the base's private functions -> compile error everywhere.
class Uncopyable {
protected:
    Uncopyable() {}      // allow construction and destruction
    ~Uncopyable() {}     // of derived objects

private:
    Uncopyable(const Uncopyable&);              // declared, not defined
    Uncopyable& operator=(const Uncopyable&);   // declared, not defined
};

} // namespace bank

#endif // BANK_UNCOPYABLE_HPP
