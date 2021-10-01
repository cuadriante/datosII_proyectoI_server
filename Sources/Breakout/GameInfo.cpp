//
// Created by cuadriante on 20/9/21.
//

#include <cstdio>
#include <cstdlib>
#include "../../Headers/Breakout/GameInfo.h"

GameInfo::GameInfo() {
    int id = 0;
    int x = 7;
    int y = 0;
    
    for (int row = 0; row < 12; row++){
        for(int col = 0; col < 5; col++){
            //int type = 36;
            int type = (rand() %6) + 31;
            Block * block = new Block(id++, type, x, y);
            block->setHitsByType(type);
            blockList.push_back(block);
            x = x + 120;
        }
        x = 7;
        y = y + 20;
    }

    ball = new Ball();
    ball->setX(25);
    ball->setY(720);
    ball->setVx(15);
    ball->setVy(-15);

}


const vector<Block *> & GameInfo::getBlockList() const {
    return blockList;
}

Ball *GameInfo::getBall() const {
    return ball;
}

const vector<PlayerInfo *> & GameInfo::getPlayerList() const {
    return playerList;
}

void GameInfo::removePlayer(PlayerInfo *playerInfo) {
    //playerList.erase(playerList.cbegin());

}

void GameInfo::addPlayer(PlayerInfo *playerInfo) {
    playerList.push_back(playerInfo);

}

int GameInfo::getDepthLevel() const {
    return depthLevel;
}

void GameInfo::setDepthLevel(int depthLevel) {
    this->depthLevel = depthLevel;
}

int GameInfo::getVisibleBlocks() const {
    return visibleBlocks;
}

void GameInfo::setVisibleBlocks(int visibleBlocks) {
    GameInfo::visibleBlocks = visibleBlocks;
}


