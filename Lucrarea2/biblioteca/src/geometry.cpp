#include <geometry/geometry.h>

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace geometry {

namespace {
const double PI = 3.14159265358979323846;
}

const char* version()
{
    return "geometry 1.0 (static library)";
}

double distance(const Point& a, const Point& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// ------------------------------------------------------------------ Rectangle
Rectangle::Rectangle(double width, double height)
    : width_(width), height_(height)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("rectangle sides must be positive");
}

double Rectangle::area() const { return width_ * height_; }

double Rectangle::perimeter() const { return 2 * (width_ + height_); }

std::string Rectangle::describe() const
{
    std::ostringstream out;
    out << "Rectangle " << width_ << " x " << height_;
    return out.str();
}

// --------------------------------------------------------------------- Circle
Circle::Circle(const Point& center, double radius)
    : center_(center), radius_(radius)
{
    if (radius <= 0)
        throw std::invalid_argument("circle radius must be positive");
}

double Circle::area() const { return PI * radius_ * radius_; }

double Circle::perimeter() const { return 2 * PI * radius_; }

bool Circle::contains(const Point& p) const
{
    return distance(center_, p) <= radius_;
}

std::string Circle::describe() const
{
    std::ostringstream out;
    out << "Circle center (" << center_.x << ", " << center_.y << "), r = " << radius_;
    return out.str();
}

} // namespace geometry
