#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){
    Command* one = new UploadTimeCommand();
    Command* two = new AlgorithmCommand();
    Command* three = new DetectCommand();
    Command* four = new DisplayCommand();
    Command* five = new UploadAnomaliesCommand();
    Command* six = new ExitCommand();
    this->commands = {one, two, three, four, five, six};
}


CLI::~CLI() {
}

