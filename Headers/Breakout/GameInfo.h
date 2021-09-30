//
// Created by cuadriante on 20/9/21.
//

/** @brief GameInfo class used for storing game information.

    @author cuadriante
    @date September 2021
    */


#ifndef DATOSII_PROYECTOI_SERVER_GAMEINFO_H
#define DATOSII_PROYECTOI_SERVER_GAMEINFO_H


#include "Block.h"
#include "Ball.h"
#include "../PlayerInfo.h"
#include <vector>

using namespace std;

class GameInfo {
private:
    vector<PlayerInfo *> playerList; /**<initial player list vector*/
    vector<Block *> blockList; /**<initial block list vector*/
    Ball * ball; /**<initial ball*/
    int depthLevel = 0; /**<initial depth level*/
    int visibleBlocks = 60;

public:
    /** Constructor. Initializes game in client.
     *
     */
    GameInfo();
    /** Returns block list vector.
     *
     * @return
     */
    const vector<Block *> & getBlockList() const;

    /** Returns ball.
     *
     * @return
     */
    Ball *getBall() const;

    /** Returns player information vector.
     *
     * @return
     */
    const vector<PlayerInfo *> & getPlayerList() const;
    /** Removes player from connected clients.
     *
     * @param playerInfo
     */
    void removePlayer(PlayerInfo * playerInfo);
    /** Adds player to player information vector.
     *
     * @param playerInfo
     */
    void addPlayer(PlayerInfo * playerInfo);
    /** Returns current depth level.
     *
     * @return
     */
    int getDepthLevel() const;
    /**Sets depth level.
     *
     * @param depthLevel
     */
    void setDepthLevel(int depthLevel);

    int getVisibleBlocks() const;

    void setVisibleBlocks(int visibleBlocks);

};

//static GameInfo GAME_SINGLETON;

#endif //DATOSII_PROYECTOI_SERVER_GAMEINFO_H
