# Lucrare 3 – Gradebook

Aplicație C++ (individual, proof of life) care ilustrează:

| # | Concept | Unde |
|---|---------|------|
| 1 | Build cu CMake (structura din laborator) | `CMakeLists.txt`, `src/`, `inc/gradebook/` |
| 2 | Încapsulare | `Student`: date `private`, acces doar prin metode cu validare |
| 3 | Inițializarea membrilor în constructor | lista de inițializare; `name_` și `id_` sunt `const` |
| 4 | Eliberarea heap-ului în destructor | `~Student()` face `delete[] grades_` |
| 5 | Copy constructor (deep copy) | `Student(const Student&)` |
| 6 | Move constructor | `Student(Student&&) noexcept` |

Fiecare constructor/destructor afișează un mesaj și adresa array-ului de pe heap.

## Build și rulare

```bash
cmake -S . -B build
cmake --build build
./build/gradebook
```

## Demo: ce se întâmplă fără copy constructor

```bash
cmake -S . -B build-shallow -DDEMO_SHALLOW_COPY=ON
cmake --build build-shallow
./build-shallow/gradebook
```

`ShallowStudent` folosește copy constructor-ul generat de compilator: cele două obiecte
partajează același array, iar la final ambii destructori fac `delete[]` pe aceeași adresă.
AddressSanitizer raportează `double-free`.
