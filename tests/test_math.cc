#include <iostream>
#include <math/Vector.hpp>

int main() {
  try {
    Vec3d a{1.0, 2.0, 3.0, 4.0};
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}