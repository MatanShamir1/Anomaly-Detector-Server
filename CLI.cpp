#include "CLI.h"
#include "DefaultIO.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){
    Command* a = new UploadTimeCommand()
    Command* a = new UploadAnomaliesCommand()
}


CLI::~CLI() {
}

