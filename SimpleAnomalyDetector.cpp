
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    float corealtion = 0.9;
    vector<float> f1;
    vector<float> f2;
    int numFeatures = ts.getNumFeatures();
    for (int i = 1; i < numFeatures; i++) {
        int currentCorrelate = -1;
        f1 = ts.getDataOfFeature(i);
        for (int j = i + 1; j < numFeatures; j++) {
            f2 = ts.getDataOfFeature(j);
            if (pearson(&f1[0], &f2[0], f1.size()) > corealtion) {
                currentCorrelate = j;
                corealtion = pearson(&f1[0], &f2[0], f1.size());
            }
        }
        if (currentCorrelate != -1) {
            correlatedFeatures appendData;
            appendData.corrlation = corealtion;
            appendData.feature1 = to_string(i);
            appendData.feature2 = to_string(currentCorrelate);
            vector<Point> featurePoint = createPoints(&f1[0], &f2[0], ts.getNumSamples());
            Point **points = nullptr;
            std::copy(featurePoint.begin(), featurePoint.end(), points);
            appendData.lin_reg = linear_reg(points, featurePoint.size());
            appendData.threshold = maxDevPoint(appendData.lin_reg, points, featurePoint.size());
            cf.push_back(appendData);
        }
    }
}

vector<Point> SimpleAnomalyDetector::createPoints(float *f1, float *f2, int size) {
    vector<Point> featuresPoints;
    for (int i = 0; i < size; i++) {
        featuresPoints.push_back(Point(f1[i], f2[i]));
    }
    return featuresPoints;
}

float SimpleAnomalyDetector::maxDevPoint(Line f1, Point **points, int size) {
    float maxDev = dev(*points[0], f1);
    for (int i = 1; i < size; i++) {
        float check = dev(*points[i], f1);
        if (check > maxDev) {
            maxDev = check;
        }
    }
    maxDev = maxDev * 1.1;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;
    if (cf.empty()) {
        // exceptions maybe
        learnNormal(ts);
    }
    long i = 1;
    for (correlatedFeatures i1: cf) {
        int numOfFeature1 = stoi(i1.feature1);
        int numOfFeature2 = stoi(i1.feature2);
        vector<Point> dataPoints = createPoints(&ts.getDataOfFeature(numOfFeature1)[0],
                                                &ts.getDataOfFeature(numOfFeature2)[0], ts.getNumSamples());
        for (Point p: dataPoints) {
            if (dev(p, i1.lin_reg) > i1.threshold) {
                AnomalyReport deviation = AnomalyReport(i1.feature1 + "-" + i1.feature2, i);
                i++;
                report.push_back(deviation);
            }
        }
    }
    return report;
}
