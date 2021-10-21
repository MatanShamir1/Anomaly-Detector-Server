#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;
    class TimeSeries {
        //private class members
        int numColumns;
        int numRows;
        map<string, vector<float>> flightData;

        //private methods
        void readFromFile(const char *CSVfileName);

    public:
        TimeSeries(const char *CSVfileName);
    };

#endif /* TIMESERIES_H_ */
