//
// Created by cuadriante on 25/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_PLAYERBAR_H
#define DATOSII_PROYECTOI_SERVER_PLAYERBAR_H


class PlayerBar {
private:
    int posX = 300; /**<initial x position*/
    int posY = 550; /**<initial y position*/
    int size = 100; /**<initial size*/
public:
    /** Returns player bar x position.
     *
     * @return
     */
    int getPosX() const;
    /** Sets player bar x position.
     *
     * @param posX
     */
    void setPosX(int posX);
    /** Returns player bar y position.
     *
     * @return
     */
    int getPosY() const;
    /** Sets player bar y position.
     *
     * @param posY
     */
    void setPosY(int posY);
    /** Returns player bar current size.
     *
     * @return
     */
    int getSize() const;
    /** Sets player bar size.
     *
     * @param size
     */
    void setSize(int size);
};


#endif //DATOSII_PROYECTOI_SERVER_PLAYERBAR_H
