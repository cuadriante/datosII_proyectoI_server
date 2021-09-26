#include "../Headers/Socket.h"
#include "../Headers/Protocol.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameInfo.h"

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
            gameInfo->getBall()->setX(gameInfo->getBall()->getX() + rand() %3 - 1);
            gameInfo->getBall()->setY(gameInfo->getBall()->getY() + rand() %3 - 1);

            Command cmd;
            cmd.setAction(Command::ACTION_MOVE_BALL);
            cmd.setPosX(gameInfo->getBall()->getX());
            cmd.setPosY(gameInfo->getBall()->getY());

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
