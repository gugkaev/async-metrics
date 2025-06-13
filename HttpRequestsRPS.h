#pragma once
#include "IMetric.h"
#include <atomic>
#include <string>

class HttpRequestsRPS : public IMetric {
  std::atomic<int> count_;

public:
  HttpRequestsRPS();
  void Increment(int v = 1);
  std::string GetName() const override;
  std::string GetValueAsString() const override;
  void Reset() override;
};
