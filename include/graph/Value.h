#ifndef GRAPH_VALUE_H
#define GRAPH_VALUE_H

#include <unordered_map>
#include <vector>

enum class Operators { Plus, Minus, Multiply, Divide, Value };

enum class Precision { FP32, FP64, FP16 };

// In order to evaluate the graph at runtime, we need to provide polymorphism
// (Maybe precision mixing in the future?)
class Value {
 public:
  virtual Precision precision() = 0;
  virtual size_t size() const = 0;
};

using ValuesDict = std::unordered_map<std::string, Value*>;

class Double : public Value {
 private:
  std::vector<double> _vals;
  Precision _precision;  // precision at runtime

 public:
  Double(std::vector<double> vals);

  // getters
  Precision precision() override;
  double operator[](size_t i) const;
  size_t size() const override;
};

#endif  // GRAPH_VALUE_H