//
// Created by cuadriante on 8/9/21.
//
//
//#include "../Headers/Protocol.h"
//
//Protocol::Protocol(Socket *server) {
//    serverSocket = server;
//}
//
//void Protocol::objectToPtree(string obj) {
//    ptree pt;
//    pt.put("object", obj);
//    ptreeToJson(pt);
//}
//
//string Protocol::ptreeToJson(ptree ptree1) {
//    ostringstream buff;
//    write_json(buff, ptree1, false);
//    string json = buff.str();
//    //cout << json << endl;
//    //sendStringToSocket(json);
//    return json;
//}
//
//ptree* Protocol::JsonToPtree(string json){
//    ptree pt;
//    istringstream is (json);
//    read_json (is, pt);
//    return &pt;
//}
//
//
//void Protocol::sendStringToSocket(string json) {
//    serverSocket->sendMessageToAll(json.c_str());
//}
//
//string Protocol::receiveStringFromSocket(string json) {
//
//        return serverSocket->readMessage();
//
//}
