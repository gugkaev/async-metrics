#pragma once
#include <string>

class IMetric {
public:
  virtual ~IMetric() = default;
  virtual std::string GetName() const = 0;
  virtual std::string GetValueAsString() const = 0;
  virtual void Reset() = 0;
};
