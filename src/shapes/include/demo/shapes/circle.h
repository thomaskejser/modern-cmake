#pragma once
#include "point.h"

namespace demo::shapes {
class Circle {
public:
  explicit Circle(const double radius, const Point center): radius(radius),center(center) {};
  const double radius;
  const Point center;
  [[nodiscard]] double area() const;
  [[nodiscard]] double circumference() const;
};

}