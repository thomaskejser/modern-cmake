#include "include/demo/shapes/circle.h"
#include <numbers>

namespace demo::shapes {

double Circle::area() const {
  return std::numbers::pi * radius * radius;
}

double Circle::circumference() const{
  return 2 * std::numbers::pi * radius;
}

}