//
// Created by cuadriante on 25/9/21.
//

/** @brief PlayerInfo class used for storing player information.

    @author cuadriante
    @date September 2021
    */

#ifndef DATOSII_PROYECTOI_SERVER_PLAYERINFO_H
#define DATOSII_PROYECTOI_SERVER_PLAYERINFO_H


#include "Breakout/PlayerBar.h"
#include "Socket.h"

class PlayerInfo {
private:
    int socketId; /**<initial socket id*/
    int pointsGained = 0; /**<initial gained points*/
    void * gameInfo; /**<initial game information*/
    PlayerBar * playerBar; /**<initial player bar*/
    Socket * socket; /**<initial socket*/

public:
    /**Constructor.
     *
     */
    PlayerInfo();
    /** Returns socket id.
     *
     * @return
     */
    int getSocketId() const;
    /** Sets socket id.
     *
     * @param socketId
     */
    void setSocketId(int socketId);
    /** Returns points gained in game.
     *
     * @return
     */
    int getPointsGained() const;
    /** Sets points gained in game.
     *
     * @param pointGained
     */
    void setPointsGained(int pointGained);
    /** Returns game information.
     *
     * @return
     */
    void *getGameInfo() const;
    /** Sets game information.
     *
     * @param gameInfo
     */
    void setGameInfo(void *gameInfo);
    /** Returns player bar.
     *
     * @return
     */
    PlayerBar *getPlayerBar() const;
    /** Returns client socket.
     *
     * @return
     */
    Socket *getSocket() const;
    /** Sets client socket.
     *
     * @param socket
     */
    void setSocket(Socket *socket);

};


#endif //DATOSII_PROYECTOI_SERVER_PLAYERINFO_H
