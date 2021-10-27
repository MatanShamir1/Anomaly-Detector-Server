#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
    class TimeSeries {
        //private class members
        int numOfFeatures;
        int numDataPerFeature;
        vector<pair<string, vector<float>*>> flightData;

        //private methods
        void readFromFile(const char *CSVfileName);
        void insertFeatures(stringstream& columnNamesBuff);
        void insertData(ifstream& dataCSVFile, string fileLine);

    public:
        explicit TimeSeries(const char *CSVfileName);
    };

#endif /* TIMESERIES_H_ */
