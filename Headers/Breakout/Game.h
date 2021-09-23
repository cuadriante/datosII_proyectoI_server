//
// Created by cuadriante on 20/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAME_H
#define DATOSII_PROYECTOI_SERVER_GAME_H


#include "Block.h"
#include "Ball.h"
#include <vector>

using namespace std;

class Game {
private:
    vector<Block *> blockList;
    Ball * ball;

public:
    Game();

    const vector<Block *> & getBlockList() const;

    void setBlockList(const vector<Block> &blockList);

    Ball *getBall() const;
};

static Game GAME_SINGLETON;

#endif //DATOSII_PROYECTOI_SERVER_GAME_H
