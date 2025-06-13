#include "CpuMetric.h"
#include "HttpRequestsRPS.h"
#include "MetricManager.h"
#include "MetricLogger.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>

void RunTests() {
  std::cout << "[TEST] Starting tests...\n";

  CpuMetric cpu;
  cpu.Set(1.5);
  assert(cpu.GetName() == "CPU");
  assert(cpu.GetValueAsString() == "1.500000");
  cpu.Reset();
  assert(cpu.GetValueAsString() == "0.000000");
  std::cout << "[PASS] CpuMetric tests passed.\n";

  HttpRequestsRPS http;
  http.Increment(3);
  assert(http.GetName() == "HTTP requests RPS");
  assert(http.GetValueAsString() == "3");
  http.Reset();
  assert(http.GetValueAsString() == "0");
  std::cout << "[PASS] HttpRequestsRPS tests passed.\n";

  MetricManager manager;
  auto cpu_ptr = std::make_shared<CpuMetric>();
  auto http_ptr = std::make_shared<HttpRequestsRPS>();
  manager.RegisterMetric(cpu_ptr);
  manager.RegisterMetric(http_ptr);

  auto snapshot = manager.GetMetricsSnapshot();
  assert(snapshot.size() == 2);
  std::cout << "[PASS] MetricManager test passed.\n";

  cpu_ptr->Set(0.75);
  http_ptr->Increment(7);
  {
    MetricLogger logger("test_metrics.log", manager, 500);
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  std::cout << "[PASS] MetricLogger integration test passed.\n";

  std::cout << "[ALL TESTS PASSED]\n";
}

int main() {
  RunTests();

  std::cout << "\n[DEMO] Starting metric logging...\n";

  MetricManager manager;
  auto cpu = std::make_shared<CpuMetric>();
  auto http = std::make_shared<HttpRequestsRPS>();
  manager.RegisterMetric(cpu);
  manager.RegisterMetric(http);

  MetricLogger logger("metrics_output.log", manager, 1000);

  for (int i = 0; i < 5; ++i) {
    cpu->Set(0.25 * (i + 1));
    http->Increment(10 + i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "[DEMO] Done logging.\n";
  return 0;
}
