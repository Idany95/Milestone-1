#include "Commands.h"

int conectClient(int port) {
    // creates a socket and checks if created
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    // creates a socket address
    sockaddr_in address;
    // IPV4, local host, the port we get
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);
    // requests to connect
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
     // TODO for now, we want to know if the client connected.
    int is_sent = send(client_socket , "Hi from client" , strlen("Hi from client"), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }
    char buffer[1024] = {0};
    // reads information TODO (for now to check)
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;
    close(client_socket);
    return 0;
}
int ConnectCommand::execute(list<string>::iterator it) {
    string ip = *it;
    string port = *(++it);
    thread client_thread(conectClient, stoi(port));
    client_thread.join();
    return 2;
}