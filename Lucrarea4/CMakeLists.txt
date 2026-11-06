cmake_minimum_required(VERSION 3.10)
project(bank)

include_directories(inc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# NOTE (Item 4): fees.cpp is listed BEFORE exchange_rates.cpp on purpose.
# The order in which non-local static objects from different translation units
# are initialized is unspecified; with GCC/Clang it usually follows the link
# order, so this order makes the "static initialization order fiasco" visible.
add_executable(${PROJECT_NAME}
    inc/bank/bank_config.hpp
    inc/bank/tracer.hpp
    inc/bank/customer.hpp
    inc/bank/loan.hpp
    inc/bank/exchange_rates.hpp
    inc/bank/fees.hpp
    inc/bank/generated.hpp
    inc/bank/uncopyable.hpp
    inc/bank/account.hpp
    src/main.cpp
    src/tracer.cpp
    src/customer.cpp
    src/loan.cpp
    src/fees.cpp
    src/exchange_rates.cpp
    src/account.cpp
)
