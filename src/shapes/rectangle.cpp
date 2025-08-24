#include "include/demo/shapes/rectangle.h"

#include <cmath>

namespace demo::shapes {
double Rectangle::area() const {
  return std::abs(corner1.x - corner2.x) * std::abs(corner1.y - corner2.y);
}
double Rectangle::perimeter() const {
  return 2 * (std::abs(corner1.x - corner2.x) + std::abs(corner1.y - corner2.y));
}
}  // namespace demo::shapes