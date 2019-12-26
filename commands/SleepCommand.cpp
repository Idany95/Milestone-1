#include "Commands.h"

int SleepCommand::execute(list<string>::iterator it) {
    double time = calculateValue(*it) / 1000;
    sleep(time);
    return 0;
}