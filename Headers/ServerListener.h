//
// Created by cuadriante on 14/9/21.
//

/** @brief ServerListener class used for sending messages to socket.

    @author cuadriante
    @date September 2021
    */


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
#include <chrono>
#include "Breakout/GameInfo.h"

using namespace std;

class ServerListener {
private:
    int serverSocketId; /**<initial server socket id*/
    struct sockaddr_in serverSocketInfo; /**<initial server socket information*/
    int serverSocketInfoLen = sizeof(serverSocketInfo); /**<initial length of server socket information*/
    int serverSocketPort = 4050; /**<initial port*/
    int maxConnectedClients = 5; /**<initial maximum quantity of connected clients in server*/
public:
    /** Sets and binds socket kernel.
     *
     * @return
     */
    bool start();
    /** Waits for client socket to connect and starts game if successful.
     *
     * @param gameInfo
     */
    [[noreturn]] void waitForConnections(GameInfo *gameInfo);
    /** Starts game in client socket if succesfully connected.
     *
     * @param pplayerInfo
     * @return
     */
    [[noreturn]] static void * startPLayerSession(void * pplayerInfo);
};


#endif //DATOSII_PROYECTOI_SERVER_SERVERLISTENER_H
