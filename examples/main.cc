#include <iostream>
#include <math/Vector.hpp>

int main() {
  Vector<3, double> a;
  for (int i = 0; i < 3; i++) {
    std::cout << a[i] << std::endl;
  }
}