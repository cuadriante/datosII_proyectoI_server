//
// Created by cuadriante on 8/9/21.
//

#ifndef DATOSII_PROYECTOI_SERVER_BLOCK_H
#define DATOSII_PROYECTOI_SERVER_BLOCK_H


class Block {
private:
    int id;
    int type;
    int hitsToBreak;
    int posx;
    int posy;

public:
    Block(int id, int type, int posx, int posy);

    int getId() const;

    int getHitsToBreak() const;

    void setHitsToBreak(int hitsToBreak);

    int getPosX() const;

    void setPosx(int posx);

    int getPosY() const;

    void setPosy(int posy);

};


#endif //DATOSII_PROYECTOI_SERVER_BLOCK_H
