//
// Created by cuadriante on 14/9/21.
//

#include <thread>
#include "../Headers/ServerListener.h"
#include "../Headers/Socket.h"
#include "../Headers/Command.h"
#include "../Headers/Breakout/Block.h"
#include "../Headers/Breakout/GameInfo.h"
#include <fcntl.h>


bool ServerListener::start() {
    // create descriptor
    serverSocketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocketId <= 0) {
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
    memset(&serverSocketInfo.sin_zero, 0,
           sizeof(serverSocketInfo.sin_zero)); //used to clean attribute, access directly to its direction

    if ((bind(serverSocketId, (struct sockaddr *) &serverSocketInfo, sizeof(serverSocketInfo)) < 0)) {
        cout << "Error: Could not bind." << endl;
        return false;
    }

    if (listen(serverSocketId, maxConnectedClients)) {
        cout << "Error: Listen unsuccessful." << endl;
        return false;
    }

    // server socket created successfully.
    return true;

}

[[noreturn]] void ServerListener::waitForConnections(GameInfo *gameInfo) {
    while (true) {
        cout << "Waiting for client to connect." << endl;
        int clientSocketId = accept(serverSocketId, (struct sockaddr *) &serverSocketInfo,
                                    (socklen_t *) &serverSocketInfoLen);
        if (clientSocketId < 0) {
            cout << "Warning: could not accept newest client." << endl;
        } else {
            //clients.push_back(data.descriptor);
            cout << "Client connected successfully." << endl;

            // Put the socket in non-blocking mode:
            if (fcntl(clientSocketId, F_SETFL, fcntl(clientSocketId, F_GETFL) | O_NONBLOCK) < 0) {
                // handle error
                cout << "Error: Socket is nonblocking.";
            }
            PlayerInfo *playerInfo = new PlayerInfo();
            playerInfo->setSocketId(clientSocketId);

            playerInfo->setGameInfo(gameInfo);
            pthread_t thread;
            pthread_create(&thread, 0, ServerListener::startPLayerSession, (void *) playerInfo);
            pthread_detach(thread);
        }
    }
}

[[noreturn]] void *ServerListener::startPLayerSession(void *pplayerInfo) {
    PlayerInfo *playerInfo = (PlayerInfo *) pplayerInfo;
    int socketId = playerInfo->getSocketId();
    GameInfo *gameInfo = (GameInfo *) (playerInfo->getGameInfo());
    gameInfo->addPlayer(playerInfo);
    cout << "socketId: " << socketId << endl;

    Socket * socket = new Socket(socketId);
    playerInfo->setSocket(socket);
    bool exit = false;

    while (!exit) {

        Command *cmd = socket->readCommand();
        if (cmd != NULL) {
            switch (cmd->getAction()) {
                case (Command::ACTION_END_GAME): {
                    exit == true;
                    break;
                }
                case (Command::ACTION_START_GAME): {
                    for (Block *b: gameInfo->getBlockList()) {
                        Command c;
                        c.setAction(c.ACTION_CREATE_BLOCK);
                        c.setId(b->getId());
                        c.setPosX(b->getPosX());
                        c.setPosY(b->getPosY());
                        c.setType(b->getType());
                        socket->sendCommand(c);
                    }
                    Command c;
                    c.setAction(c.ACTION_MOVE_BALL);
                    c.setPosX(gameInfo->getBall()->getX());
                    c.setPosY(gameInfo->getBall()->getY());

                    socket->sendCommand(c);

                    c.setAction(c.ACTION_MOVE_PLAYER);
                    c.setPosX(300);
                    c.setPosY(550);
                    c.setSize(100);

                    socket->sendCommand(c);
                    break;
                }
                case (Command::ACTION_MOVE_PLAYER): {
                    int x = cmd->getPosX();
                    int y = cmd->getPosY();
                    if (x < 0) {
                        x = 0;
                    }
                    playerInfo->getPlayerBar()->setPosX(x);
                    playerInfo->getPlayerBar()->setPosY(y);
                    //cout << "Client moved to x: " << x << " y: " << y << endl;
                    //todo: send new pos to all clients except one
//                    Command c;
//                    c.setAction(c.ACTION_MOVE_PLAYER);
//                    c.setPosX(x);
//                    c.setPosY(y);
//                    c.setSize(playerInfo->getPlayerBar()->getSize());
//                    socket.sendCommand(c);
                    break;
                }
            }
        }
    }

    delete socket;
    gameInfo->removePlayer(playerInfo);
    close(socketId);
    pthread_exit(NULL);

}
