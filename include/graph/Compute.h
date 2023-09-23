#ifndef GRAPH_COMPUTE_H
#define GRAPH_COMPUTE_H

#include <list>
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

  std::list<Compute> _dependencies;

  // value
  Value* _val;

 public:
  // constructor
  Compute(std::string name, Shape shape);

  // destructor
  ~Compute();

  // getters
  std::string getName();
  Operators getOp() const;
  std::list<Compute>& getDependencies();
  Value* getVal();
  Shape getShape();

  // setters
  void setOp(Operators op);
  void setVal(Value* val, Precision prec);

  friend Compute& operator+(Compute& lhs, Compute& rhs);
  friend Compute& operator+(Compute& lhs, double rhs);

  // print the tree
  static void print(Compute* node, std::string& message);

  // print the node
  std::string toString();
};

void deleteGraph(Compute& node);

#endif