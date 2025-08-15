#pragma once

namespace demo::shapes {
class Point {
public:
  explicit Point(const double x, const double y): x(x), y(y) {};
  const double x;
  const double y;
};

}