#include "Commands.h"

int openServer(int port) {
    //creates socket and checks if created
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        std::cerr << "Could not create a socket"<<std::endl;
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
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }
    // listens to clients (1 can wait in the queue)
    if (listen(socketFD, 1) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    // accepts a client
    socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketFD, (struct sockaddr *)&address,
                               &addrlen);
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }
    close(socketFD);
    //reading from client
    char buffer[1024] = {0};
    int count=0;

    while(true){
        count++;
        int valread = read( client_socket , buffer, 1024);
        std::cout<<buffer<<std::endl;
        /**if(count==2){
            break;
        }**/
    }
    return 0;
}
int OpenServerCommand::execute(list<string>::iterator it) {
    string port = *it;
    thread server_thread(openServer, calculateValue(port));
    server_thread.join();
    return 1;
}