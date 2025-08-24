#pragma once
#include "point.h"
namespace demo::shapes {

class Triangle {
public:
  Triangle(const Point corner1, Point corner2, Point corner3);
  const Point corner1;
  const Point corner2;
  const Point corner3;
  double area() const;
};
}