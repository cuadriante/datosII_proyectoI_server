#include "../Headers/ServerSocket.h"
#include "../Headers/Protocol.h"
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>

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
    ServerSocket * serverPointer = server;
    pthread_t serverThread;
    pthread_create(&serverThread, 0, serverRun, NULL);
    pthread_detach(serverThread);

    Protocol protocol(serverPointer);

    //Test: send messages from server to client
    string json = "start"; // !! esto es lo que hay que poner como un command de verdad proximamente
    //protocol.objectToPtree(json);
    while(1){

        string msn;
        cin >> msn;

 //       protocol.objectToPtree(json);
//        if(msn == "exit"){
//            break;
//        }
//        server->sendMessageToAll(json.c_str());

    }
    delete server;
    return 0;
}
