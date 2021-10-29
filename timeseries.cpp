#include "timeseries.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    this->numOfFeatures = 0;
    this->numOfSamples = 0;
    readFromFile(CSVfileName);
}

void TimeSeries::insertFeatures(stringstream& columnNamesBuff) {
    string token;
    int column_index=0;
    //create all the needed columns: each column is a key in a map, and its value is a new vector of floats.
    while(std::getline(columnNamesBuff,token,',')){
        this->flightData.emplace_back(token, vector<float>());
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
            this->flightData[column_index].second.push_back(value);
        }
        this->numOfSamples++;
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
    dataCSVFile.close();
}

//class getter: return the amount of samples, also the size of each vector.
int TimeSeries:: getNumSamples() const{
    return this->numOfSamples;
}

//class getter: return the amount of Features in the time series.
int TimeSeries:: getNumFeatures() const{
    return this->numOfFeatures;
}

//class getter: get a an integer and return the related Feature name accordingly.
string TimeSeries::getNameOfFeature(int index) const{
    if(index >= flightData.size() || this->flightData.empty()){
        return NULL;
    }
    return flightData.at(index).first;
}

//class getter: get the vector of data of a specific feature.
vector<float> TimeSeries:: getDataOfFeature(int index) const{
    return this->flightData.at(index).second;
}

int TimeSeries::indexOfFeature(string feature) const{
    int result = 0;
    for(pair<string,vector<float>> a_pair :this->flightData){
        if(a_pair.first == feature){
            return result;
        }
        result++;
    }
}

//class getter: get a vector of all the features.
vector<string> TimeSeries::getFeatureVector() const {
    vector<string> features;
    for(int i=0; i< this->getNumFeatures();i++){
        features.push_back(this->flightData[i].first);
    }
    return features;
}



//class getter: given 2 features and an index, this method returns a point of the specific sample of the two features.
Point TimeSeries:: getFeaturesData(int index, string feature1, string feature2) const{
    float first, second;
    for(int i = 0; i < this->numOfFeatures; i++){
        if(flightData.at(i).first == feature1){
            first = this->flightData.at(i).second->at(index);
        } else if (flightData.at(i).first == feature2){
            second = this->flightData.at(i).second->at(index);
        }
    }
    return Point(first, second);
}