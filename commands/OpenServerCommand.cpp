#include "Commands.h"

int openServer(int port)
{
    //create socket
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    // Binding the socket to the given port at localhost.
    if (bind(socketFD, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }
    if (listen(socketFD, 1) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketFD, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }

    close(socketFD); //closing the listening socket
    //reading from client
    char buffer[1024] = {0};
    int count=0;
    while(true){
        count++;
        int valread = read( client_socket , buffer, 1024);
        std::cout<<buffer<<std::endl;
        if(count==2){
            break;
        }
    }
    return 0;
}
int OpenServerCommand::execute(list<string>::iterator it) {
    string instruction = *it;
    string port = *(++it);
    thread server_thread(openServer, stoi(port));
    server_thread.join();
    return 2;
}
