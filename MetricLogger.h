#pragma once
#include "MetricManager.h"
#include <fstream>
#include <atomic>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

class MetricLogger {
  std::ofstream file_;
  std::atomic<bool> stop_flag_;
  std::thread worker_;
  MetricManager& manager_;
  int interval_ms_;

public:
  MetricLogger(const std::string& filename, MetricManager& mgr, int interval = 1000);
  ~MetricLogger();

private:
  void Run();
};
