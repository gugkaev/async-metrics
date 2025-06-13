#include "CpuMetric.h"

CpuMetric::CpuMetric() : value_(0.0) {}

void CpuMetric::Set(double v) {
  value_.store(v);
}

std::string CpuMetric::GetName() const {
  return "CPU";
}

std::string CpuMetric::GetValueAsString() const {
  return std::to_string(value_.load());
}

void CpuMetric::Reset() {
  value_.store(0.0);
}
