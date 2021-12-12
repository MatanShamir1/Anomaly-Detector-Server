
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <utility>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    void uploadFile(string inPath, string outPath) {
        ifstream inputStream;
        inputStream.open(inPath);
        ofstream outputStream;
        outputStream.open(outPath);
        string line;

        while (getline(inputStream, line) && line != "done") {
            outputStream << line;
        }
        inputStream.close();
        outputStream.close();
    }

    void uploadFile(const string &path) {
        ofstream outputStream;
        outputStream.open(path);
        string line;
        while ((line = read())!="done") {
            outputStream << line;
        }
        outputStream.close();
    }


    // you may add additional methods here
};

// you may add here helper classes
class CLI_Data{
    vector<AnomalyReport>* reports;
    float correlation;
public:
    CLI_Data(){
        this->correlation = 0.9;
    }
    float getCorrelation(){
        return this->correlation;
    }
};

// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    CLI_Data* data;
public:
    string description;
    Command(DefaultIO* dio , string description, CLI_Data* data){
        this->dio = dio;
        this->description = std::move(description);
        this->data = data;
    }
    virtual void execute() = 0;
    virtual ~Command(){}
    string getDescription(){
        return this->description;
    }
};

// implement here your command classes
class UploadTimeCommand: public Command{
public:
    UploadTimeCommand(DefaultIO* dio, string description, CLI_Data* data): Command(dio, std::move(description), data){}
    virtual void execute(){
        this->dio->write("please upload your local train csv file.\n");
        this->dio->uploadFile("anomalyTrain.csv");
        this->dio->write("Upload Complete.\n");
        this->dio->write("please upload your local train csv file.\n");
        this->dio->uploadFile("anomalyTest.csv");
        this->dio->write("Upload Complete.\n");
    }
};

class SettingsCommand: public Command{

public:
    SettingsCommand(DefaultIO* dio, string description, CLI_Data* data): Command(dio, std::move(description), data){}
    virtual void execute(){
        this->dio->write("The current correlation threshold is");
        this->dio->write(this->data->getCorrelation());
        float newCorrelation;
        this->dio->read(&newCorrelation);
        while(newCorrelation<0 || newCorrelation>1){
            this->dio->write("please choose a value between 0 and 1.");
            this->dio->write("The current correlation threshold is");
            this->dio->write(this->data->getCorrelation());
            this->dio->read(&newCorrelation);
        }
    }
};

class DetectCommand: public Command{

};

class DisplayCommand: public Command{

};

class UploadAnomaliesCommand: public Command{

};

class ExitCommand: public Command{

};



#endif /* COMMANDS_H_ */
