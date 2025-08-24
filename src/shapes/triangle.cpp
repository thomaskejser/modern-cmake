#include "include/demo/shapes/triangle.h"
#include <cmath>
namespace demo::shapes {

double Triangle::area() const{
  return 0.5 * std::abs(
      corner1.x * (corner2.y - corner3.y) +
      corner2.x * (corner3.y - corner1.y) +
      corner3.x * (corner1.y - corner2.y)
  );
}
}
