#include "graph/Value.h"

Double::Double(std::vector<double> vals)
    : _vals(vals), _precision(Precision::FP64) {}

Precision Double::precision() { return _precision; }

size_t Double::size() const { return _vals.size(); }

double Double::operator[](size_t i) const { return _vals[i]; }