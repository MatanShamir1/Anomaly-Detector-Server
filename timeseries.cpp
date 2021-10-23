#include "timeseries.h"
#include "anomaly_detection_util.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    numColumns = 0;
    numRows = 0;
    readFromFile(CSVfileName);
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
    string token;
    //create all of the needed columns: each calumn is a key in a map, and its value is a new vector of floats.
    while(std::getline(columnNamesBuff,token,',')){
        flightData[token] = vector<float>();
    }
    int columnIndex = 0;
    //as long as able to read more lines of the file, divided by commas, insert to the specific vector of a category.
    //MAIN PROBLEM IN TIMESERIES: CAN'T TELL FOR WHICH COLUMN TO ADD THE WORDS TO, NEED TO NUMBER THE MAP SOMEHOW.
    while(getline(dataCSVFile,fileLine)) {
        stringstream columnDataBuff(fileLine);
        while(std::getline(columnNamesBuff,token,',')){

        }
    }
}
