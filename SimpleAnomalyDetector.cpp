
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    float threshold = 0.9;
    vector<float> f1;
    vector<float> f2;
    int numFeatures = ts.getNumFeatures();
    for (int i = 1; i < numFeatures; i++) {
        int currentCorrelate = -1;
        f1 = ts.getDataOfFeature(i);
        for (int j = i + 1; j < numFeatures; j++) {
            f2 = ts.getDataOfFeature(j);
            if (pearson(&f1[0], &f2[0], f1.size()) > threshold) {
                currentCorrelate = j;
                threshold = pearson(&f1[0], &f2[0], f1.size());
            }
        }
        if (currentCorrelate != -1) {
            correlatedFeatures appendData;
            appendData.threshold = 0.9;
            appendData.corrlation = threshold;
            appendData.feature1 = to_string(i);
            appendData.feature2 = to_string(currentCorrelate);
            vector<Point>featurePoint = createPoints(&f1[0],&f2[0],ts.getNumSamples());
            Point **points = nullptr;
            std::copy(featurePoint.begin(), featurePoint.end(), points);
            appendData.lin_reg = linear_reg(points,featurePoint.size());
            cf.push_back(appendData);
        }
    }
}

vector<Point> SimpleAnomalyDetector::createPoints(float *f1, float *f2, int size) {
    vector<Point>featuresPoints;
    for (int i = 0; i < size; i++) {
        featuresPoints.push_back(Point(f1[i],f2[i]));
    }
    return featuresPoints;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}
