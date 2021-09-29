#include "../Headers/Socket.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameInfo.h"
#include "../Headers/Breakout/GameModeSettings.h"
#include "../Headers/Breakout/GameLoop.h"

//void checkForBallOutOfBounds(Ball *ball);
//
//void checkBlockCollision(GameModeSettings gameModeSettings, GameInfo *gameInfo, Ball *ball);
//
//void checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball);




int main() {

    GameInfo *gameInfo = new GameInfo();
    ServerListener serverListener;
    if (serverListener.start()) {
        GameLoop gameLoop(gameInfo);
//        pthread_t thread;
//        pthread_create(&thread, 0, gameLoop, (void *) gameInfo);
//        pthread_detach(thread);
        serverListener.waitForConnections(gameInfo);
    }
    return 0;
}
