#ifndef GRADEBOOK_STUDENT_HPP
#define GRADEBOOK_STUDENT_HPP

#include <cstddef>
#include <string>

namespace gradebook {

// A student owns a dynamic array of grades allocated on the heap.
// Because of that, it must manage the memory itself (Rule of Three / Five).
class Student {
public:
    Student(const std::string& name, int id, std::size_t capacity = 2);
    ~Student();

    Student(const Student& other);           // deep copy
    Student(Student&& other) noexcept;       // move (steals the array)

    // Assignment operators are covered in a later lab. They are deleted so the
    // compiler cannot generate a shallow assignment that would break ownership.
    Student& operator=(const Student&) = delete;
    Student& operator=(Student&&) = delete;

    // Public interface: the only way to touch the private data
    void addGrade(int grade);
    bool setGrade(std::size_t index, int grade);
    int grade(std::size_t index) const;
    double average() const;

    const std::string& name() const { return name_; }
    int id() const { return id_; }
    std::size_t count() const { return count_; }
    bool empty() const { return grades_ == nullptr; }

    void print() const;

private:
    void grow();
    static bool isValid(int grade) { return grade >= 1 && grade <= 10; }

    // Declaration order = initialization order in the constructor
    const std::string name_;   // const: can ONLY be set in the initializer list
    const int id_;             // const: can ONLY be set in the initializer list
    std::size_t capacity_;
    std::size_t count_;
    int* grades_;              // owned heap array
};

#ifdef DEMO_SHALLOW_COPY
// Same idea, but WITHOUT a user-defined copy constructor.
// The compiler-generated copy copies the pointer, not the array.
class ShallowStudent {
public:
    explicit ShallowStudent(int firstGrade);
    ~ShallowStudent();
    void setFirst(int grade) { grades_[0] = grade; }
    int first() const { return grades_[0]; }
private:
    int* grades_;
};
#endif

} // namespace gradebook

#endif // GRADEBOOK_STUDENT_HPP
