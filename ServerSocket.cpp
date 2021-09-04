//
// Created by cuadriante on 2/9/21.
//

#include "ServerSocket.h"

ServerSocket::ServerSocket() {

}

void ServerSocket::run() {
    if (!create_socket()) {
        throw string("Error: could not creating socket.");
    }
    if (!bind_kernel()){
        throw string("Error: could not binding kernel.");
    }
    while(true){
        dataSocket data;
        socklen_t size = sizeof(data.info);
        cout << "Waiting for client to connect." << endl;
        data.descriptor = accept(descriptor, (sockaddr *)&data.info, &size);
        if(data.descriptor < 0){
            cout << "Error: could not accept client." << endl;
            break;
        }
        else {
            clients.push_back(data.descriptor);
            cout << "Client connected successfully.";
            pthread_t thread;
            pthread_create(&thread, 0, ServerSocket::ClientController, (void *)&data);
            pthread_detach(thread);
        }
    }
    close(descriptor);

}

void ServerSocket::setMessage(const char *msn) {
    int i;
    for(int i = 0; i < clients.size(); i++){ // sends message to all clients
        send(clients[i], msn, strlen(msn), 0);
    }
}

bool ServerSocket::create_socket() {
    // create descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (descriptor < 0){
        return false;
    }

    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY; // accepts anything
    info.sin_port = htons(4050);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero)); //used to clean attribute, access directly to its direction
    return true;
}

bool ServerSocket::bind_kernel() {
    if((bind(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)) < 0)){
        return false;
    } // listen for client
    listen(descriptor, maxConnectedClients); //establish maximum number of clients
    return true;
}

void *ServerSocket::ClientController(void *obj) {
    dataSocket* data = (dataSocket *)obj;
    while(true){
        string message;
        char buffer[bufferSize] = {0}; //number to be defined
        while(1){
            memset(buffer, 0, bufferSize);
            int bytes = recv(data->descriptor, buffer, bufferSize, 0);
            message.append(buffer, bytes);
            if (bytes <= 0){ //reads message
                close(data->descriptor);
                pthread_exit(NULL);
            }
            if (bytes < bufferSize){ // stops reading
                break;
            }
        }
        cout << message << endl;
        close(data->descriptor);
        pthread_exit(NULL);
    }

}
