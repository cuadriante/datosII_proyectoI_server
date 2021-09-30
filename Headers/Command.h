//
// Created by cuadriante on 19/9/21.
//

/** @brief Command class used for communication between server and socket.

    @author cuadriante
    @date September 2021
    */


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
    static const int ACTION_CREATE_PLAYER = 10; /**<action for player creation*/
    static const int ACTION_MOVE_PLAYER = 11; /**<action for player movement*/
    static const int ACTION_MOVE_BALL = 12; /**<action for ball movement*/
    static const int ACTION_MOVE_BLOCK = 13; /**<action for block movement*/
    static const int ACTION_DELETE_BLOCK = 14; /**<action for block deletion*/
    static const int ACTION_SET_SCORE = 15; /**<action for score setting*/
    static const int ACTION_CREATE_BLOCK = 16; /**<action for block creation*/
    static const int ACTION_SET_DEPTH_LEVEL = 17; /**<action for depth level setting*/
    static const int ACTION_SET_PLAYER_BAR_SIZE = 18; /**<action for player bar size  setting*/
    static const int ACTION_MOVE_OTHER_PLAYER = 19; /**<action for other player movement setting*/
    // to server
    static const int ACTION_START_GAME = 20; /**<action for game start*/
    static const int ACTION_MOVE_LEFT = 21; /**<action for player movement to the left*/
    static const int ACTION_MOVE_RIGHT = 22; /**<action for player movement to the right*/
    static const int ACTION_END_GAME = 23; /**<action for game end*/
    // block types
    static const int BLOCK_TYPE_COMMON = 31; /**<action for common block*/
    static const int BLOCK_TYPE_DOUBLE = 32; /**<action for double block*/
    static const int BLOCK_TYPE_TRIPLE = 33; /**<action for triple block*/
    static const int BLOCK_TYPE_INTERNAL = 34; /**<action for internal block*/
    static const int BLOCK_TYPE_DEEP = 35; /**<action for deep block*/
    static const int BLOCK_TYPE_SURPRISE = 36; /**<action for surprise block*/

    /** Sets action.
       *
       * @param action
       */
    void setAction(int action);
    /** Sets position in X.
     *
     * @param newPlayerX
     */
    void setPosX(int newPlayerX);
    /** Returns action.
     *
     * @return
     */
    int getAction();
    /** Returns position in y.
     *
     * @return
     */
    int getPosX();
    /** Returns type.
     *
     * @return
     */
    int getType() const;
    /** Returns position in y.
     *
     * @return
     */
    int getPosY() const;
    /** Sets position in Y.
     *
     * @param posY
     */
    void setPosY(int posY);
    /** Sets type.
     *
     * @param type
     */
    void setType(int type);
    /**Returns name.
     *
     * @return
     */
    const string &getName() const;
    /** Sets name.
     *
     * @param name
     */
    void setName(const string &name);
    /** Returns size.
     *
     * @return
     */
    int getSize() const;
    /** Sets size.
     *
     * @param size
     */
    void setSize(int size);
    /** Returns id.
     *
     * @return
     */
    int getId() const;
    /** Sets id.
     *
     * @param id
     */
    void setId(int id);

private:
    int id; /**<initial id*/
    int action; /**<initial action*/
    int posX; /**<initial x position*/
    int posY; /**<initial y position*/
    string name; /**<initial name*/
    int type; /**<initial type*/
    int size; /**<initial size*/

};

#endif //DATOSII_PROYECTOI_SERVER_COMMAND_H
