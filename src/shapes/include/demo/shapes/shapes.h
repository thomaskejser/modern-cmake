#pragma once
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "point.h"
#include <variant>

namespace demo::shapes {
using Shape = std::variant<Circle, Rectangle, Triangle>;
}