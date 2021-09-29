//
// Created by cuadriante on 29/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAMELOOP_H
#define DATOSII_PROYECTOI_SERVER_GAMELOOP_H

#include "GameModeSettings.h"
#include "GameInfo.h"

class GameLoop {
private:
    GameInfo * gameInfo;
public:
    GameLoop(GameInfo *gameInfo);
    static bool collide(int x1, int x2, int y1, int y2, int w, int z);

    [[noreturn]] static void *gameLoop(void *pgame);

    static long currentTimeInMillis();

    static void checkBlockCollision(GameModeSettings gameModeSettings, GameInfo *gameInfo, Ball *ball);

    static void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball);

    static void checkForBallOutOfBounds(Ball *ball);
};


#endif //DATOSII_PROYECTOI_SERVER_GAMELOOP_H
