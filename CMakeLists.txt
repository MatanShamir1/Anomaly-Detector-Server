cmake_minimum_required(VERSION 3.0)
project(anomaly_detection_util)

set(CMAKE_CXX_STANDARD 14)

add_executable(anomaly_detection_util MainTrain.cpp anomaly_detection_util.cpp anomaly_detection_util.h)
