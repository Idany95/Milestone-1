#include "Commands.h"

/**
 * This is SleepCommand class for Sleep command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int SleepCommand::execute(list<string>::iterator it) {
    std::this_thread::sleep_for(std::chrono::milliseconds((int)calculateValue(*it)));
    return 0;
}