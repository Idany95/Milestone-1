#include "Commands.h"

int SleepCommand::execute(list<string>::iterator it) {
//    double time = calculateValue(*it) / 1000;
//    sleep(time);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)calculateValue(*it)));
    return 0;
}