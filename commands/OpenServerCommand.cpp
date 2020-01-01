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
    int counter = 0;
    while (true) {
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
                DefineVarCommand::getInstance()->getOrderedMap()->find(counter)->second->setValue(stod(value));
            }
            counter++;
            mu.unlock();
        }
        //std::cout << buffer << std::endl;
    }
}
int OpenServerCommand::execute(list<string>::iterator it) {
    string port = *it;
    cout << "serverCommand: ";
    cout << port << endl;
    thread server_thread(openServer, calculateValue(port));
    server_thread.join();
    //thread server_loop_thread(serverLoop);
    OpenServerCommand::getInstance()->loopThread = thread(serverLoop);
    //server_loop_thread.join();
    return 0;
}