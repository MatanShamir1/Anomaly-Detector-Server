

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
    CLI_Data data; // the data needed for the cli program- reports, etc.

    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
    void printMenu();
};

#endif /* CLI_H_ */
