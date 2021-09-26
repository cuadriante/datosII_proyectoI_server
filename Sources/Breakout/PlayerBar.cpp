//
// Created by cuadriante on 25/9/21.
//

#include "../../Headers/Breakout/PlayerBar.h"

int PlayerBar::getPosX() const {
    return posX;
}

void PlayerBar::setPosX(int posX) {
    PlayerBar::posX = posX;
}

int PlayerBar::getPosY() const {
    return posY;
}

void PlayerBar::setPosY(int posY) {
    PlayerBar::posY = posY;
}

int PlayerBar::getSize() const {
    return size;
}

void PlayerBar::setSize(int size) {
    PlayerBar::size = size;
}
