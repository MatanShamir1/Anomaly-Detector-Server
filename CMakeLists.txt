cmake_minimum_required(VERSION 3.0)
project(AnomalyDetector)

set(CMAKE_CXX_STANDARD 14)

add_executable(anomaly_detection_util MainTrain.cpp anomaly_detection_util.cpp anomaly_detection_util.h timeseries.cpp timeseries.h SimpleAnomalyDetector.h SimpleAnomalyDetector.cpp AnomalyDetector.h minCircle.cpp minCircle.h HybridAnomalyDetector.cpp HybridAnomalyDetector.cpp CLI.cpp CLI.h commands.h Server.cpp Server.h)
