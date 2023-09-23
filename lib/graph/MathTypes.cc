#include "graph/MathTypes.h"

Compute Vector(std::string vector_name, int dims) {
  Shape shape{dims};
  return Compute(vector_name, shape);
}

Compute Matrix(std::string matrix_name, Shape shape) {
  return Compute(matrix_name, shape);
}
