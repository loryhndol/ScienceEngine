#include "graph/Compute.h"

Compute::Compute(std::string name, Shape shape)
    : _op(Operators::Value),
      _val(nullptr),
      _name(name),
      _shape(shape),
      _left(nullptr),
      _right(nullptr) {}

Operators Compute::getOp() const { return _op; }

void Compute::setOp(Operators op) { this->_op = op; }

std::string Compute::getName() { return _name; }

Compute operator+(Compute& lhs, Compute& rhs) {
  Compute node("+", lhs._shape);
  node._left = &lhs;
  node._right = &rhs;
  node._op = Operators::Plus;
  return node;
}

Compute* Compute::getLeft() { return _left; }

Compute* Compute::getRight() { return _right; }

void Compute::setVal(Value* val) { _val = val; }

Value* Compute::getVal() { return _val; }

std::string Compute::toString() {
  std::string str = "";
  if (_val != nullptr) {
    Precision precision = _val->precision();

    std::stringstream ss;

    switch (precision) {
      case Precision::FP64: {
        str += "FP64: ";
        Double data = *dynamic_cast<Double*>(_val);

        for (size_t i = 0; i < _val->size(); i++) {
          ss << data[i] << " ";
        }
        break;
      }

      default:
        break;
    }

    std::string dataStr = ss.str();
    str += dataStr;
  }
  return str;
}

void Compute::print(Compute* node, std::string& message) {
  if (node == nullptr) {
    return;
  }

  // is leaf
  if (node->_left == nullptr && node->_right == nullptr) {
    message += "\"shape\": ";
    std::stringstream ss;
    for (int i = 0; i < node->_shape.size(); i++) {
      ss << node->_shape[i];
      if (i != node->_shape.size() - 1) {
        ss << ",";
      }
    }
    std::string shapeStr = ss.str();
    message += "\"" + shapeStr + "\"";
    return;
  }

  message += "\"" + node->_name + "\"" + ":{";
  if (node->_left != nullptr) {
    message += "\"left\":{";
    print(node->_left, message);
    message += "},";
  }
  if (node->_right != nullptr) {
    message += "\"right\":{";
    print(node->_right, message);
    message += "}";
  }
  message += "}";
}
