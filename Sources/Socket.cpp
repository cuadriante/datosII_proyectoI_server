//
// Created by cuadriante on 2/9/21.
//

#include "../Headers/Socket.h"

Socket::Socket(int socketId) {
    this->socketId = socketId;

}

void Socket::sendMessage(string message) {
    //message.append("\n");
    send(socketId, message.c_str(), message.size(), 0);
}

string Socket::readMessage() {
    //char buffer[bufferSize] = {0}; //number to be defined
    string output(bufferSize, 0);


    int bytes_received = read(socketId, &output[0], bufferSize-1);
    if (bytes_received>0) {
        output.resize(bytes_received);
        output[bytes_received] = 0;
        buffer.append(output);

    }

    int pos = buffer.find("\n");
    if (pos > 0) {
        string msg = buffer.substr(0, pos);
        buffer.erase(0, pos + 1);
        //cout << "output: " << output << endl;
        //cout << "message: " << msg << endl;
        //cout << "buffer: " << buffer << endl;
        return msg;
    }

    return "";
}


void Socket::sendPtree(ptree *ptree) {
    ostringstream buff;
    write_json(buff, *ptree, false);
    string json = buff.str();
    sendMessage(json);
}

ptree * Socket::readPtree() {
    string json = readMessage();
    if (json.empty()){
        return NULL;
    }
    //cout << json << endl;
    //json = "{\"action\":\"1\",\"posX\":\"200\"}";
    ptree * pt = new ptree();
    istringstream is (json);
    read_json (is, *pt);
    return pt;

}

void Socket::sendCommand(Command &command) {
    ptree * pt = new ptree();
    pt->put("action", command.getAction());
    pt->put("id", command.getId());
    pt->put("posX", command.getPosX());
    pt->put("posY", command.getPosY());
    pt->put("type", command.getType());
    //pt->put("name", command.getName());
    pt->put("size", command.getSize());
    sendPtree(pt);
}

Command * Socket::readCommand(){
    ptree * pt = readPtree();
    if (pt == NULL){
        return NULL;
    }
    Command * c = new Command();
    c->setAction(pt->get<int>("action", 0));
    c->setId(pt->get<int>("id", 0));
    c->setPosX(pt->get<int>("posX", 0));
    c->setPosY(pt->get<int>("posY", 0));
    //c->setName(pt->get<string>("name", 0));
    c->setSize(pt->get<int>("size", 0));
    return c;
}

