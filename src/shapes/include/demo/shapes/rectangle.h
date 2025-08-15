#pragma once
#include "point.h"
namespace demo::shapes {

class Rectangle {
public:
  explicit Rectangle(const Point corner1, const Point corner2): corner1(corner1), corner2(corner2) {};
  const Point corner1;
  const Point corner2;
  double area() const;
  double perimeter() const;
};

}

