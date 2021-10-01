//
// Created by cuadriante on 29/9/21.
//

#include "../../Headers/Breakout/GameLoop.h"

GameLoop::GameLoop(GameInfo *gameInfo) {
    this->gameInfo = gameInfo;
    pthread_t thread;
    pthread_create(&thread, 0, gameLoop, (void *) gameInfo);
    pthread_detach(thread);

}


bool GameLoop::collide(int x1, int x2, int y1, int y2, int w, int z) {
    //return true if x-y rect contains w,z
    return (x1 <= w && w <= x2 && y1 <= z && z <= y2);
}


long GameLoop::currentTimeInMillis() {
    return chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[noreturn]] void *GameLoop::gameLoop(void *pgame) {
    GameInfo *gameInfo = (GameInfo *) pgame;
    GameModeSettings gameModeSettings(gameInfo);
    const int ballUpdateIntervalInMilli = 100;
    long ballLastUpdated = 0;

    while (true) {
        if (gameInfo->getPlayerList().size() == 0) {
            sleep(1);
            continue;
        }
        if (currentTimeInMillis() - ballLastUpdated > ballUpdateIntervalInMilli) {

            Ball *ball = gameInfo->getBall();
            checkForBallOutOfBounds(gameInfo, ball);
            checkBlockCollision(gameModeSettings, gameInfo, ball);
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

void GameLoop::checkBlockCollision(GameModeSettings gameModeSettings, GameInfo * gameInfo, Ball *ball) {
    int ignoreBlocksAfter = 60 - gameInfo->getDepthLevel() * 5;
    int currentBlockId = 0;
//    if (ignoreBlocksAfter <= 0){
//        ignoreBlocksAfter = 12;
//    }
    for (Block *block: gameInfo->getBlockList()) {
        if (currentBlockId >= ignoreBlocksAfter && block->getType() != Command::BLOCK_TYPE_DEEP){
            currentBlockId ++;
            continue;
        }
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
                gameModeSettings.createSurprise();
            }

            // change depth level
            if (block->getType() == Command::BLOCK_TYPE_DEEP) {
                int currentDepthLevel = gameInfo->getDepthLevel();
                gameInfo->setDepthLevel(currentDepthLevel + 1);
                if (gameInfo->getDepthLevel() >= 13){
                    gameInfo->setDepthLevel(0);
                }
                Command cmd;
                cmd.setAction(cmd.ACTION_SET_DEPTH_LEVEL);
                cmd.setSize(gameInfo->getDepthLevel());
                for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                    playerInfo->getSocket()->sendCommand(cmd);
                }
            }

            if (block->getHitsToBreak() <= 0) { //cambiar
                int type = block->getType();

                gameInfo->setVisibleBlocks(gameInfo->getVisibleBlocks()-1);
                gameModeSettings.sendPointsGained(type);
                Command c;
                c.setAction(c.ACTION_DELETE_BLOCK);
                c.setId(block->getId());

                for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                    playerInfo->getSocket()->sendCommand(c);
                }

                // win game

                bool onlyDeepBlocksLeft = true;

                for (Block * block: gameInfo->getBlockList()) {
                    if (block->getType() != Command::BLOCK_TYPE_DEEP){
                        onlyDeepBlocksLeft = false;
                        break;
                    }
                }

                if (gameInfo->getVisibleBlocks() <= 0 || onlyDeepBlocksLeft){
                    Command c2;
                    c2.setAction(c2.ACTION_WIN_GAME);
                    for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                        playerInfo->getSocket()->sendCommand(c2);
                    }
                }

            }
        }
        currentBlockId ++;
    }
}

void GameLoop::checkPlayerBarCollision(const GameInfo *gameInfo, Ball *ball) {
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

void GameLoop::checkForBallOutOfBounds(const GameInfo *gameInfo, Ball *ball) {
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
        if (ball->getVy() > 0){
            Command c;
            c.setAction(c.ACTION_END_GAME);
            for (PlayerInfo *playerInfo: gameInfo->getPlayerList()) {
                //playerInfo->getSocket()->sendCommand(c);
            }
        }

        ball->setY(600);
        ball->setVy(-ball->getVy());

        if (gameInfo->getVisibleBlocks() <= 0) {
            ball->setY(600);
            ball->setVy(-ball->getVy());
        }
    }
}
