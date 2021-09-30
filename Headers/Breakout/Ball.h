//
// Created by cuadriante on 22/9/21.
//

/** @brief Ball class used for gathering ball information.

    Gathers information about ball in game.
    @author cuadriante
    @date September 2021
    */


#ifndef DATOSII_PROYECTOI_SERVER_BALL_H
#define DATOSII_PROYECTOI_SERVER_BALL_H


class Ball {
private:
    int x; /**<initial x position*/
    int y; /**<initial y position*/
    int Vx; /**<initial x velocity*/
    int Vy; /**<initial y velocity*/
public:
    /** Returns x position.
     *
     * @return
     */
    int getX() const;
    /** Sets x position.
     *
     * @param x
     */
    void setX(int x);
    /**Returns Y position.
     *
     * @return
     */
    int getY() const;
    /**Sets y position.
     *
     * @param y
     */
    void setY(int y);
    /** Returns x velocity.
     *
     * @return
     */
    int getVx() const;
    /** Sets x velocity.
     *
     * @param vx
     */
    void setVx(int vx);
    /** Sets y velocity.
     *
     * @return
     */
    int getVy() const;
    /** Sets y velocity.
     *
     * @param vy
     */
    void setVy(int vy);
};


#endif //DATOSII_PROYECTOI_SERVER_BALL_H
