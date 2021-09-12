//
// Created by cuadriante on 2/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_SERVERSOCKET_H
#define DATOSII_PROYECTOI_SERVER_SERVERSOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> //librerias para red
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h> // threads for multiprogramming
#include <vector> //para almacenar varios clientes
#include <unistd.h>
using namespace std;

//Structure to represent clients
struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class ServerSocket {
public:
    ServerSocket();
    void run();
    void sendMessageToAll(const char *msn);
    string readMessage();

private:
    int descriptor; // se utiliza para identificar los sistemas
    const int maxConnectedClients = 4;
    static const int bufferSize = 1024;
    sockaddr_in info;
    vector<int> clients; // stores connected clients
    bool create_socket();
    bool bind_kernel(); //bind with port, establish maximum client quantity
    static void* ClientController(void*);

    void sendMessage(int id, const char *msn);
};


#endif //DATOSII_PROYECTOI_SERVER_SERVERSOCKET_H
