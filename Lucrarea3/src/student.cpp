#include <gradebook/student.hpp>

#include <iostream>
#include <stdexcept>

namespace gradebook {

// ---------------------------------------------------------------- constructor
// All members are initialized in the member initializer list, BEFORE the body.
// name_ and id_ are const, so assigning them in the body would not compile:
//     name_ = name;   // error: assignment of read-only member
Student::Student(const std::string& name, int id, std::size_t capacity)
    : name_(name),
      id_(id),
      capacity_(capacity == 0 ? 1 : capacity),
      count_(0),
      grades_(new int[capacity_])   // capacity_ is already set (declared before grades_)
{
    std::cout << "  [ctor]  Student \"" << name_ << "\" (id " << id_
              << "), heap array of " << capacity_ << " at " << grades_ << "\n";
}

// ----------------------------------------------------------------- destructor
// Releases the heap array. new[] is paired with delete[].
// After a move, grades_ is nullptr and delete[] nullptr does nothing.
Student::~Student()
{
    std::cout << "  [dtor]  Student \"" << name_ << "\" frees "
              << (grades_ ? "array at " : "nothing (moved-from)");
    if (grades_) std::cout << grades_;
    std::cout << "\n";
    delete[] grades_;
}

// ----------------------------------------------------------- copy constructor
// Deep copy: allocate a NEW array and copy the values, not the address.
Student::Student(const Student& other)
    : name_(other.name_ + " (copy)"),
      id_(other.id_),
      capacity_(other.capacity_),
      count_(other.count_),
      grades_(other.grades_ ? new int[other.capacity_] : nullptr)
{
    for (std::size_t i = 0; i < count_; ++i)
        grades_[i] = other.grades_[i];

    std::cout << "  [copy]  \"" << name_ << "\" gets its own array at " << grades_
              << " (source array stays at " << other.grades_ << ")\n";
}

// ----------------------------------------------------------- move constructor
// Takes over the array: no new allocation, no copying of elements.
// The source is left valid but empty (nullptr), so its destructor frees nothing.
Student::Student(Student&& other) noexcept
    : name_(other.name_),   // name_ is const, so it can only be copied, not moved
      id_(other.id_),
      capacity_(other.capacity_),
      count_(other.count_),
      grades_(other.grades_)
{
    other.grades_ = nullptr;
    other.count_ = 0;
    other.capacity_ = 0;

    std::cout << "  [move]  \"" << name_ << "\" takes array at " << grades_
              << " (source now holds nullptr)\n";
}

// ------------------------------------------------------------ public methods
void Student::addGrade(int grade)
{
    if (!isValid(grade))
        throw std::invalid_argument("grade must be between 1 and 10");
    if (grades_ == nullptr)
        throw std::logic_error("cannot add grades to a moved-from Student");
    if (count_ == capacity_)
        grow();
    grades_[count_++] = grade;
}

bool Student::setGrade(std::size_t index, int grade)
{
    if (index >= count_ || !isValid(grade))
        return false;
    grades_[index] = grade;
    return true;
}

int Student::grade(std::size_t index) const
{
    if (index >= count_)
        throw std::out_of_range("grade index out of range");
    return grades_[index];
}

double Student::average() const
{
    if (count_ == 0) return 0.0;
    int sum = 0;
    for (std::size_t i = 0; i < count_; ++i) sum += grades_[i];
    return static_cast<double>(sum) / count_;
}

void Student::print() const
{
    std::cout << "  " << name_ << " (id " << id_ << "): ";
    if (grades_ == nullptr) {
        std::cout << "<empty, moved-from>\n";
        return;
    }
    std::cout << "[";
    for (std::size_t i = 0; i < count_; ++i)
        std::cout << grades_[i] << (i + 1 < count_ ? ", " : "");
    std::cout << "]  avg = " << average() << "\n";
}

// ----------------------------------------------------------- private helper
// Doubles the capacity: allocate new, copy, release old.
void Student::grow()
{
    std::size_t newCapacity = capacity_ * 2;
    int* bigger = new int[newCapacity];
    for (std::size_t i = 0; i < count_; ++i) bigger[i] = grades_[i];
    delete[] grades_;
    grades_ = bigger;
    capacity_ = newCapacity;
}

#ifdef DEMO_SHALLOW_COPY
ShallowStudent::ShallowStudent(int firstGrade) : grades_(new int[1])
{
    grades_[0] = firstGrade;
    std::cout << "  [ctor]  ShallowStudent, array at " << grades_ << "\n";
}

ShallowStudent::~ShallowStudent()
{
    std::cout << "  [dtor]  ShallowStudent frees array at " << grades_ << "\n";
    delete[] grades_;
}
#endif

} // namespace gradebook
