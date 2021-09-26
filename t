 int *socketId = (int *) psocketId;
    cout << "socketId: " << socketId << endl;

    Socket socket = Socket(*socketId);

    bool exit = false;

    Ball lastBallPosition;
    lastBallPosition.setX(GAME_SINGLETON.getBall()->getX());
    lastBallPosition.setY(GAME_SINGLETON.getBall()->getY());

    while (!exit) {
        Command *cmd = socket.readCommand();
        if (cmd != NULL) {
            int action = cmd->getAction();
            switch (action) {
                case Command::ACTION_START_GAME: {
                    for (Block *b: GAME_SINGLETON.getBlockList()) {
                        Command c;
                        c.setAction(c.ACTION_CREATE_BLOCK);
                        c.setId(b->getId());
                        c.setPosX(b->getPosX());
                        c.setPosY(b->getPosY());
                        c.setType(b->getType());
                        socket.sendCommand(c);

                        Command c2;
                        c2.setAction(c2.ACTION_MOVE_BALL);
                        c2.setPosX(GAME_SINGLETON.getBall()->getX());
                        c2.setPosY(GAME_SINGLETON.getBall()->getY());
                        socket.sendCommand(c2);
                    }
                };
            };
        }
        Ball currentBallPosition;
        currentBallPosition.setX(GAME_SINGLETON.getBall()->getX());
        currentBallPosition.setY(GAME_SINGLETON.getBall()->getY());
        if (currentBallPosition.getX() != lastBallPosition.getX() || currentBallPosition.getY() != lastBallPosition.getY()) {
            Command c2;
            c2.setAction(c2.ACTION_MOVE_BALL);
            c2.setPosX(GAME_SINGLETON.getBall()->getX());
            c2.setPosY(GAME_SINGLETON.getBall()->getY());
            socket.sendCommand(c2);

            lastBallPosition.setX(currentBallPosition.getX());
            lastBallPosition.setY(currentBallPosition.getY());
        }

    }

