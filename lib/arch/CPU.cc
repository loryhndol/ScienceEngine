#include <arch/Backend.h>

void CPU::evaluate(Compute& node, ValuesDict& data) {
  Compute* left = node.getLeft();
  Compute* right = node.getRight();

  // is leaf
  if (left == nullptr && right == nullptr) {
    // Assign value
    node.setVal(data[node.getName()]);
    return;
  }

  if (left != nullptr) {
    evaluate(*left, data);
  }

  if (right != nullptr) {
    evaluate(*right, data);
  }

  // Evaluate
  if (node.getOp() == Operators::Plus) {
    Precision left_prec = left->getVal()->precision();
    Precision right_prec = right->getVal()->precision();

    if (left_prec != right_prec) {
      throw std::runtime_error("Precision mismatch");
    }

    switch (left_prec) {
      case Precision::FP64: {
        std::vector<double> result;
        Double left_vals = *dynamic_cast<Double*>(left->getVal());
        Double right_vals = *dynamic_cast<Double*>(right->getVal());

        for (size_t i = 0; i < left_vals.size(); i++) {
          result.push_back(left_vals[i] + right_vals[i]);
        }

        node.setVal(new Double(result));
        break;
      }

      default:
        break;
    }
  }
}
