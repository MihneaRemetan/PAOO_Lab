#include <geometry/geometry.h>   // header exported by the first project

#include <iostream>

int main()
{
    std::cout << "Application shapes_app\n"
              << "Using " << geometry::version() << "\n\n";

    geometry::Rectangle room(4.0, 3.5);
    std::cout << room.describe() << "\n"
              << "  area      = " << room.area() << "\n"
              << "  perimeter = " << room.perimeter() << "\n\n";

    geometry::Circle pool({0.0, 0.0}, 3.0);
    std::cout << pool.describe() << "\n"
              << "  area      = " << pool.area() << "\n"
              << "  perimeter = " << pool.perimeter() << "\n";

    geometry::Point inside{1.0, 1.0};
    geometry::Point outside{4.0, 1.0};
    std::cout << "  contains (1, 1)? " << (pool.contains(inside) ? "yes" : "no") << "\n"
              << "  contains (4, 1)? " << (pool.contains(outside) ? "yes" : "no") << "\n\n";

    std::cout << "Distance (1, 1) -> (4, 1) = "
              << geometry::distance(inside, outside) << "\n";

    return 0;
}
