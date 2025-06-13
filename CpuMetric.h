#pragma once
#include "IMetric.h"
#include <atomic>
#include <string>

class CpuMetric : public IMetric {
  std::atomic<double> value_;

public:
  CpuMetric();
  void Set(double v);
  std::string GetName() const override;
  std::string GetValueAsString() const override;
  void Reset() override;
};
