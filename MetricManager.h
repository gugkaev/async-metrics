#pragma once
#include "IMetric.h"
#include <vector>
#include <memory>
#include <mutex>

class MetricManager {
  std::vector<std::shared_ptr<IMetric>> metrics_;
  std::mutex mtx_;

public:
  void RegisterMetric(const std::shared_ptr<IMetric>& metric);
  std::vector<std::shared_ptr<IMetric>> GetMetricsSnapshot();
};
