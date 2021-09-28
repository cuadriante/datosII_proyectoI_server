//
// Created by cuadriante on 25/9/21.
//

#include "../Headers/PlayerInfo.h"

PlayerInfo::PlayerInfo() {
    playerBar = new PlayerBar();
}

int PlayerInfo::getSocketId() const {
    return socketId;
}

void PlayerInfo::setSocketId(int socketId) {
    PlayerInfo::socketId = socketId;
}

int PlayerInfo::getPointsGained() const {
    return pointsGained;
}

void PlayerInfo::setPointsGained(int pointGained) {
    PlayerInfo::pointsGained = pointGained;
}

void *PlayerInfo::getGameInfo() const {
    return gameInfo;
}

void PlayerInfo::setGameInfo(void *gameInfo) {
    PlayerInfo::gameInfo = gameInfo;
}

PlayerBar *PlayerInfo::getPlayerBar() const {
    return playerBar;
}

Socket *PlayerInfo::getSocket() const {
    return socket;
}

void PlayerInfo::setSocket(Socket *socket) {
    PlayerInfo::socket = socket;
}


