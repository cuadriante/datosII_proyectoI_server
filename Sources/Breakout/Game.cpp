//
// Created by cuadriante on 20/9/21.
//

#include "../../Headers/Breakout/Game.h"

Game::Game() {
    int id = 0;
    int x = 7;
    int y = 0;
    Block * block = new Block(id++, 31, x, y);
    blockList.push_back(block);
    for (int row = 0; row < 12; row++){
        for(int col = 0; col < 5; col++){
            Block * block = new Block(id++, 31, x, y);
            blockList.push_back(block);
            x = x + 120;
        }
        x = 7;
        y = y + 20;
    }

    ball = new Ball();
    ball->setX(300);
    ball->setY(300);

}


const vector<Block *> & Game::getBlockList() const {
    return blockList;
}

Ball *Game::getBall() const {
    return ball;
}

