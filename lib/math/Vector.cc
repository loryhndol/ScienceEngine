#include "math/Vector.h"

Compute Vector(std::string vector_name, Shape shape) {
  return Compute(vector_name, shape);
}

Compute Vec3d(std::string vector_name) {
  return Compute(vector_name, Shape(3));
}