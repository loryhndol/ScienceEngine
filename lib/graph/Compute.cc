#include "graph/Compute.h"

Compute::Compute(std::string name, Shape shape)
    : _op(Operators::Value), _val(nullptr), _name(name), _shape(shape) {}

Compute::~Compute() {}

Operators Compute::getOp() const { return _op; }

void Compute::setOp(Operators op) { this->_op = op; }

std::string Compute::getName() { return _name; }

std::list<Compute>& Compute::getDependencies() { return _dependencies; }

Compute& operator+(Compute& lhs, Compute& rhs) {
  rhs.setOp(Operators::Plus);
  lhs._dependencies.push_back(rhs);
  return lhs;
}

Compute& operator+(Compute& lhs, double rhs) {
  Compute scalar("scalar", {1});
  scalar.setVal(new Double({rhs}), Precision::FP64);
  scalar.setOp(Operators::Plus);
  lhs._dependencies.push_back(scalar);
  return lhs;
}

void Compute::setVal(Value* val, Precision prec) {
  if (_val == nullptr) {
    switch (prec) {
      case Precision::FP64: {
        Double d = *dynamic_cast<Double*>(val);
        _val = new Double(d);
        break;
      }

      default:
        break;
    }
    return;
  } else {
    _val = val;
  }
}

Value* Compute::getVal() { return _val; }

Shape Compute::getShape() { return _shape; }

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
  if (node->getOp() == Operators::Value) {
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
  std::list<Compute> dependencies = node->getDependencies();

  if (dependencies.size() > 0) {
    message += "\"dependencies\":[";
    for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
      message += "\"" + (*it)._name + "\",";
    }
  }

  message += "}";
}

void deleteGraph(Compute& node) {
  for (auto it = node.getDependencies().begin();
       it != node.getDependencies().end(); it++) {
    deleteGraph(*it);
  }
  delete node.getVal();
}