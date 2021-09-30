//
// Created by cuadriante on 29/9/21.
//

#include "../../Headers/Breakout/GameModeSettings.h"

GameModeSettings::GameModeSettings(GameInfo *gameInfo) {
    this->gameInfo = gameInfo;
}

void GameModeSettings::sendPointsGained(int type) {
    int pointsGained;
    switch (type) {
        case Command::BLOCK_TYPE_COMMON: { //common
            pointsGained = 10;
            break;
        }
        case Command::BLOCK_TYPE_DOUBLE: { //double
            pointsGained = 15;
            break;
        }
        case Command::BLOCK_TYPE_TRIPLE: { //triple
            pointsGained = 20;
            break;
        }
        case Command::BLOCK_TYPE_INTERNAL: { //internal
            if (gameInfo->getDepthLevel() <= 0) {
                pointsGained = 0;
            } else {
                pointsGained = 30;
            }

            break;
        }
        case Command::BLOCK_TYPE_DEEP: { //deep
            pointsGained = 0;
            break;
        }
        case Command::BLOCK_TYPE_SURPRISE: { //surprise
            pointsGained = 0;
            break;
        }
    }
    Command cmd;
    cmd.setAction(cmd.ACTION_SET_SCORE);
    cmd.setSize(pointsGained);

    for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
        playerInfo->getSocket()->sendCommand(cmd);
    }
}

void GameModeSettings::createSurprise() {
    int surprise = rand() % 5 + 1;
    int currentVx = gameInfo->getBall()->getVx();
    int currentVy = gameInfo->getBall()->getVy();

    switch (surprise) {
        case 1: { // increase velocity
            gameInfo->getBall()->setVy(currentVy + (rand() % 10));
            gameInfo->getBall()->setVx(currentVx + (rand() % 10));
            cout << "INCREASE VELOCITY" << endl;
            cout << "Vx: " << gameInfo->getBall()->getVx() << endl;
            cout << "Vy: " << gameInfo->getBall()->getVy() << endl;
            break;
        }
        case 2: { //decrease velocity
            gameInfo->getBall()->setVy(currentVy - (rand() % 10));
            gameInfo->getBall()->setVx(currentVx - (rand() % 10));
            cout << "DECREASE VELOCITY" << endl;
            cout << "Vx: " << gameInfo->getBall()->getVx() << endl;
            cout << "Vy: " << gameInfo->getBall()->getVy() << endl;
            break;
        }
        case 3: { // increase player size
            cout << "INCREASE PLAYER BAR SIZE" << endl;
            Command c;
            c.setAction(c.ACTION_SET_PLAYER_BAR_SIZE);
            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                int currentSize = playerInfo->getPlayerBar()->getSize();
                playerInfo->getPlayerBar()->setSize(currentSize + (rand() % 20));
                if (playerInfo->getPlayerBar()->getSize() >= 150) {
                    playerInfo->getPlayerBar()->setSize(150);
                }
                c.setSize(playerInfo->getPlayerBar()->getSize());
                playerInfo->getSocket()->sendCommand(c);
                cout << "Size: " << playerInfo->getPlayerBar()->getSize() << endl;
            }

            break;
        }
        case 4: { // decrease player size
            cout << "DECREASE PLAYER BAR SIZE" << endl;
            Command c;
            c.setAction(c.ACTION_SET_PLAYER_BAR_SIZE);
            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                int currentSize = playerInfo->getPlayerBar()->getSize();
                playerInfo->getPlayerBar()->setSize(currentSize - (rand() % 20));
                if (playerInfo->getPlayerBar()->getSize() <= 20) {
                    playerInfo->getPlayerBar()->setSize(20);
                }
                c.setSize(playerInfo->getPlayerBar()->getSize());
                playerInfo->getSocket()->sendCommand(c);
                cout << "Size: " << playerInfo->getPlayerBar()->getSize() << endl;
            }
            break;
        }
        case 5: { //tbd
            cout << "CHANGE DEPTH LEVEL TO 0" << endl;
            gameInfo->setDepthLevel(0);
            break;
        }
    }
    for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {

    }
}
