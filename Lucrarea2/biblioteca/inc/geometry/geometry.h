#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H

#include <string>

// Public interface of the static library libgeometry.a.
// This is the only file a user of the library needs to include.
namespace geometry {

const char* version();

struct Point {
    double x;
    double y;
};

double distance(const Point& a, const Point& b);

class Rectangle {
public:
    Rectangle(double width, double height);
    double area() const;
    double perimeter() const;
    std::string describe() const;
private:
    double width_;
    double height_;
};

class Circle {
public:
    Circle(const Point& center, double radius);
    double area() const;
    double perimeter() const;
    bool contains(const Point& p) const;
    std::string describe() const;
private:
    Point center_;
    double radius_;
};

} // namespace geometry

#endif // GEOMETRY_GEOMETRY_H
