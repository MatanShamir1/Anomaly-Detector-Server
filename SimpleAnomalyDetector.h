#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle minCircle;
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    //private fields
    vector<correlatedFeatures> cf;
    //we need a field of current correlation and a setter, because the command can change this.
    //private methods
    vector<Point *> createPoints(const vector<float> &f1, const vector<float> &f2, int size);
    float linearCorrelation;
    float maxDevPoint(Line f1, Point **, int);

public:
    SimpleAnomalyDetector(float linearCorrelation):linearCorrelation(linearCorrelation){}

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual void insertData(float correlation, correlatedFeatures* appendData,
                                          int num_of_samples, vector<Point *> featurePoint);

    virtual void add_report(Point *p, vector<AnomalyReport> *report, const correlatedFeatures &i1, size_t i);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);


    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }
};


#endif /* SIMPLEANOMALYDETECTOR_H_ */