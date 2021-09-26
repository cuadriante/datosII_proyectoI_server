//
// Created by cuadriante on 20/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAMEINFO_H
#define DATOSII_PROYECTOI_SERVER_GAMEINFO_H


#include "Block.h"
#include "Ball.h"
#include "../PlayerInfo.h"
#include <vector>

using namespace std;

class GameInfo {
private:
    vector<PlayerInfo *> playerList;
    vector<Block *> blockList;
    Ball * ball;

public:
    GameInfo();

    const vector<Block *> & getBlockList() const;

    void setBlockList(const vector<Block> &blockList);

    Ball *getBall() const;

    const vector<PlayerInfo *> & getPlayerList() const;

    void removePlayer(PlayerInfo * playerInfo);

    void addPlayer(PlayerInfo * playerInfo);



};

//static GameInfo GAME_SINGLETON;

#endif //DATOSII_PROYECTOI_SERVER_GAMEINFO_H
