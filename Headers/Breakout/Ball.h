//
// Created by cuadriante on 22/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_BALL_H
#define DATOSII_PROYECTOI_SERVER_BALL_H


class Ball {
private:
    int x;
    int y;
    int Vx;
    int Vy;
public:
    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getVx() const;

    void setVx(int vx);

    int getVy() const;

    void setVy(int vy);
};


#endif //DATOSII_PROYECTOI_SERVER_BALL_H
