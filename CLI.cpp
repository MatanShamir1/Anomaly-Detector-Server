#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start() {
    CLI_Data algData = CLI_Data();
    Command *one = new UploadTimeCommand(dio , "upload a time series csv file", &algData);
    Command *two = new SettingsCommand(dio , "algorithm settings", &algData);
    Command *three = new DetectCommand(dio, &algData);
    Command *four = new DisplayCommand(dio, &algData);
    Command *five = new UploadAnomaliesCommand(dio, &algData);
    Command *six = new ExitCommand();
    this->commands = {one, two, three, four, five, six};
    printMenu();
    string option = dio->read();
    while(option != "6"){
        int i = stoi(option);
        this->commands[i]->execute();
        option = dio->read();
    }
}

void CLI::printMenu() {
    cout << "Welcome to the Anomaly Detection Server" << endl;
    cout << "Please choose an option" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i << "." << commands[i]->getDescription() << endl;
    }
}


CLI::~CLI() {
}

