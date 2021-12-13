
#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector : public SimpleAnomalyDetector {
public:
    virtual ~HybridAnomalyDetector();

    HybridAnomalyDetector(float linearCorrelation) : SimpleAnomalyDetector(linearCorrelation) {}

    virtual void insertData(float correlation, correlatedFeatures *ptr_appendData,
                            int num_of_samples, vector<Point *> featurePoint);

    virtual void add_report(Point *p, vector<AnomalyReport> *report, const correlatedFeatures &i1, size_t i);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */