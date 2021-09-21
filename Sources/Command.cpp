//
// Created by cuadriante on 19/9/21.
//

#include "../Headers/Command.h"

void Command::writeToPtree(ptree *pt) {
    pt->put("action", action);
    pt->put("posX", posX);
}

void Command::readFromPtree(ptree *pt) {
    action = pt->get<int>("action", 0);
    posX = pt->get<int>("posX", 0);
}

void Command::setAction(int action) {
    this->action = action;

}

void Command::setPosX(int newPlayerX) {
    this->posX = newPlayerX;

}

int Command::getAction() {
    return action;

}

int Command::getPosX() {
    return posX;

}

int Command::getPosY() const {
    return posY;
}

void Command::setPosY(int posY) {
    Command::posY = posY;
}

const string &Command::getName() const {
    return name;
}

void Command::setName(const string &name) {
    Command::name = name;
}

int Command::getType() const {
    return type;
}

int Command::getId() const {
    return id;
}

void Command::setId(int id) {
    Command::id = id;
}
