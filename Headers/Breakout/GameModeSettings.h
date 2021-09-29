//
// Created by cuadriante on 29/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H
#define DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H

/** @brief GameModeSettings class used for storing game mode information.

    @author cuadriante
    @date September 2021
    */

#include "../Command.h"
#include "../Breakout/GameInfo.h"

class GameModeSettings {
private:
    GameInfo * gameInfo; /**<initial gameInfo*/
public:
    /** Constructor.
     *
     * @param gameInfo
     */
    GameModeSettings(GameInfo * gameInfo);
    /** Sends gained points to client.
     *
     * @param type
     */
    void sendPointsGained(int type);
    /** Sets surprise when surprise block is deleted.
     *
     */
    void createSurprise();
};


#endif //DATOSII_PROYECTOI_SERVER_GAMEMODESETTINGS_H
