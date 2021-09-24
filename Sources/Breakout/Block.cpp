//
// Created by cuadriante on 8/9/21.
//

#include "../../Headers/Breakout/Block.h"

Block::Block(int id, int type, int posx, int posy) {
    this-> id = id;
    this-> type = type;
    this-> posx = posx;
    this-> posy = posy;


}

int Block::getHitsToBreak() const {
    return hitsToBreak;
}

void Block::setHitsToBreak(int hitsToBreak) {
    Block::hitsToBreak = hitsToBreak;
}

int Block::getId() const {
    return id;
}

int Block::getPosX() const {
    return posx;
}

void Block::setPosx(int posx) {
    Block::posx = posx;
}

int Block::getPosY() const {
    return posy;
}

void Block::setPosy(int posy) {
    Block::posy = posy;
}

int Block::getType() const {
    return type;
}

