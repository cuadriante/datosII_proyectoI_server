//
// Created by cuadriante on 14/9/21.
//

#include "../Headers/ServerListener.h"
#include "../Headers/Socket.h"

bool ServerListener::start(){
    // create descriptor
    serverSocketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocketId <= 0){
        cout << "Error: Could not create socket" << endl;
        return false;
    }

    int opt = 1;

    if (setsockopt(serverSocketId, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
      cout << "Error: Could not set socket options." << endl;
      return false;
    }

    serverSocketInfo.sin_family = AF_INET;
    serverSocketInfo.sin_addr.s_addr = INADDR_ANY; // accepts anything
    serverSocketInfo.sin_port = htons(serverSocketPort);
    memset(&serverSocketInfo.sin_zero, 0, sizeof(serverSocketInfo.sin_zero)); //used to clean attribute, access directly to its direction

    if((bind(serverSocketId, (struct sockaddr *)&serverSocketInfo, sizeof(serverSocketInfo)) < 0)){
        cout << "Error: Could not bind." << endl;
        return false;
    }

    if (listen(serverSocketId, maxConnectedClients)){
        cout << "Error: Listen unsuccessful." << endl;
        return false;
    }

    // server socket created successfully.
    return true;

}

void ServerListener::waitForConnections() {
    while(true){
        cout << "Waiting for client to connect." << endl;
        int clientSocketId = accept(serverSocketId, (struct sockaddr *)&serverSocketInfo, (socklen_t *)&serverSocketInfoLen);
        if(clientSocketId< 0){
            cout << "Error: could not accept client." << endl;
            break;
        }
        else {
            //clients.push_back(data.descriptor);
            cout << "Client connected successfully." << endl;

            pthread_t thread;
            pthread_create(&thread, 0, ServerListener::startClientSession, (void *)&clientSocketId);
            pthread_detach(thread);
        }
    }
}

void * ServerListener::startClientSession(void * psocketId) {
    int * socketId =  (int *)psocketId;
    cout << "socketId: " << socketId << endl;

    Socket socket = Socket(*socketId);
    sleep(1);



    socket.sendMessage("juajua");




    close(*socketId);
    pthread_exit(NULL);

}