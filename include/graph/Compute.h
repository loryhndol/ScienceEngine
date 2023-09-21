#ifndef GRAPH_COMPUTE_H
#define GRAPH_COMPUTE_H

#include <sstream>
#include <string>
#include <vector>

#include "Value.h"

using Shape = std::vector<int>;

// Node for computation
class Compute {
 private:
  // placeholders
  std::string _name;
  Shape _shape;
  Operators _op;

  // dependencies
  Compute* _left;
  Compute* _right;

  // value
  Value* _val;

 public:
  // constructor
  Compute(std::string name, Shape shape);

  // getters
  std::string getName();
  Operators getOp() const;
  Compute* getLeft();
  Compute* getRight();
  Value* getVal();

  // setters
  void setOp(Operators op);
  void setVal(Value* val);

  friend Compute operator+(Compute& lhs, Compute& rhs);

  // print the tree
  static void print(Compute* node, std::string& message);

  // print the node
  std::string toString();
};

#endif