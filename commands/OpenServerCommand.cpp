#include <sstream>
#include "Commands.h"
#include "../lexer/Lexer.h"
int s_client_socket;
int openServer(int port) {
    //creates socket and checks if created
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //binds socket to IP address (we want to listen to al IP)
    sockaddr_in address;
    address.sin_family = AF_INET;
    // any IP in IPV4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    // Binds the socket to the given port at localhost.
    if (bind(socketFD, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    // listens to clients (1 can wait in the queue)
    if (listen(socketFD, 1) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    // accepts a client
    socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketFD, (struct sockaddr *) &address,
                               &addrlen);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    close(socketFD);
    s_client_socket = client_socket;
    return 0;
}
void serverLoop() {
    //reading from client
    char buffer[1024] = {0};
    map<int, Variable *> orderedMap;
    map<string, Variable *> simSymbolTable = DefineVarCommand::getInstance()->getSimSymbolTable();
    simSymbolTable.insert(
            {"/instrumentation/airspeed-indicator/indicated-speed-kt",
             new Variable("<-", "/instrumentation/airspeed-indicator/indicated-speed-kt")});
    orderedMap.insert({0, simSymbolTable.find("/instrumentation/airspeed-indicator/indicated-speed-kt")->second});
    simSymbolTable.insert(
            {"/sim/time/warp",
             new Variable("<-", "/sim/time/warp")});
    orderedMap.insert({1, simSymbolTable.find("/sim/time/warp")->second});
    simSymbolTable.insert(
            {"/controls/switches/magnetos",
             new Variable("<-", "/controls/switches/magnetos")});
    orderedMap.insert({2, simSymbolTable.find("/controls/switches/magnetos")->second});
    simSymbolTable.insert(
            {"/instrumentation/heading-indicator/offset-deg",
             new Variable("<-", "/instrumentation/heading-indicator/offset-deg")});
    orderedMap.insert({3, simSymbolTable.find("/instrumentation/heading-indicator/offset-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/altimeter/indicated-altitude-ft",
             new Variable("<-", "/instrumentation/altimeter/indicated-altitude-ft")});
    orderedMap.insert({4, simSymbolTable.find("/instrumentation/altimeter/indicated-altitude-ft")->second});
    simSymbolTable.insert(
            {"/instrumentation/altimeter/pressure-alt-ft",
             new Variable("<-", "/instrumentation/altimeter/pressure-alt-ft")});
    orderedMap.insert({5, simSymbolTable.find("/instrumentation/altimeter/pressure-alt-ft")->second});
    simSymbolTable.insert(
            {"/instrumentation/attitude-indicator/indicated-pitch-deg",
             new Variable("<-", "/instrumentation/attitude-indicator/indicated-pitch-deg")});
    orderedMap.insert({6, simSymbolTable.find("/instrumentation/attitude-indicator/indicated-pitch-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/attitude-indicator/indicated-roll-deg",
             new Variable("<-", "/instrumentation/attitude-indicator/indicated-roll-deg")});
    orderedMap.insert({7, simSymbolTable.find("/instrumentation/attitude-indicator/indicated-roll-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/attitude-indicator/internal-pitch-deg",
             new Variable("<-", "/instrumentation/attitude-indicator/internal-pitch-deg")});
    orderedMap.insert({8, simSymbolTable.find("/instrumentation/attitude-indicator/internal-pitch-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/attitude-indicator/internal-roll-deg",
             new Variable("<-", "/instrumentation/attitude-indicator/internal-roll-deg")});
    orderedMap.insert({9, simSymbolTable.find("/instrumentation/attitude-indicator/internal-roll-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/encoder/indicated-altitude-ft",
             new Variable("<-", "/instrumentation/encoder/indicated-altitude-ft")});
    orderedMap.insert({10, simSymbolTable.find("/instrumentation/encoder/indicated-altitude-ft")->second});
    simSymbolTable.insert(
            {"/instrumentation/encoder/pressure-alt-ft",
             new Variable("<-", "/instrumentation/encoder/pressure-alt-ft")});
    orderedMap.insert({11, simSymbolTable.find("/instrumentation/encoder/pressure-alt-ft")->second});
    simSymbolTable.insert(
            {"/instrumentation/gps/indicated-altitude-ft",
             new Variable("<-", "/instrumentation/gps/indicated-altitude-ft")});
    orderedMap.insert({12, simSymbolTable.find("/instrumentation/gps/indicated-altitude-ft")->second});
    simSymbolTable.insert(
            {"/instrumentation/gps/indicated-ground-speed-kt",
             new Variable("<-", "/instrumentation/gps/indicated-ground-speed-kt")});
    orderedMap.insert({13, simSymbolTable.find("/instrumentation/gps/indicated-ground-speed-kt")->second});
    simSymbolTable.insert(
            {"/instrumentation/gps/indicated-vertical-speed",
             new Variable("<-", "/instrumentation/gps/indicated-vertical-speed")});
    orderedMap.insert({14, simSymbolTable.find("/instrumentation/gps/indicated-vertical-speed")->second});
    simSymbolTable.insert(
            {"/instrumentation/heading-indicator/indicated-heading-deg",
             new Variable("<-", "/instrumentation/heading-indicator/indicated-heading-deg")});
    orderedMap.insert({15, simSymbolTable.find("/instrumentation/heading-indicator/indicated-heading-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/magnetic-compass/indicated-heading-deg",
             new Variable("<-", "/instrumentation/magnetic-compass/indicated-heading-deg")});
    orderedMap.insert({16, simSymbolTable.find("/instrumentation/magnetic-compass/indicated-heading-deg")->second});
    simSymbolTable.insert(
            {"/instrumentation/slip-skid-ball/indicated-slip-skid",
             new Variable("<-", "/instrumentation/slip-skid-ball/indicated-slip-skid")});
    orderedMap.insert({17, simSymbolTable.find("/instrumentation/slip-skid-ball/indicated-slip-skid")->second});
    simSymbolTable.insert(
            {"/instrumentation/turn-indicator/indicated-turn-rate",
             new Variable("<-", "/instrumentation/turn-indicator/indicated-turn-rate")});
    orderedMap.insert({18, simSymbolTable.find("/instrumentation/turn-indicator/indicated-turn-rate")->second});
    simSymbolTable.insert(
            {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
             new Variable("<-", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm")});
    orderedMap.insert(
            {19, simSymbolTable.find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm")->second});
    simSymbolTable.insert(
            {"/controls/flight/aileron",
             new Variable("<-", "/controls/flight/aileron")});
    orderedMap.insert({20, simSymbolTable.find("/controls/flight/aileron")->second});
    simSymbolTable.insert(
            {"/controls/flight/elevator",
             new Variable("<-", "/controls/flight/elevator")});
    orderedMap.insert({21, simSymbolTable.find("/controls/flight/elevator")->second});
    simSymbolTable.insert(
            {"/controls/flight/rudder",
             new Variable("<-", "/controls/flight/rudder")});
    orderedMap.insert({22, simSymbolTable.find("/controls/flight/rudder")->second});
    simSymbolTable.insert(
            {"/controls/flight/flaps",
             new Variable("<-", "/controls/flight/flaps")});
    orderedMap.insert({23, simSymbolTable.find("/controls/flight/flaps")->second});
    simSymbolTable.insert(
            {"/controls/engines/engine/throttle",
             new Variable("<-", "/controls/engines/engine/throttle")});
    orderedMap.insert({24, simSymbolTable.find("/controls/engines/engine/throttle")->second});
    simSymbolTable.insert(
            {"/controls/engines/current-engine/throttle",
             new Variable("<-", "/controls/engines/current-engine/throttle")});
    orderedMap.insert({25, simSymbolTable.find("/controls/engines/engine/throttle")->second});
    simSymbolTable.insert(
            {"/controls/switches/master-avionics",
             new Variable("<-", "/controls/switches/master-avionics")});
    orderedMap.insert({26, simSymbolTable.find("/controls/switches/master-avionics")->second});
    simSymbolTable.insert(
            {"/controls/switches/starter",
             new Variable("<-", "/controls/switches/starter")});
    orderedMap.insert({27, simSymbolTable.find("/controls/switches/starter")->second});
    simSymbolTable.insert(
            {"/engines/active-engine/auto-start",
             new Variable("<-", "/engines/active-engine/auto-start")});
    orderedMap.insert({28, simSymbolTable.find("/engines/active-engine/auto-start")->second});
    simSymbolTable.insert(
            {"/controls/flight/speedbrake",
             new Variable("<-", "/controls/flight/speedbrake")});
    orderedMap.insert({29, simSymbolTable.find("/controls/flight/speedbrake")->second});
    simSymbolTable.insert(
            {"/sim/model/c172p/brake-parking",
             new Variable("<-", "/sim/model/c172p/brake-parking")});
    orderedMap.insert({30, simSymbolTable.find("/sim/model/c172p/brake-parking")->second});
    simSymbolTable.insert(
            {"/controls/engines/engine/primer",
             new Variable("<-", "/controls/engines/engine/primer")});
    orderedMap.insert({31, simSymbolTable.find("/controls/engines/engine/primer")->second});
    simSymbolTable.insert(
            {"/controls/engines/current-engine/mixture",
             new Variable("<-", "/controls/engines/current-engine/mixture")});
    orderedMap.insert({32, simSymbolTable.find("/controls/engines/current-engine/mixture")->second});
    simSymbolTable.insert(
            {"/controls/switches/master-bat",
             new Variable("<-", "/controls/switches/master-bat")});
    orderedMap.insert({33, simSymbolTable.find("/controls/switches/master-bat")->second});
    simSymbolTable.insert(
            {"/controls/switches/master-alt",
             new Variable("<-", "/controls/switches/master-alt")});
    orderedMap.insert({34, simSymbolTable.find("/controls/switches/master-alt")->second});
    simSymbolTable.insert(
            {"/engines/engine/rpm",
             new Variable("<-", "/engines/engine/rpm")});
    orderedMap.insert({35, simSymbolTable.find("/engines/engine/rpm")->second});
    int counter = 0;
    while (true) {
        mu.lock();
        int client_socket = s_client_socket;
        int valread = read(client_socket, buffer, 1024);
        stringstream bufferedValues(buffer);
        string value;
        while (getline(bufferedValues, value, ',')) {
            if (counter == 36) {
                counter = 0;
            }
            if (orderedMap.find(counter)->second->getDirection() == "<-") {
                orderedMap.find(counter)->second->setValue(stod(value));
            }
            counter++;
        }
        std::cout << buffer << std::endl;
        mu.unlock();
    }
}
int OpenServerCommand::execute(list<string>::iterator it) {
    string port = *it;
    thread server_thread(openServer, calculateValue(port));
    server_thread.join();
    //thread server_loop_thread(serverLoop);
    OpenServerCommand::getInstance()->loopThread = thread(serverLoop);
    //server_loop_thread.join();
    return 1;
}