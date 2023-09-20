#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

template <int Rows, int Cols, typename Prec>
class Matrix {
 private:
  Prec data[Rows * Cols];

 public:
  Matrix() {
    for (int i = 0; i < Rows * Cols; i++) {
      data[i] = static_cast<Prec>(0.0);
    }
  }

  Matrix(std::initializer_list<std::initializer_list<Prec>> l) {
    if (l.size() > Rows) {
      throw std::runtime_error("Matrix initialized with too many rows");
    }
    for (int i = 0; i < l.size(); i++) {
      if (l.begin()[i].size() > Cols) {
        throw std::runtime_error("Matrix initialized with too many columns");
      }
    }

    for (int i = 0; i < l.size(); i++) {
      for (int j = 0; j < l.begin()[i].size(); j++) {
        data[i * Cols + j] = l.begin()[i].begin()[j];
      }
    }

    if (l.size() < Rows) {
      for (int i = l.size(); i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
          data[i * Cols + j] = static_cast<Prec>(0.0);
        }
      }
    }
  }

  Prec& operator()(int i, int j) {
    if (i < 0 || i >= Rows || j < 0 || j >= Cols) {
      throw std::runtime_error("Matrix index out of bounds");
    }
    return data[i * Cols + j];
  }

  Prec operator()(int i, int j) const {
    if (i < 0 || i >= Rows || j < 0 || j >= Cols) {
      throw std::runtime_error("Matrix index out of bounds");
    }
    return data[i * Cols + j];
  }
};

using Mat3x3f = Matrix<3, 3, float>;
using Mat4x4f = Matrix<4, 4, float>;

using Mat3x3d = Matrix<3, 3, double>;
using Mat4x4d = Matrix<4, 4, double>;

#endif  // MATH_MATRIX_H