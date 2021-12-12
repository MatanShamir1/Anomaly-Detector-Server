#include "SimpleAnomalyDetector.h"

#include <utility>
#include "anomaly_detection_util.h"

const float oneDotOne = 1.2;

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //this is minimal correlation, each time there's a correlation the max updates.
    int num_of_samples = ts.getNumSamples();
    vector<float> f1, f2;
    int numFeatures = ts.getNumFeatures();
    // go over every feature and find the most correlated feature of him.
    for (int i = 0; i < numFeatures; i++) {
        //if no matching correlation, this will remain -1.
        int currentCorrelate = -1;
        float correlation = 0;
        f1 = ts.getDataOfFeature(i);
        for (int j = i + 1; j < numFeatures; j++) {
            f2 = ts.getDataOfFeature(j);
            // ask if the correlation is bigger from the current correlation.
            if (abs(pearson(&f1[0], &f2[0], ts.getNumSamples())) >= correlation) {
                currentCorrelate = j;
                correlation = pearson(&f1[0], &f2[0], num_of_samples);
            }
        }
        if(currentCorrelate != -1) {
            correlatedFeatures appendData;
            appendData.corrlation = correlation;
            appendData.feature1 = std::move(ts.getNameOfFeature(i));
            appendData.feature2 = std::move(ts.getNameOfFeature(currentCorrelate));
            // create point from the two feature.
            vector<Point *> featurePoint = createPoints(f1, ts.getDataOfFeature(currentCorrelate), num_of_samples);
            insertData(correlation, &appendData, num_of_samples, featurePoint);
            for (size_t k = 0; k < num_of_samples; k++)
                delete featurePoint[k];
            if (appendData.corrlation != -1) {
                cf.push_back(appendData);
            }
        }
    }
}


void SimpleAnomalyDetector::insertData(float correlation, correlatedFeatures* ptr_appendData,
                                                     int num_of_samples, vector<Point *> featurePoint) {
    if (correlation >= 0.9) {
        ptr_appendData->lin_reg = linear_reg(&(featurePoint[0]), num_of_samples);
        // send to check the most further point from the linear.
        ptr_appendData->threshold = maxDevPoint(ptr_appendData->lin_reg, &(featurePoint[0]), num_of_samples) * oneDotOne;
        // delete  points that we created on the heap.
    } else {
        ptr_appendData->corrlation = -1;
    }
}


// the function create point with the two feature.
vector<Point *> SimpleAnomalyDetector::createPoints(const vector<float> &f1, const vector<float> &f2, int size) {
    vector<Point *> featuresPoints;
    for (int i = 0; i < size; i++) {
        auto *p = new Point(f1[i], f2[i]);
        featuresPoints.push_back(p);
    }
    return featuresPoints;
}

// the function check the most distance point from the linear.
float SimpleAnomalyDetector::maxDevPoint(Line f1, Point **points, int size) {
    float maxDev = 0;
    for (int i = 0; i < size; i++) {
        float check = dev(*(points[i]), f1);
        if (check > maxDev) {
            maxDev = check;
        }
    }
    return maxDev;
}

void SimpleAnomalyDetector::add_report(Point *p, vector<AnomalyReport> *report, const correlatedFeatures &i1, size_t i){
    if (dev(*p, i1.lin_reg) > i1.threshold) {
        AnomalyReport deviation = AnomalyReport(i1.feature1 + "-" + i1.feature2, i + 1);
        report->push_back(deviation);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;
    //each variable initiated in the for loop is a const reference, not a shallow copy!
    for (const correlatedFeatures &i1: this->cf) {
        //we use create points because this is data of a new input of a flight.
        vector<Point *> dataPoints = createPoints(ts.getDataOfFeature(ts.indexOfFeature(i1.feature1)),
                                                  ts.getDataOfFeature(ts.indexOfFeature(i1.feature2)),
                                                  ts.getNumSamples());
        for (size_t i = 0; i < dataPoints.size(); i++) {
            add_report(dataPoints[i], &report, i1, i);
        }
    }
    return std::move(report);
}
