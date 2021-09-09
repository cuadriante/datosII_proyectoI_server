//
// Created by cuadriante on 8/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_PROTOCOL_H
#define DATOSII_PROYECTOI_SERVER_PROTOCOL_H
#include <iostream>
#include <boost/property_tree//json_parser.hpp>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>
#include "ServerSocket.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class Protocol {
private:

    ServerSocket * serverSocket;

public:
    Protocol(ServerSocket * server);
    void objectToPtree(string obj);
    void ptreeToJson(ptree ptree1);
    void sendJsonToClient(string json);

};


#endif //DATOSII_PROYECTOI_SERVER_PROTOCOL_H
