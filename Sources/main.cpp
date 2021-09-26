#include "../Headers/Socket.h"
#include "../Headers/Protocol.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameInfo.h"

long currentTimeInMillis(){
    return chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[noreturn]] void * gameLoop(void * pgame){
    GameInfo * gameInfo = (GameInfo *)pgame;
    const int ballUpdateIntervalInMilli = 150;
    long ballLastUpdated = 0;

    while (true){
        if (gameInfo->getPlayerList().size() == 0){
            sleep(1);
            continue;
        }
        if (currentTimeInMillis() - ballLastUpdated > ballUpdateIntervalInMilli) {
            Ball * ball = gameInfo->getBall();
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
