#include "../Headers/Socket.h"
#include "../Headers/ServerListener.h"
#include "../Headers/Breakout/GameModeSettings.h"
#include "../Headers/Breakout/GameLoop.h"


int main() {

    GameInfo *gameInfo = new GameInfo();
    ServerListener serverListener;
    if (serverListener.start()) {
        GameLoop gameLoop(gameInfo);
        serverListener.waitForConnections(gameInfo);
    }
    return 0;
}
