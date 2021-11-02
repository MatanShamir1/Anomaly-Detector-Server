#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //this is minimal correlation, each time there's a correlation the max updates.
    int num_of_samples = ts.getNumSamples();
    vector<float> f1, f2;
    int numFeatures = ts.getNumFeatures();
    for (int i = 0; i < numFeatures; i++) {
        //if no matching correlation, this will remain -1.
        int currentCorrelate = -1;
        float correlation = 0.9;
        f1 = ts.getDataOfFeature(i);
        for (int j = i + 1; j < numFeatures; j++) {
            f2 = ts.getDataOfFeature(j);
            if (abs(pearson(&f1[0],&f2[0], ts.getNumSamples())) > correlation) {
                currentCorrelate = j;
                correlation = pearson(&f1[0], &f2[0], num_of_samples);
            }
        }
        if (currentCorrelate != -1) {
            correlatedFeatures appendData;
            appendData.corrlation = correlation;
            appendData.feature1 = ts.getNameOfFeature(i);
            appendData.feature2 = ts.getNameOfFeature(currentCorrelate);
            vector<Point*> featurePoint = createPoints(f1, ts.getDataOfFeature(currentCorrelate), num_of_samples);
            appendData.lin_reg = linear_reg(&(featurePoint[0]), num_of_samples);
            appendData.threshold = maxDevPoint(appendData.lin_reg, &(featurePoint[0]), num_of_samples);
            this->cf.push_back(appendData);
        }
    }
}
//correct for sure
vector<Point*> SimpleAnomalyDetector::createPoints(const vector<float>& f1, const vector<float>& f2, int size) {
    vector<Point*> featuresPoints;
    for (int i = 0; i < size; i++) {
        auto* p = new Point(f1[i], f2[i]);
        featuresPoints.push_back(p);
    }
    return featuresPoints;
}

float SimpleAnomalyDetector::maxDevPoint(Line f1,Point** points, int size) {
    float maxDev = dev(**points, f1);
    for (int i = 1; i < size; i++) {
        float check = dev(*(points[i]), f1);
        if (check > maxDev) {
            maxDev = check;
        }
    }
    return (float)(maxDev*1.1);
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;
    if (this->cf.empty()) {
        // exceptions maybe
        learnNormal(ts);
    }
    //each variable initiated in the for loop is a const reference, not a shallow copy!
    for (const correlatedFeatures& i1: this->cf) {
        //we use create points because this is data of a new input of a flight.
        vector<Point*> dataPoints = createPoints(ts.getDataOfFeature(ts.indexOfFeature(i1.feature1)),
                                                ts.getDataOfFeature(ts.indexOfFeature(i1.feature2)),
                                                ts.getNumSamples());
        for (Point* p: dataPoints) {
            if (dev(*p, i1.lin_reg) > i1.threshold) {
                AnomalyReport deviation = AnomalyReport(i1.feature1 + "-" + i1.feature2, p->x);
                report.push_back(deviation);
            }
        }
    }
    return std::move(report);
}