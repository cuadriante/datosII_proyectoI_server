//
// Created by cuadriante on 8/9/21.
//

#include "../Headers/Protocol.h"

void Protocol::objectToPtree(string obj) {
    ptree pt;
    pt.put("object", obj);
    ptreeToJson(pt);
}

void Protocol::ptreeToJson(ptree ptree1) {
    ostringstream buff;
    write_json(buff, ptree1, false);
    string json = buff.str();
    cout << json << endl;
    sendJsonToClient(json);

}

void Protocol::sendJsonToClient(string json) {
        serverSocket->setMessage(json.c_str());

}

Protocol::Protocol(ServerSocket *server) {
    serverSocket = server;
}
