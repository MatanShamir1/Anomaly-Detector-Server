
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::insertData(float correlation, correlatedFeatures* ptr_appendData,
                                                     int num_of_samples, vector<Point *> featurePoint){
    if (correlation >= 0.9) {
        SimpleAnomalyDetector::insertData(correlation, ptr_appendData, num_of_samples, featurePoint);
    } else if (correlation >= 0.5){
        ptr_appendData->minCircle = findMinCircle(&(featurePoint[0]), featurePoint.size());
        ptr_appendData->minCircle.radius *= 1.1;
    } else {
        ptr_appendData->corrlation = -1;
    }
}

void HybridAnomalyDetector::add_report(Point *p, vector<AnomalyReport> *report, const correlatedFeatures &i1, size_t i){
    if (i1.corrlation >= 0.9) {
        SimpleAnomalyDetector::add_report(p,report,i1,i);
    } else if (i1.corrlation >= 0.5){
        if(!isInside(i1.minCircle, *p)){
            AnomalyReport deviation = AnomalyReport(i1.feature1 + "-" + i1.feature2, i + 1);
            report->push_back(deviation);
        }
    }
}