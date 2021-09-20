//
// Created by cuadriante on 14/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_SERVERLISTENER_H
#define DATOSII_PROYECTOI_SERVER_SERVERLISTENER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> //librerias para red
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h> // threads for multiprogramming
#include <vector> //para almacenar varios clientes
#include <unistd.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>

using namespace std;

class ServerListener {
private:
    int serverSocketId;
    struct sockaddr_in serverSocketInfo;
    int serverSocketInfoLen = sizeof(serverSocketInfo);
    int serverSocketPort = 4050;
    int maxConnectedClients = 5;
public:
    bool start();
    void waitForConnections();
    static void * startClientSession(void * psocketId);
};


#endif //DATOSII_PROYECTOI_SERVER_SERVERLISTENER_H
