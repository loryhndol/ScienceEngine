#include <arch/Backend.h>

void CPU::evaluate(Compute& node, ValuesDict& data) {
  if (node.getName() != "scalar") {
    // load data
    auto node_val = data[node.getName()];
    node.setVal(node_val, node_val->precision());
  }

  std::list<Compute>& dependencies = node.getDependencies();

  for (auto& dependency : dependencies) {
    if (dependency.getName() != "scalar") {
      auto dependency_val = data[dependency.getName()];
      dependency.setVal(dependency_val, dependency_val->precision());
    }
  }

  for (auto& dependency : dependencies) {
    // Evaluate
    Value* result = nullptr;
    switch (dependency.getOp()) {
      case Operators::Plus:
        result = plus(node, dependency);
        break;

      case Operators::Minus:
        break;
      case Operators::Multiply:
        break;
      case Operators::Divide:
        break;

      default:
        break;
    }
    node.setVal(result, result->precision());
  }
}

Value* CPU::plus(Compute& left, Compute& right) {
  auto left_vals = *dynamic_cast<Double*>(left.getVal());
  auto right_vals = *dynamic_cast<Double*>(right.getVal());
  Precision prec_tmp = left_vals.precision();
  prec_tmp = right_vals.precision();

  samePrecision(left.getVal(), right.getVal());

  Precision prec = left.getVal()->precision();

  Value* ret = nullptr;

  switch (prec) {
    case Precision::FP64: {
      std::vector<double> result;
      Double left_vals = *dynamic_cast<Double*>(left.getVal());
      Double right_vals = *dynamic_cast<Double*>(right.getVal());

      if (left_vals.size() == right_vals.size()) {
        for (size_t i = 0; i < left_vals.size(); i++) {
          result.push_back(left_vals[i] + right_vals[i]);
        }
      }
      if (left_vals.size() == 1 && right_vals.size() != 1) {
        for (size_t i = 0; i < right_vals.size(); i++) {
          result.push_back(left_vals[0] + right_vals[i]);
        }
      }
      if (right_vals.size() == 1 && left_vals.size() != 1) {
        for (size_t i = 0; i < left_vals.size(); i++) {
          result.push_back(left_vals[i] + right_vals[0]);
        }
      }

      ret = new Double(result);
      break;
    }

    default:
      break;
  }

  return ret;
}

Value* CPU::minus(Compute& left, Compute& right) {
  samePrecision(left.getVal(), right.getVal());

  Precision prec = left.getVal()->precision();

  Value* ret = nullptr;

  switch (prec) {
    case Precision::FP64: {
      std::vector<double> result;
      Double left_vals = *dynamic_cast<Double*>(left.getVal());
      Double right_vals = *dynamic_cast<Double*>(right.getVal());

      for (size_t i = 0; i < left_vals.size(); i++) {
        result.push_back(left_vals[i] - right_vals[i]);
      }
      ret = new Double(result);
      break;
    }

    default:
      break;
  }

  return ret;
}

Value* CPU::multiply(Compute& left, Compute& right) {
  throw std::runtime_error("Not implemented");
}

Value* CPU::divide(Compute& left, Compute& right) {
  throw std::runtime_error("Not implemented");
}

void samePrecision(Value* left, Value* right) {
  if (left->precision() != right->precision()) {
    throw std::runtime_error("Precision mismatch");
  }
}

void sameShape(Compute& left, Compute& right) {
  if (left.getShape() != right.getShape()) {
    throw std::runtime_error("Shape mismatch");
  }
}