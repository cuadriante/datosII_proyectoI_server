//
// Created by cuadriante on 2/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_SOCKET_H
#define DATOSII_PROYECTOI_SERVER_SOCKET_H

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
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class Socket {
private:
    int socketId;
public:
    Socket(int socketId);
    string readMessage();
    void sendMessage(string message);
    void sendPtree(ptree * ptree);
    ptree * readPtree();

private:
    int descriptor; // se utiliza para identificar los sistemas
    const int maxConnectedClients = 4;
    static const int bufferSize = 1024;
    sockaddr_in info;
    vector<int> clients; // stores connected clients
    bool create_socket();
    bool bind_kernel(); //bind with port, establish maximum client quantity
    static void* ClientController(void*);


};


#endif //DATOSII_PROYECTOI_SERVER_SOCKET_H
