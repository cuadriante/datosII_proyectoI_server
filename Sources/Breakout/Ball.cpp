//
// Created by cuadriante on 22/9/21.
//

#include "../../Headers/Breakout/Ball.h"

int Ball::getX() const {
    return x;
}

void Ball::setX(int x) {
    Ball::x = x;
}

int Ball::getY() const {
    return y;
}

void Ball::setY(int y) {
    Ball::y = y;
}

int Ball::getVx() const {
    return Vx;
}

void Ball::setVx(int vx) {
    Vx = vx;
}

int Ball::getVy() const {
    return Vy;
}

void Ball::setVy(int vy) {
    Vy = vy;
}
