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
#include "Socket.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class Protocol {

public:
    Protocol();

    void objectToPtree(string obj);
    string ptreeToJson(ptree ptree1);
    void sendStringToSocket(string json);
    string receiveStringFromSocket(string json);

    ptree* JsonToPtree(string json);
};


#endif //DATOSII_PROYECTOI_SERVER_PROTOCOL_H
