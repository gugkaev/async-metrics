#include "MetricLogger.h"
#include <iostream>

MetricLogger::MetricLogger(const std::string& filename, MetricManager& mgr, int interval)
    : file_(filename), stop_flag_(false), manager_(mgr), interval_ms_(interval) {
  worker_ = std::thread([this]() { this->Run(); });
}

MetricLogger::~MetricLogger() {
  stop_flag_.store(true);
  if (worker_.joinable()) {
    worker_.join();
  }
}

void MetricLogger::Run() {
  while (!stop_flag_.load()) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) % 1000;

    std::ostringstream timestamp;
    timestamp << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "."
              << std::setfill('0') << std::setw(3) << ms.count();

    std::ostringstream line;
    line << timestamp.str();

    auto metrics = manager_.GetMetricsSnapshot();
    for (auto& metric : metrics) {
      line << " \"" << metric->GetName() << "\" " << metric->GetValueAsString();
    }

    file_ << line.str() << std::endl;

    for (auto& metric : metrics) {
      metric->Reset();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms_));
  }
}
