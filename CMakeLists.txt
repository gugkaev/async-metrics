cmake_minimum_required(VERSION 3.30)
project(async_metrics)

set(CMAKE_CXX_STANDARD 20)

add_executable(async_metrics main.cpp
        IMetric.h
        CpuMetric.cpp
        CpuMetric.h
        HttpRequestsRPS.cpp
        HttpRequestsRPS.h
        MetricManager.cpp
        MetricManager.h
        MetricLogger.cpp
        MetricLogger.h)
