

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
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

    // you may add additional methods here
};

// you may add here helper classes
class CLI_Data{
    vector<AnomalyReport> reports;

};

// you may edit this class
class Command{
    DefaultIO* dio;
public:
    Command(DefaultIO* dio):dio(dio){}
    virtual void execute()=0;
    virtual ~Command(){}
};

// implement here your command classes
class UploadTimeCommand: Command{
    virtual void execute(){

    }
};

class AlgorithmCommand: Command{

};

class DetectCommand: Command{
    AnomalyReport r;
};

class DisplayCommand: Command{

};

class UploadAnomaliesCommand: Command{

};

class ExitCommand: Command{

};



#endif /* COMMANDS_H_ */
