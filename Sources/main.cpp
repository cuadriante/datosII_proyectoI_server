#include "../Headers/Socket.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameInfo.h"

void checkForBallOutOfBounds(Ball *ball);

void checkBlockCollision(GameInfo *gameInfo, Ball *ball);

void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball);

void checkPointsGained(int type, int i);

void sendPointsGained(GameInfo *gameInfo, int type);

void createSurprise(GameInfo *gameInfo);

bool collide(int x1, int x2, int y1, int y2, int w, int z) {
    //return true if x-y rect contains w,z
    return (x1 <= w && w <= x2 && y1 <= z && z <= y2);
}

long currentTimeInMillis() {
    return chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[noreturn]] void *gameLoop(void *pgame) {
    GameInfo *gameInfo = (GameInfo *) pgame;
    const int ballUpdateIntervalInMilli = 100;
    long ballLastUpdated = 0;

    while (true) {
        if (gameInfo->getPlayerList().size() == 0) {
            sleep(1);
            continue;
        }
        if (currentTimeInMillis() - ballLastUpdated > ballUpdateIntervalInMilli) {

            Ball *ball = gameInfo->getBall();
            checkForBallOutOfBounds(ball);
            checkBlockCollision(gameInfo, ball);
            checkPlayerBarCollision(gameInfo, ball);

            Command cmd;
            cmd.setAction(Command::ACTION_MOVE_BALL);
            cmd.setPosX(ball->getX());
            cmd.setPosY(ball->getY());

            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                Socket *socket = new Socket(playerInfo->getSocketId());
                socket->sendCommand(cmd);
            }

            ballLastUpdated = currentTimeInMillis();

        }

    }

}

void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball) {
    if (ball->getVy() > 0) {
        for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
            if (collide(playerInfo->getPlayerBar()->getPosX(),
                        playerInfo->getPlayerBar()->getPosX() + playerInfo->getPlayerBar()->getSize(),
                        playerInfo->getPlayerBar()->getPosY(),
                        playerInfo->getPlayerBar()->getPosY() + 25, ball->getX(), ball->getY())) {
                ball->setVx(ball->getVx());
                ball->setVy(-ball->getVy());
            }
        }
    }
}

void checkBlockCollision(GameInfo *gameInfo, Ball *ball) {
    for (Block *block: gameInfo->getBlockList()) {
        if (block->getHitsToBreak() > 0 &&
            collide(block->getPosX(), block->getPosX() + 100, block->getPosY(),
                    block->getPosY() + 25, ball->getX(),
                    ball->getY())) {

            ball->setVx(ball->getVx());
            ball->setVy(-ball->getVy());
            block->setHitsToBreak(block->getHitsToBreak() - 1);
            cout << block->getHitsToBreak() << endl;

            //surprise
            if (block->getType() == Command::BLOCK_TYPE_SURPRISE) {
                createSurprise(gameInfo);
            }

            // change depth level
            if (block->getType() == Command::BLOCK_TYPE_DEEP) {
                int currentDepthLevel = gameInfo->getDepthLevel();
                gameInfo->setDepthLevel(currentDepthLevel + 1);
                Command cmd;
                cmd.setAction(cmd.ACTION_SET_DEPTH_LEVEL);
                cmd.setSize(gameInfo->getDepthLevel());
                for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                    playerInfo->getSocket()->sendCommand(cmd);
                }
            }

            if (block->getHitsToBreak() <= 0) { //cambiar
                int type = block->getType();

                sendPointsGained(gameInfo, type);

                Command c;
                c.setAction(c.ACTION_DELETE_BLOCK);
                c.setId(block->getId());

                for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                    playerInfo->getSocket()->sendCommand(c);
                }

            }
        }
    }
}

void createSurprise(GameInfo *gameInfo) {
    int surprise = rand() % 5 + 1;
    int currentVx = gameInfo->getBall()->getVx();
    int currentVy = gameInfo->getBall()->getVy();

    switch (surprise) {
        case 1: { // increase velocity
            gameInfo->getBall()->setVy(currentVy + (rand() % 10));
            gameInfo->getBall()->setVx(currentVx + (rand() % 10));
            cout << "INCREASE VELOCITY" << endl;
            cout << "Vx: " << gameInfo->getBall()->getVx() << endl;
            cout << "Vy: " << gameInfo->getBall()->getVy() << endl;
            break;
        }
        case 2: { //decrease velocity
            gameInfo->getBall()->setVy(currentVy - (rand() % 10));
            gameInfo->getBall()->setVx(currentVx - (rand() % 10));
            cout << "DECREASE VELOCITY" << endl;
            cout << "Vx: " << gameInfo->getBall()->getVx() << endl;
            cout << "Vy: " << gameInfo->getBall()->getVy() << endl;
            break;
        }
        case 3: { // increase player size
            cout << "INCREASE PLAYER BAR SIZE" << endl;
            Command c;
            c.setAction(c.ACTION_SET_PLAYER_BAR_SIZE);
            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                int currentSize = playerInfo->getPlayerBar()->getSize();
                playerInfo->getPlayerBar()->setSize(currentSize + (rand() % 20));
                c.setSize(playerInfo->getPlayerBar()->getSize());
                playerInfo->getSocket()->sendCommand(c);
                cout << "Size: " << playerInfo->getPlayerBar()->getSize() << endl;
            }

            break;
        }
        case 4: { // decrease player size
            cout << "DECREASE PLAYER BAR SIZE" << endl;
            Command c;
            c.setAction(c.ACTION_SET_PLAYER_BAR_SIZE);
            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                int currentSize = playerInfo->getPlayerBar()->getSize();
                playerInfo->getPlayerBar()->setSize(currentSize - (rand() % 20));
                if (playerInfo->getPlayerBar()->getSize() >= 150) {
                    playerInfo->getPlayerBar()->setSize(150);
                }
                //playerInfo->getSocket()->sendCommand(c);
                cout << "Size: " << playerInfo->getPlayerBar()->getSize() << endl;
            }
            break;
        }
        case 5: { //tbd
            cout << "OTHER SURPRISE" << endl;
            break;
        }
    }
    for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {

    }
}

void sendPointsGained(GameInfo *gameInfo, int type) {
    int pointsGained;
    switch (type) {
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
            if (gameInfo->getDepthLevel() <= 0) {
                pointsGained = 0;
            } else {
                pointsGained = 30;
            }

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

    for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
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

    GameInfo *gameInfo = new GameInfo();
    ServerListener serverListener;
    if (serverListener.start()) {
        pthread_t thread;
        pthread_create(&thread, 0, gameLoop, (void *) gameInfo);
        pthread_detach(thread);
        serverListener.waitForConnections(gameInfo);
    }
    return 0;
}
