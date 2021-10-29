#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "anomaly_detection_util.h"

using namespace std;
class TimeSeries {
    //private class members
    int numOfFeatures;
    int numOfSamples;
    vector<pair<string, vector<float>>> flightData;

    //private methods
    void readFromFile(const char *CSVfileName);
    void insertFeatures(stringstream& columnNamesBuff);
    void insertData(ifstream& dataCSVFile, string fileLine);

public:
    //constructor:
    explicit TimeSeries(const char *CSVfileName);
    //class getters:
    int getNumSamples() const;
    int getNumFeatures() const;
    vector<string> getFeatureVector() const;
    int indexOfFeature(string) const;
    string getNameOfFeature(int index) const;
    vector<float> getDataOfFeature(int) const;
    Point getFeaturesData(int index,string feature1, string feature2) const;
};

#endif /* TIMESERIES_H_ */