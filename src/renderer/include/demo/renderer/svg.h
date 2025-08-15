#pragma once
#include <vector>


namespace demo::shapes {
  class Shape;
}

namespace demo::renderer {
  void to_svg(std::vector<demo::shapes::Shape*>& shapes);
}