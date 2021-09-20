//
// Created by cuadriante on 2/9/21.
//

#include "../Headers/Socket.h"

Socket::Socket(int socketId) {
    this->socketId = socketId;

}

void Socket::sendMessage(string message) {
    send(socketId, message.c_str(), message.size(), 0);
}

string Socket::readMessage() {
    char buffer[bufferSize] = {0};
    for (int i = 0; i < clients.size(); i++){
        read(clients[i], buffer, bufferSize);
    }
    return buffer;
}

void Socket::sendPtree(ptree *ptree) {
    ostringstream buff;
    write_json(buff, *ptree, false);
    string json = buff.str();
    sendMessage(json);
}

ptree * Socket::readPtree() {
    string json = readMessage();
    ptree pt;
    istringstream is (json);
    read_json (is, pt);
    return &pt;

}

