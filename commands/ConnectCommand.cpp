#include "Commands.h"

int conectClient(string ip, int port) {
    // creates a socket and checks if created
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    // creates a socket address
    sockaddr_in address;
    const char* IP = ip.c_str();
    // IPV4, local host, the port we get
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP);
    address.sin_port = htons(port);
    // requests to connect
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    // we want to know if the client connected.
    int is_sent = send(client_socket , "Hi from client" , strlen("Hi from client"), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }
    queue<Variable*> variableQueue = DefineVarCommand::getInstance()->getQueue();
    mu.lock();
    while (!variableQueue.empty()) {
        Variable* currentVariable = variableQueue.front();
        variableQueue.pop();
        string simPath = currentVariable->getSim();
        string value = to_string(currentVariable->getValue());
        string message = "set{" + simPath + "}{" + value + "}\n";
        char* messageSend = const_cast<char *>(message.c_str());
        int toSend = send(client_socket , messageSend , strlen(messageSend), 0);
        if (is_sent == -1) {
            std::cout << "Error sending message" << std::endl;
        }
    }
    mu.unlock();
    close(client_socket);
    return 0;
}
int ConnectCommand::execute(list<string>::iterator it) {
    string ip = (*it).substr(1,(*it).length()-2);
    string port = *(++it);
    ConnectCommand::getInstance()->loopThread = thread(conectClient,ip,calculateValue(port));
    //client_thread(conectClient,ip,calculateValue(port));
    //client_thread.join();
    return 2;
}