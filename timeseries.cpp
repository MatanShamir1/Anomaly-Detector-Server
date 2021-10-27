#include "timeseries.h"
#include "anomaly_detection_util.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    this->numOfFeatures = 0;
    this->numDataPerFeature = 0;
    readFromFile(CSVfileName);
}

void TimeSeries::insertFeatures(stringstream& columnNamesBuff) {
    string token;
    int column_index=0;
    //create all the needed columns: each calumn is a key in a map, and its value is a new vector of floats.
    while(std::getline(columnNamesBuff,token,',')){
        this->flightData.emplace_back(token,new vector<float>);
        column_index++;
        this->numOfFeatures++;
    }
}

void TimeSeries::insertData(ifstream& dataCSVFile, string fileLine) {
    //as long as able to read more lines of the file, divided by commas, insert to the specific vector of a category.
    int column_index=0;
    string token;
    while(getline(dataCSVFile,fileLine)) {
        column_index=0;
        stringstream columnDataBuff(fileLine);
        while(std::getline(columnDataBuff,token,',')){
            stringstream token_to_int(token);
            float value;
            token_to_int>>value;
            this->flightData[column_index].second->push_back(value);
        }
        this->numDataPerFeature++;
    }
}

void TimeSeries::readFromFile(const char *CSVfileName) {
    // first, we create an input file stream with the given file as a parameter.
    ifstream dataCSVFile(CSVfileName);

    // in case the file isn't opened, throw an exception because the fstream object has failed.
    if(!dataCSVFile.is_open()){
        throw runtime_error("Could not open file");
    }
    //create a string that later will be each line read from the text file.
    string fileLine;
    //get the first line of the file, in which there are the column names.
    getline(dataCSVFile,fileLine);
    stringstream columnNamesBuff(fileLine);
    insertFeatures(columnNamesBuff);
    insertData(dataCSVFile, fileLine);
}
