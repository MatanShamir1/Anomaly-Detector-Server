
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <utility>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "timeseries.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

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
        while ((line = read()) != "done") {
            outputStream << line;
        }
        outputStream.close();
    }


    // you may add additional methods here
};

// you may add here helper classes
class CLI_Data {
    vector<AnomalyReport> *reports;
    float correlation;
    const char *name_of_path_first_csv;
    const char *name_of_path_second_csv;
public:
    CLI_Data() {
        this->correlation = 0.9;
    }

    float getCorrelation() {
        return this->correlation;
    }

    void set_name_first_csv(const char *name_of_first_csv) {
        this->name_of_path_first_csv = name_of_first_csv;
    }

    void set_name_second_csv(const char *name_of_second_csv) {
        this->name_of_path_second_csv = name_of_second_csv;
    }

    const char *get_name_second_csv() {
        return this->name_of_path_second_csv;
    }

    const char *get_name_first_csv() {
        return this->name_of_path_first_csv;
    }

    void set_reports(vector<AnomalyReport> * report) {
        reports = report;
    }

    vector<AnomalyReport> get_reports() {
        return *this->reports;
    }
    void set_correlation(float new_correlation){
        this->correlation = new_correlation;
    }

};

// you may edit this class
class Command {
protected:
    DefaultIO *dio;
    CLI_Data *data;
public:
    string description;

    Command(DefaultIO *dio, string description, CLI_Data *data) {
        this->dio = dio;
        this->description = std::move(description);
        this->data = data;
    }

    virtual void execute() = 0;

    virtual ~Command() {}

    string getDescription() {
        return this->description;
    }
};

// implement here your command classes
class UploadTimeCommand : public Command {
public:
    UploadTimeCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description),data) {}

    virtual void execute() {
        this->dio->write("please upload your local train csv file.\n");
        this->dio->uploadFile("anomalyTrain.csv");
        this->data->set_name_first_csv("anomalyTrain.csv");
        this->dio->write("Upload Complete.\n");
        this->dio->write("please upload your local train csv file.\n");
        this->dio->uploadFile("anomalyTest.csv");
        this->data->set_name_second_csv("anomalyTest.csv");
        this->dio->write("Upload Complete.\n");
    }
};

class SettingsCommand : public Command {

public:
    SettingsCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        this->dio->write("The current correlation threshold is");
        this->dio->write(this->data->getCorrelation());
        float newCorrelation;
        this->dio->read(&newCorrelation);
        while (newCorrelation < 0 || newCorrelation > 1) {
            this->dio->write("please choose a value between 0 and 1.");
            this->dio->write("The current correlation threshold is");
            this->dio->write(this->data->getCorrelation());
            this->dio->read(&newCorrelation);
        }
        this->data->set_correlation(newCorrelation);
    }
};

class DetectCommand : public Command {
public:
    DetectCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        HybridAnomalyDetector *anomalyDetector = new HybridAnomalyDetector(data->getCorrelation());
        const char *name = this->data->get_name_first_csv();
        TimeSeries ts = TimeSeries(name);
        anomalyDetector->learnNormal(ts);
        const char *name_second_file = this->data->get_name_second_csv();
        TimeSeries second_ts = TimeSeries(name_second_file);
        vector<AnomalyReport> report = anomalyDetector->detect(second_ts);
        this->data->set_reports(&report);
        dio->write("anomaly detection complete");
    }
};

class DisplayCommand : public Command {
public:
    DisplayCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        vector<AnomalyReport> report = this->data->get_reports();
        for (int i = 0; i < report.size(); i++) {
            std::string s = std::to_string(report[i].timeStep);
            // maybe add /n
            string output = s + "    " + report[i].description;
            dio->write(output);
        }
        dio->write("Done.");
    }
};

class UploadAnomaliesCommand : public Command {
public:
    UploadAnomaliesCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description),
                                                                                         data) {}

    virtual void execute() {
        dio->write("Please upload your local anomalies file.");
        vector<pair<long, long>> detection;
        string delimiter = ",";
        long splits[2];
        string token;
        size_t pos = 0;
        int i = 0;

        string time_step = dio->read();
        while (time_step != "done") {
            pair<long , long> period_time_step;
            while ((pos = time_step.find(delimiter)) != std::string::npos) {
                token = time_step.substr(0, pos);
                splits[i] = std::stoi(token);
                time_step.erase(0, pos + delimiter.length());
                i++;
            }
            period_time_step.first = splits[0];
            period_time_step.second = splits[1];
            detection.push_back(period_time_step);
            time_step = dio->read();
        }


    }
};


class ExitCommand : public Command {
public:
    ExitCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        return;
    }
};


#endif /* COMMANDS_H_ */