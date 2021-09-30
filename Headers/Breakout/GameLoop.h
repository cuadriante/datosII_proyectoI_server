//
// Created by cuadriante on 29/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAMELOOP_H
#define DATOSII_PROYECTOI_SERVER_GAMELOOP_H

#include "GameModeSettings.h"
#include "GameInfo.h"

/** @brief GameLoop class used for thread implementation.

    @author cuadriante
    @date September 2021
    */

class GameLoop {
private:
    GameInfo * gameInfo; /**<initial game info*/
public:
    /** Constructor.
     *
     * @param gameInfo
     */
    GameLoop(GameInfo *gameInfo);
    /**Checks for collision with given parameters.
     *
     * @param x1
     * @param x2
     * @param y1
     * @param y2
     * @param w
     * @param z
     * @return
     */
    static bool collide(int x1, int x2, int y1, int y2, int w, int z);
    /** Continuous loop for game movement.
     *
     * @param pgame
     * @return
     */
    [[noreturn]] static void *gameLoop(void *pgame);
    /** Returns current time in milliseconds.
     *
     * @return
     */
    static long currentTimeInMillis();
    /** Checks ball collision with blocks.
     *
     * @param ball
     */
    static void checkBlockCollision(GameModeSettings gameModeSettings, GameInfo *gameInfo, Ball *ball);
    /** Checks ball collision with player bar.
     *
     * @param gameInfo
     * @param ball
     */
    static void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball);
    /** Checks for ball out of bounds.
     *
     * @param ball
     */
    static void checkForBallOutOfBounds(const GameInfo *gameInfo, Ball *ball);
};


#endif //DATOSII_PROYECTOI_SERVER_GAMELOOP_H
