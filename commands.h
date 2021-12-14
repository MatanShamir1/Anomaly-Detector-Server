
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

class CLI_Data {
    vector<AnomalyReport> *reports;
    float correlation;
    const char *name_of_path_first_csv;
    const char *name_of_path_second_csv;
    long sample_amount_lines;
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

    void set_reports(vector<AnomalyReport> *report) {
        reports = report;
    }

    void set_amount_of_lines(long amount_of_lines) {
        this->sample_amount_lines = amount_of_lines;
    }

    vector<AnomalyReport>* get_reports() {
        return this->reports;
    }

    long get_amount_of_lines() {
        return this->sample_amount_lines;
    }

    void set_correlation(float new_correlation) {
        this->correlation = new_correlation;
    }

};

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

//    void uploadFile(string inPath, string outPath) {
//        ifstream inputStream;
//        inputStream.open(inPath);
//        ofstream outputStream;
//        outputStream.open(outPath);
//        string line;
//        while (getline(inputStream, line) && line != "done") {
//            outputStream << line;
//        }
//        inputStream.close();
//        outputStream.close();
//    }

    void uploadFile(const string &path, CLI_Data *data) {
        long counter = 0;
        ofstream outputStream;
        outputStream.open(path);
        string line;
        while ((line = read()) != "done") {
            counter++;
            outputStream << line << "\n";
        }
        counter--;
        data->set_amount_of_lines(counter);
        outputStream.close();
    }


    // you may add additional methods here
};

// you may add here helper classes

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
    UploadTimeCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description),
                                                                                    data) {}

    virtual void execute() {
        this->dio->write("Please upload your local train CSV file.\n");
        this->dio->uploadFile("anomalyTrain.csv", this->data);
        this->data->set_name_first_csv("anomalyTrain.csv");
        this->dio->write("Upload complete.\n");
        this->dio->write("Please upload your local test CSV file.\n");
        this->dio->uploadFile("anomalyTest.csv", this->data);
        this->data->set_name_second_csv("anomalyTest.csv");
        this->dio->write("Upload complete.\n");
    }
};

class SettingsCommand : public Command {

public:
    SettingsCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        this->dio->write("The current correlation threshold is ");
        this->dio->write(this->data->getCorrelation());
        this->dio->write("\nType a new threshold\n");
        float newCorrelation;
        this->dio->read(&newCorrelation);
        while (newCorrelation < 0 || newCorrelation > 1) {
            this->dio->write("please choose a value between 0 and 1.\n");
            this->dio->write("The current correlation threshold is");
            this->dio->write(this->data->getCorrelation());
            this->dio->write("\nType a new threshold\n");
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
        vector<AnomalyReport>* report= new vector<AnomalyReport>;
        *report = anomalyDetector->detect(second_ts);
        this->data->set_reports(report);
        dio->write("anomaly detection complete.\n");
        return;
    }
};

class DisplayCommand : public Command {
public:
    DisplayCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description), data) {}

    virtual void execute() {
        vector<AnomalyReport> *reports = this->data->get_reports();
        for (int i = 0; i < reports->size(); i++) {
            std::string s = std::to_string((*(reports))[i].timeStep);
            string output = s + "        " + (*(reports))[i].description + "\n";
            dio->write(output);
        }
        dio->write("Done.\n");
    }
};

class UploadAnomaliesCommand : public Command {
private:
    string make_printable_float(float num){
        string to_print = to_string(num);
        to_print = (to_print.substr(0, 5));
        string string_to_return;
        int check = 0;
        for (std::string::iterator it=to_print.end() -1; it!=to_print.begin(); --it) {
            std::string::iterator c =to_print.end() -check;
            if ((*it) != '0') {
                if (*it == '.') {
                    c = to_print.end() -check -1;
                    string_to_return = std::string(to_print.begin(), c);
                    break;
                }
                string_to_return = std::string(to_print.begin(),c);
                break;
            }
            check++;
        }
        return string_to_return;
    }
public:
    UploadAnomaliesCommand(DefaultIO *dio, string description, CLI_Data *data) : Command(dio, std::move(description),
                                                                                         data) {}

    virtual void execute() {
        dio->write("Please upload your local anomalies file.\n");
        vector<pair<long, long>> client_reports;
        string delimiter = ",";
        string token;
        size_t pos;
        string time_step;
        while ((time_step = dio->read()) != "done") {
            pair<long, long> period_time_step;
            pos = time_step.find(delimiter);
            period_time_step.first = std::stol(time_step.substr(0, pos));
            time_step.erase(0, pos + delimiter.length());
            period_time_step.second = stol(time_step);
            client_reports.push_back(period_time_step);
        }
        dio->write("Upload complete.\n");
        vector<AnomalyReport> *reports = this->data->get_reports();
        vector<pair<long, long>> server_reports;
        long initial_time = (*(reports))[0].timeStep, counter = (*(reports))[0].timeStep-1;
        string last_name = (*(reports))[0].description;
        for (const AnomalyReport &report: *reports) {
            if (&report == &reports->back()) {
                pair<long, long> newPair = make_pair(initial_time, report.timeStep);
                server_reports.push_back(newPair);
                break;
            }
            if (report.description != last_name || counter + 1 != report.timeStep) {
                pair<long, long> newPair = make_pair(initial_time, counter);
                server_reports.push_back(newPair);
                initial_time = report.timeStep;
            }
            counter = report.timeStep;
            last_name = report.description;
        }
        //now go through all server reports and client reports and test the false\true positives.
        float p = client_reports.size();
        float tp =0, fp=0, sum_of_lines_client = 0, N;
        for (pair<long, long> client_report: client_reports) {
            sum_of_lines_client += (client_report.second - client_report.first + 1);
        }
        N = this->data->get_amount_of_lines() - sum_of_lines_client;
        for (const pair<long, long> &server_report: server_reports) {
            for (const pair<long, long> &client_report: client_reports) {
                //if in the last iteration and no match, increment FP
                //if there is no overlap between the two reports, pass to the next.
                if (server_report.first > client_report.second || server_report.second < client_report.first){
                    //if there is no equivalence in the last, there has been no equivalence at all, this is a false positive.
                    if(&client_report == &client_reports.back()){
                        fp++;
                    }
                    continue;
                } else {
                    tp++;
                    break;
                }
            }
        }
        float true_positive = tp/p;
        float false_positive = fp/N;

        string s1 = "True Positive Rate: " + make_printable_float(true_positive) + "\n";
        string s2 = "False Positive Rate: " + make_printable_float(false_positive) + "\n";
        dio->write(s1 +s2);

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