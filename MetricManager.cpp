#include "MetricManager.h"

void MetricManager::RegisterMetric(const std::shared_ptr<IMetric>& metric) {
  std::lock_guard lock(mtx_);
  metrics_.push_back(metric);
}

std::vector<std::shared_ptr<IMetric>> MetricManager::GetMetricsSnapshot() {
  std::lock_guard lock(mtx_);
  return metrics_;
}
