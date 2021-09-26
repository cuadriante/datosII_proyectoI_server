//
// Created by cuadriante on 25/9/21.
//

#include "../Headers/PlayerInfo.h"

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
