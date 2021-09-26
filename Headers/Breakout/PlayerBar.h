//
// Created by cuadriante on 25/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_PLAYERBAR_H
#define DATOSII_PROYECTOI_SERVER_PLAYERBAR_H


class PlayerBar {
private:
    int posX = 300;
    int posY = 550;
    int size = 100;
public:
    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

    int getSize() const;

    void setSize(int size);
};


#endif //DATOSII_PROYECTOI_SERVER_PLAYERBAR_H
