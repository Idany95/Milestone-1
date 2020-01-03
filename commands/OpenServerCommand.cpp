#include <sstream>
#include "Commands.h"
#include "../lexer/Lexer.h"
// global socket
int s_client_socket;

/**
 * This is a callable for the thread of opening the server
 * @param port the port to listen
 * @return 0 if all the steps succeeded
 */
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

/**
 * This is a callable for the thread of the sever loop
 */
void serverLoop() {
    //reading from client
    char buffer[1024] = {0};
    int counter = 0;
    /**
     * read variables of "generic small"
     */
    while (ParseCommand::getInstance()->getParsingFlag() == false) {
        int client_socket = s_client_socket;
        int valread = read(client_socket, buffer, 1024);
        stringstream bufferedValues(buffer);
        string value;
        while (getline(bufferedValues, value, ',')) {
            mu.lock();
            if (counter == 36) {
                counter = 0;
            }
            if (DefineVarCommand::getInstance()->getOrderedMap()->find(counter)->second->getDirection() == "<-") {
                try {
                    DefineVarCommand::getInstance()->getOrderedMap()->find(counter)->second->setValue(stod(value));
                }
                catch(...) {
                    cout << "Couldn't use stod in OpenServerCommand" << endl;
                }
            }
            counter++;
            mu.unlock();
        }
    }
}

/**
 * Execute the command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int OpenServerCommand::execute(list<string>::iterator it) {
    // the port to listen
    string port = *it;
    // open new threads for open a server and do the server loop
    thread server_thread(openServer, calculateValue(port));
    server_thread.join();
    OpenServerCommand::getInstance()->loopThread = thread(serverLoop);
    return 0;
}