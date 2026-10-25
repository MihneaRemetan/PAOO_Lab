#include <gradebook/gradebook_config.hpp>
#include <gradebook/student.hpp>

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using gradebook::Student;

static void section(const char* title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// 2. Encapsulation: data is private, only reachable through validated methods.
static void encapsulationDemo()
{
    section("2. Encapsulation");
    Student s("Ana", 101);
    s.addGrade(9);
    s.addGrade(10);

    // s.grades_[0] = 42;   // does not compile: grades_ is private
    // s.count_ = 100;      // does not compile: count_ is private

    try {
        s.addGrade(42);    // rejected by the public interface
    } catch (const std::exception& e) {
        std::cout << "  addGrade(42) rejected: " << e.what() << "\n";
    }
    std::cout << "  setGrade(5, 7) on 2 grades -> "
              << (s.setGrade(5, 7) ? "ok" : "rejected (index out of range)") << "\n";
    s.print();
}

// 3. Member initialization in the constructor
static void initializationDemo()
{
    section("3. Member initializer list");
    // name_ and id_ are const members: they exist from the very start of the
    // object's life and can only receive their value in the initializer list.
    // grades_ is allocated using capacity_, which works only because capacity_
    // is declared (and therefore initialized) before grades_.
    Student s("Bogdan", 102, 3);
    s.addGrade(8);
    s.print();
}

// 4. Destructor releases the heap
static void destructorDemo()
{
    section("4. Destructor");
    std::cout << "  Entering block\n";
    {
        Student s("Cristi", 103);
        s.addGrade(7);
        s.addGrade(6);
        s.addGrade(9);   // array grows: old one is freed inside grow()
        s.print();
        std::cout << "  Leaving block -> destructor runs automatically\n";
    }

    std::cout << "  Object created with new:\n";
    Student* p = new Student("Dana", 104);
    p->addGrade(10);
    delete p;        // calls ~Student(), which frees the grades array
    p = nullptr;     // optional: p would otherwise be dangling
    // Without delete[] in ~Student(), every Student would leak its array.
}

// 5. Copy constructor (deep copy)
static void copyDemo()
{
    section("5. Copy constructor (deep copy)");
    Student original("Elena", 105);
    original.addGrade(5);
    original.addGrade(6);

    Student copy = original;          // copy constructor
    copy.setGrade(0, 10);             // change only the copy

    std::cout << "  After changing the copy's first grade to 10:\n";
    original.print();
    copy.print();
    std::cout << "  -> original is unchanged: the two objects own different arrays.\n"
              << "     With the compiler-generated (shallow) copy, both would point to the\n"
              << "     SAME array: the change would show up in both, and at the end both\n"
              << "     destructors would delete[] it (double delete, undefined behavior).\n"
              << "     Build with -DDEMO_SHALLOW_COPY=ON to see it.\n";

    std::cout << "  Leaving scope -> each destructor frees its own array:\n";
}

// 6. Move constructor
static Student makeTopStudent()
{
    Student s("Florin", 106);
    s.addGrade(10);
    s.addGrade(10);
    return s;
}

static void moveDemo()
{
    section("6. Move constructor");
    Student source("George", 107);
    source.addGrade(8);
    source.addGrade(9);

    Student destination = std::move(source);   // move constructor, no new array
    std::cout << "  After std::move:\n";
    source.print();
    destination.print();

    std::cout << "\n  std::vector growth: elements are moved, not copied,\n"
              << "  because the move constructor is noexcept:\n";
    std::vector<Student> group;
    group.reserve(1);
    group.push_back(makeTopStudent());   // temporary -> moved into the vector
    std::cout << "  -- push_back #2 (vector must grow and relocate element #1) --\n";
    group.push_back(Student("Ioana", 108));
    for (const Student& s : group) s.print();

    std::cout << "  Leaving scope:\n";
}

#ifdef DEMO_SHALLOW_COPY
static void shallowCopyDemo()
{
    section("Shallow copy (what goes wrong without a copy constructor)");
    gradebook::ShallowStudent a(5);
    gradebook::ShallowStudent b = a;   // compiler-generated copy: copies the pointer
    b.setFirst(10);
    std::cout << "  Changed only b, but a.first() = " << a.first()
              << " -> they share one array\n";
    std::cout << "  Leaving scope: both destructors delete[] the same address...\n";
}
#endif

int main()
{
    std::cout << "Application " << APP_NAME << "\n"
              << "Version " << APP_VERSION << "\n"
              << APP_LAB << "\n";

    encapsulationDemo();
    initializationDemo();
    destructorDemo();
    copyDemo();
    moveDemo();

#ifdef DEMO_SHALLOW_COPY
    shallowCopyDemo();
#endif

    std::cout << "\nGood bye!\n";
    return 0;
}
