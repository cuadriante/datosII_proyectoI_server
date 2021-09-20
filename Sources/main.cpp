#include "../Headers/Socket.h"
#include "../Headers/Protocol.h"
#include "../Headers/ServerListener.h"
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>

//Socket* server;
//void * serverRun(void *){
//    try {
//        server->run();
//    } catch (string ex) {
//        cout << ex << endl;
//    }
//    pthread_exit(NULL);
//}

int main() {
    ServerListener serverListener;
    if (serverListener.start()){
        serverListener.waitForConnections();
    }
//    server = new Socket(0);
//    pthread_t serverThread;
//    pthread_create(&serverThread, 0, serverRun, NULL);
//    pthread_detach(serverThread);
//
//
//
//    while(1){
//
//    }
    //delete serverListener;
    return 0;
}
