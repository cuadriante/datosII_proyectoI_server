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


static const int BLOCK_TYPE_COMMON = 31;
static const int BLOCK_TYPE_DOUBLE = 32;
static const int BLOCK_TYPE_TRIPLE = 33;
static const int BLOCK_TYPE_INTERNAL = 34;
static const int BLOCK_TYPE_DEEP = 35;
static const int BLOCK_TYPE_SURPRISE = 36;


void Block::setHitsByType(int type) {
    int hits = 0;
    switch (type){
        case 31: { //common
            hits = 1;
            break;
        }
        case 32: { //double
            hits = 2;
            break;
        }
        case 33: { //triple
            hits = 3;
            break;
        }
        case 34: { //internal
            hits = 1;
            break;
        }
        case 35: { //deep
            hits = 1000;
            break;
        }
        case 36: { //surprise
            hits = 2;
            break;
        }
    }
    Block::hitsToBreak = hits;
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

