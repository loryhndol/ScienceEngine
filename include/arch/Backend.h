#ifndef ARCH_BACKEND_H
#define ARCH_BACKEND_H

#include "../graph/Compute.h"

class Backend {
 public:
  Backend() = default;
  virtual ~Backend() = default;

  virtual void evaluate(Compute& node, ValuesDict& data) = 0;
  virtual Value* plus(Compute& left, Compute& right) = 0;
  virtual Value* minus(Compute& left, Compute& right) = 0;
  virtual Value* multiply(Compute& left, Compute& right) = 0;
  virtual Value* divide(Compute& left, Compute& right) = 0;
};

class CPU : public Backend {
 public:
  void evaluate(Compute& node, ValuesDict& data) override;
  Value* plus(Compute& left, Compute& right) override;
  Value* minus(Compute& left, Compute& right) override;
  Value* multiply(Compute& left, Compute& right) override;
  Value* divide(Compute& left, Compute& right) override;
};

void sameShape(Compute& left, Compute& right);
void samePrecision(Value* left, Value* right);

#endif  // ARCH_BACKEND_H