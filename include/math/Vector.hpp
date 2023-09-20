#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <initializer_list>
#include <stdexcept>

template <int Dims, typename Prec>
class Vector {
 private:
  Prec data[Dims];

 public:
  Vector() {
    for (int i = 0; i < Dims; i++) {
      data[i] = static_cast<Prec>(0.0);
    }
  }

  Vector(std::initializer_list<Prec> l) {
    if (l.size() > Dims) {
      throw std::runtime_error("Vector initialized with too many elements");
    }

    for (auto it = l.begin(); it != l.end(); it++) {
      data[it - l.begin()] = *it;
    }

    if (l.size() < Dims) {
      for (int i = l.size(); i < Dims; i++) {
        data[i] = static_cast<Prec>(0.0);
      }
    }
  }

  Prec& operator[](int i) {
    if (i < 0 || i >= Dims) {
      throw std::runtime_error("Vector index out of bounds");
    }
    return data[i];
  }
};

using Vec3d = Vector<3, double>;

#endif  // MATH_VECTOR_H