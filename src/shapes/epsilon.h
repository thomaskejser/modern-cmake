#pragma once
#include <algorithm>
#include <cmath>


namespace demo::shapes {
inline constexpr double EPS = 1e-9;
inline bool nearly_equal(const double a, const double b, const double eps = EPS) {
  return std::abs(a - b) <= eps * std::max(1.0, std::max(std::abs(a), std::abs(b)));
}

}