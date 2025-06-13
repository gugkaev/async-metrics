#include "HttpRequestsRPS.h"

HttpRequestsRPS::HttpRequestsRPS() : count_(0) {}

void HttpRequestsRPS::Increment(int v) {
  count_.fetch_add(v);
}

std::string HttpRequestsRPS::GetName() const {
  return "HTTP requests RPS";
}

std::string HttpRequestsRPS::GetValueAsString() const {
  return std::to_string(count_.load());
}

void HttpRequestsRPS::Reset() {
  count_.store(0);
}
