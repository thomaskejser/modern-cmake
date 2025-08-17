#pragma once
#include <demo/shapes/shapes.h>
#include <vector>

namespace demo::renderer {
  void to_svg(std::vector<shapes::Shape*>& shapes);
}