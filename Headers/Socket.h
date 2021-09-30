//
// Created by cuadriante on 2/9/21.
//

/** @brief Socket class used for communication within socket.

    Handles sending and receiving messages to and from socket.
    @author cuadriante
    @date September 2021
    */


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
#include "Command.h"
#include <chrono>

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class Socket {

private:
    int socketId; /**<initial socket id*/
    string buffer; /**<initial buffer*/
    static const int bufferSize = 1024; /**<buffer size*/

public:
    /** Constructor.
     *
     * @param socketId
     */
    Socket(int socketId);
    /** Reads json message coming from server.
     *
     * @return
     */
    string readMessage();
    /** Sends message to server.
     *
     * @param message
     */
    void sendMessage(string message);
    /** Send Ptree object.
     *
     * @param ptree
     */
    void sendPtree(ptree * ptree);
    /** Reads Ptree object.
     *
     * @return
     */
    ptree * readPtree();
    /** Sends command to server.
     *
     * @param command
     */
    void sendCommand(Command &command);
    /**Reads command from server.
     *
     * @return
     */
    Command *readCommand();
};


#endif //DATOSII_PROYECTOI_SERVER_SOCKET_H
