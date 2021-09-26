//
// Created by cuadriante on 25/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_PLAYERINFO_H
#define DATOSII_PROYECTOI_SERVER_PLAYERINFO_H


#include "Breakout/PlayerBar.h"

class PlayerInfo {
private:
    int socketId;
    int pointsGained = 0;
    void * gameInfo;
    PlayerBar * playerBar;

public:

    PlayerInfo();

    int getSocketId() const;

    void setSocketId(int socketId);

    int getPointsGained() const;

    void setPointsGained(int pointGained);

    void *getGameInfo() const;

    void setGameInfo(void *gameInfo);

    PlayerBar *getPlayerBar() const;

};


#endif //DATOSII_PROYECTOI_SERVER_PLAYERINFO_H
