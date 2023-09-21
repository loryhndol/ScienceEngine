#ifndef ARCH_BACKEND_H
#define ARCH_BACKEND_H

#include "../graph/Compute.h"

class Backend {
 public:
  Backend() = default;
  virtual ~Backend() = default;

  virtual void evaluate(Compute& node, ValuesDict& data) = 0;
};

class CPU : public Backend {
 public:
  void evaluate(Compute& node, ValuesDict& data) override;
};

#endif  // ARCH_BACKEND_H