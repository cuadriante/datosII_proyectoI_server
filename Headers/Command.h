//
// Created by cuadriante on 19/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_COMMAND_H
#define DATOSII_PROYECTOI_SERVER_COMMAND_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree//json_parser.hpp>


using boost::property_tree::ptree;
using namespace std;

class Command {
public:
    static const int ACTION_NONE = 0;
    // to player
    static const int ACTION_MOVE_PLAYER = 11;
    static const int ACTION_MOVE_BALL = 12;
    static const int ACTION_MOVE_BLOCK = 13;
    static const int ACTION_DELETE_BLOCK = 14;
    static const int ACTION_SET_SCORE = 15;
    static const int ACTION_CREATE_BLOCK = 16;
    // to server
    static const int ACTION_MOVE_LEFT = 21;
    static const int ACTION_MOVE_RIGHT = 22;
    // block types
    static const int BLOCK_TYPE_COMMON = 31;
    static const int BLOCK_TYPE_DOUBLE = 32;
    static const int BLOCK_TYPE_TRIPLE = 33;
    static const int BLOCK_TYPE_INTERNAL = 34;
    static const int BLOCK_TYPE_DEEP = 35;
    static const int BLOCK_TYPE_SURPRISE = 36;


    void writeToPtree(ptree * pt);
    void readFromPtree(ptree * pt);
    void setAction(int action);
    void setPosX(int newPlayerX);
    int getAction();
    int getPosX();
    int getType() const;
    int getPosY() const;
    void setPosY(int posY);
    const string &getName() const;
    void setName(const string &name);

private:
    int id;
public:
    int getId() const;

    void setId(int id);

private:
    int action;
    int posX;
    int posY;
    string name;
    int type;

};


#endif //DATOSII_PROYECTOI_SERVER_COMMAND_H
