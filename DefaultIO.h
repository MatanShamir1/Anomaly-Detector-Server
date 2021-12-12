//
// Created by LordMatansha on 12/12/21.
//

#ifndef ANOMALYDETECTOR_DEFAULTIO_H
#define ANOMALYDETECTOR_DEFAULTIO_H

#include <string>

using namespace std;

class DefaultIO {
    virtual string read() = 0;
    virtual void write(string text) = 0;
};


#endif //ANOMALYDETECTOR_DEFAULTIO_H
