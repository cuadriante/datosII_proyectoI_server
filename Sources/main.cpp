#include "../Headers/Socket.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameInfo.h"

void checkForBallOutOfBounds(Ball *ball);

void checkBlockCollision(const GameInfo *gameInfo, Ball *ball);

void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball);

void checkPointsGained(int type, int i);

void sendPointsGained(const GameInfo *gameInfo, int type);

bool collide(int x1, int x2, int y1, int y2, int w, int z){
    //return true if x-y rect contains w,z
    return (x1 <= w && w <= x2 && y1 <= z && z <= y2);
}

long currentTimeInMillis(){
    return chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[noreturn]] void * gameLoop(void * pgame){
    GameInfo * gameInfo = (GameInfo *)pgame;
    const int ballUpdateIntervalInMilli = 100;
    long ballLastUpdated = 0;

    while (true){
        if (gameInfo->getPlayerList().size() == 0){
            sleep(1);
            continue;
        }
        if (currentTimeInMillis() - ballLastUpdated > ballUpdateIntervalInMilli) {

            Ball * ball = gameInfo->getBall();
            checkForBallOutOfBounds(ball);
            checkBlockCollision(gameInfo, ball);
            checkPlayerBarCollision(gameInfo, ball);

            Command cmd;
            cmd.setAction(Command::ACTION_MOVE_BALL);
            cmd.setPosX(ball->getX());
            cmd.setPosY(ball->getY());

            for (PlayerInfo * playerInfo: gameInfo->getPlayerList()) {
                Socket * socket = new Socket(playerInfo->getSocketId());
                socket->sendCommand(cmd);
            }

            ballLastUpdated = currentTimeInMillis();

        }

    }

}

void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball) {
    if (ball->getVy() > 0){
        for (PlayerInfo * playerInfo: gameInfo->getPlayerList()){
            if (collide(playerInfo->getPlayerBar()->getPosX(),
                        playerInfo->getPlayerBar()->getPosX() + playerInfo->getPlayerBar()->getSize(),
                        playerInfo->getPlayerBar()->getPosY(),
                        playerInfo->getPlayerBar()->getPosY() + 25, ball->getX(), ball->getY())){
                ball->setVx(ball->getVx());
                ball->setVy(-ball->getVy());
            }
        }
    }
}

void checkBlockCollision(const GameInfo *gameInfo, Ball *ball) {
    if (ball->getVy() < 0){
        for (Block * block: gameInfo->getBlockList()){
            if (block->getHitsToBreak() > 0 && collide(block->getPosX(), block->getPosX() + 100, block->getPosY(), block->getPosY() + 25, ball->getX(), ball->getY())){

                ball->setVx(ball->getVx());
                ball->setVy(-ball->getVy());
                block->setHitsToBreak(block->getHitsToBreak() - 1);
                cout << block->getHitsToBreak() << endl;

                if (block->getHitsToBreak() <= 0){ //cambiar
                    int type = block->getType();

                    sendPointsGained(gameInfo, type);

                    Command c;
                    c.setAction(c.ACTION_DELETE_BLOCK);
                    c.setId(block->getId());

                    for (PlayerInfo * playerInfo: gameInfo->getPlayerList()){
                        playerInfo->getSocket()->sendCommand(c);
                    }

                }
            }
        }
    }
}

void sendPointsGained(const GameInfo *gameInfo, int type) {
    int pointsGained;
    switch (type){
        case Command::BLOCK_TYPE_COMMON: { //common
            pointsGained = 10;
            break;
        }
        case Command::BLOCK_TYPE_DOUBLE: { //double
            pointsGained = 15;
            break;
        }
        case Command::BLOCK_TYPE_TRIPLE: { //triple
            pointsGained = 20;
            break;
        }
        case Command::BLOCK_TYPE_INTERNAL: { //internal
            pointsGained = 0;
            break;
        }
        case Command::BLOCK_TYPE_DEEP: { //deep
            pointsGained = 0;
            break;
        }
        case Command::BLOCK_TYPE_SURPRISE: { //surprise
            pointsGained = 0;
            break;
        }
    }
    Command cmd;
    cmd.setAction(cmd.ACTION_SET_SCORE);
    cmd.setSize(pointsGained);

    for (PlayerInfo * playerInfo: gameInfo->getPlayerList()){
        playerInfo->getSocket()->sendCommand(cmd);
    }
}

void checkForBallOutOfBounds(Ball *ball) {
    ball->setX(ball->getX() + ball->getVx());
    ball->setY(ball->getY() + ball->getVy());
    if (ball->getX() < 0) { // out of bounds left side
        ball->setX(0);
        ball->setVx(-ball->getVx());
    }
    if (ball->getX() > 600) { // out of bounds right side
        ball->setX(600);
        ball->setVx(-ball->getVx());
    }
    if (ball->getY() < 0) { // out of bounds top
        ball->setY(0);
        ball->setVy(-ball->getVy());
    }
    if (ball->getY() > 600) { // out of bounds bottom
        ball->setY(600);
        ball->setVy(-ball->getVy());
    }
}


int main() {

    GameInfo * gameInfo = new GameInfo();
    ServerListener serverListener;
    if (serverListener.start()){
        pthread_t thread;
        pthread_create(&thread, 0, gameLoop, (void *) gameInfo);
        pthread_detach(thread);
        serverListener.waitForConnections(gameInfo);
    }
    return 0;
}
