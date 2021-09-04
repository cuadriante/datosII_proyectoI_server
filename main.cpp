#include "ServerSocket.h"

ServerSocket* server;
void * serverRun(void *){
    try {
        server->run();
    } catch (string ex) {
        cout << ex << endl;
    }
    pthread_exit(NULL);
}

int main() {
    server = new ServerSocket;
    pthread_t serverThread;
    pthread_create(&serverThread, 0, serverRun, NULL);
    pthread_detach(serverThread);

    //Test: send messages from server to client
    string json = "Holi soy el servidor."; // !! esto es lo que hay que poner como un json de verdad proximamente
    while(1){
        string msn;
        cin >> msn;
        if(msn == "exit"){
            break;
        }
        server->setMessage(json.c_str());

    }
    delete server;
    return 0;
}
