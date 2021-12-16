#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start() {
    CLI_Data algData = CLI_Data();
    Command *one = new UploadTimeCommand(dio , "upload a time series csv file", &algData);
    Command *two = new SettingsCommand(dio , "algorithm settings", &algData);
    Command *three = new DetectCommand(dio,"detect anomalies" ,&algData);
    Command *four = new DisplayCommand(dio,"display results", &algData);
    Command *five = new UploadAnomaliesCommand(dio,"upload anomalies and analyze results" ,  &algData);
    Command *six = new ExitCommand(dio , "exit" , &algData);
    this->commands = {one, two, three, four, five, six};
    printMenu();
    string option = dio->read();
    while(option != "6"){
        int i = stoi(option);
        this->commands[i-1]->execute();
        printMenu();
        option = dio->read();
    }
}

void CLI::printMenu() {
    this->dio->write("Welcome to the Anomaly Detection Server.\n");
    this->dio->write("Please choose an option:\n");
    for (int i = 0; i <= 5; i++) {
        string string1 = commands[i]->description;
        this->dio->write(to_string(i+1) + "." + string1 + "\n");
    }
}


CLI::~CLI() {
    for (auto c : commands)
        delete c;
}