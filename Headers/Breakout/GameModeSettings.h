//
// Created by cuadriante on 29/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H
#define DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H


#include "../Command.h"
#include "../Breakout/GameInfo.h"

class GameModeSettings {
private:
    GameInfo * gameInfo;
public:
    GameModeSettings(GameInfo * gameInfo);
    void sendPointsGained(int type);

    void checkBlockCollision(Ball *ball);

    void createSurprise();
};


#endif //DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H
