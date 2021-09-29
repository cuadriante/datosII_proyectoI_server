//
// Created by cuadriante on 8/9/21.
//

/** @brief Block class used for storing block information.

    @author cuadriante
    @date September 2021
    */


#ifndef DATOSII_PROYECTOI_SERVER_BLOCK_H
#define DATOSII_PROYECTOI_SERVER_BLOCK_H

class Block {
private:
    int id; /**<initial id*/
    int type; /**<initial type*/
    int hitsToBreak = 3; /**<initial hits to break*/
    int posx; /**<initial x position*/
    int posy; /**<initial y position*/

public:
    /** Constructor. Creates block.
     *
     * @param id
     * @param type
     * @param posx
     * @param posy
     */
    Block(int id, int type, int posx, int posy);
    /** Returns block id.
     *
     * @return
     */
    int getId() const;
    /** Returns block hits to break.
     *
     * @return
     */
    int getHitsToBreak() const;
    /** Sets block hits to break.
     *
     * @param type
     */
    void setHitsToBreak(int type);
    /** Returns block x position.
     *
     * @return
     */
    int getPosX() const;
    /** Sets block x position.
     *
     * @param posx
     */
    void setPosx(int posx);
    /** Returns block y position.
     *
     * @return
     */
    int getPosY() const;
    /** Sets block y position.
     *
     * @param posy
     */
    void setPosy(int posy);
    /** Returns block type.
     *
     * @return
     */
    int getType() const;
    /** Sets block hits to break by type.
     *
     * @param type
     */
    void setHitsByType(int type);
};


#endif //DATOSII_PROYECTOI_SERVER_BLOCK_H
