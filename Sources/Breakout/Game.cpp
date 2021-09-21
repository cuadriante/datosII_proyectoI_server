//
// Created by cuadriante on 20/9/21.
//

#include "../../Headers/Breakout/Game.h"

Game::Game() {
    int id = 0;
    int x = 0;
    int y = 0;
    Block * block = new Block(id++, 31, x, y);
    blockList.push_back(block);
    for (int row = 0; row < 5; row++){
        for(int col = 0; col < 12; col++){
            Block * block = new Block(id++, 31, x, y);
            blockList.push_back(block);
            x = x + 20;
        }
        x = 0;
        y = y + 5;
    }

}


const vector<Block *> & Game::getBlockList() const {
    return blockList;
}

