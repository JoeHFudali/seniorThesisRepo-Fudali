#include "Qalgorithm.h"

using namespace std;

//Constrctor mostly used to set up our constant values, such as the epsilon-greedy value.

Qalgorithm::Qalgorithm(double eps, double alp, double gam) {
    epsilon = eps;
    alpha = alp;
    gamma = gam;

    table.constructTable({ 0, 1, 2, 3, 4, 5, 6, 7, 8 });

}

void Qalgorithm::iterate(int episodes) {

    srand(time(0));

    for(int i = 0; i < episodes; i++) {

        string boardString = "---------";
        TicTacToeBoard board(boardString);

        //Need to account for the fact that these actions cannot be repeated in the same game
        vector<int> remainingActions = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

        //We will put the entirety of the below code into a while loop that looks something like this:
        while(board.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
         //** code below will be here **
            double randNum = double(rand()) / RAND_MAX;

            //We will use a dictionary or a similar container (enum?) to store/access our current state and the number associated with it


            int currentState;
            int currentAction;


            //currentState = getState(board.getBoardString()); getState will look through the afformentioned dictionary and retrieve the index for table use


            //We will need to minimize our actions here based on our current state before deciding the best action.

            if (randNum < epsilon) {
                int randIndex = rand() % (remainingActions.size());

                currentAction = remainingActions[randIndex];

                remainingActions.erase(remainingActions.begin() + randIndex);

            }
            else {
                currentAction = table.getActionMax(remainingActions, currentState);

                remainingActions.erase(remainingActions.cbegin() + currentAction);

            }

            //Do something like b1.setSquare() based on what our action is and what is represents (coords in this case)
            //We get new state based on new board string, our reward from the cross state/action done, and check if we are done

            TicTacToeBoard::PLAYER_TURN turn = board.getPlayerTurn();
            TicTacToeBoard::SQUARE_OCCUPANT mark;
            TicTacToeBoard::SQUARE_OCCUPANT oppMark;
            if (turn == TicTacToeBoard::PLAYER_TURN::X_TURN) {
                mark = TicTacToeBoard::SQUARE_OCCUPANT::X;
                oppMark = TicTacToeBoard::SQUARE_OCCUPANT::O;
            }
            else {
                mark = TicTacToeBoard::SQUARE_OCCUPANT::O;
                oppMark = TicTacToeBoard::SQUARE_OCCUPANT::X;
            }

            int row = table.getRow(currentAction);
            int col = table.getCol(currentAction);
            
            board.setSquare(row, col, mark);

            randomBoxPlayer(remainingActions, board, oppMark);




            int nextState;
            //nextState = getState(board.getBoardString());

            int nextAction = table.getActionMax(remainingActions, nextState);

            double currentQValue = table.getRewards()[currentState][currentAction];

            double newValue = currentQValue + alpha * (currentQValue + gamma * table.getRewards()[nextState][nextAction] - currentQValue);

            table.setQValue(currentState, currentAction, newValue);

            currentState = nextState;
         }


    }


}

Qtable Qalgorithm::getQTable() {
    return table;
}

void Qalgorithm::randomBoxPlayer(vector<int>& remainingActions, TicTacToeBoard& board, TicTacToeBoard::SQUARE_OCCUPANT occupant) {
    int randIndex = rand() % (remainingActions.size());

    remainingActions.erase(remainingActions.begin() + randIndex);

    int row = table.getRow(randIndex);
    int col = table.getCol(randIndex);

    board.setSquare(row, col, occupant);


}

void Qalgorithm::playGame(TicTacToeBoard::SQUARE_OCCUPANT player) {

    string boardString = "---------";

    string outputMark, agentMark;
    TicTacToeBoard::SQUARE_OCCUPANT agent;

    int playerRow, playerCol, agentRow, agentCol;

    if (player == TicTacToeBoard::SQUARE_OCCUPANT::X) {
        outputMark = "X";
        agentMark = "O";
        agent = TicTacToeBoard::SQUARE_OCCUPANT::O;
    }
    else {
        outputMark = "O";
        agentMark = "X";
        agent = TicTacToeBoard::SQUARE_OCCUPANT::X;
    }

    cout << "You will be playing as: " << outputMark << endl;
    cout << "The AI will be playing as: " << agentMark << endl << endl;

    TicTacToeBoard board(boardString);

    board.printBoard();

    //Play TicTacToe game very similar to our Heuristic assignment. I will just substitute the heuristic algorithm to find the max in our qTable
    //given a specific state. Will finish later

    while (board.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
        //For now, our board string will represent our current state
        if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::X) {
            cout << "Enter in X's row: ";
            cin >> playerRow;
            cout << "Enter in X's col: ";
            cin >> playerCol;

            while ((board.getSquare(playerRow, playerCol) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
                || (playerRow < 0 || playerCol < 0)
                || (playerRow > board.getBoardDimension() - 1 || playerCol > board.getBoardDimension() - 1)) {
                cout << "Oops! You entered a position that either doesn't exist or is already taken. Please enter a valid position!" << endl;

                cout << "Enter in X's row: ";
                cin >> playerRow;
                cout << "Enter in X's col: ";
                cin >> playerCol;
            }

            cout << "Playing X at row " << playerRow << " and column " << playerCol << endl;

            board.setSquare(playerRow, playerCol, player);


        }
        else if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::O_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::O) {
            cout << "Enter in O's row: ";
            cin >> playerRow;
            cout << "Enter in O's col: ";
            cin >> playerCol;

            while ((board.getSquare(playerRow, playerCol) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
                || (playerRow < 0 || playerCol < 0)
                || (playerRow > board.getBoardDimension() - 1 || playerCol > board.getBoardDimension() - 1)) {
                cout << "Oops! You entered a position that either doesn't exist or is already taken. Please enter a valid position!" << endl;

                cout << "Enter in O's row: ";
                cin >> playerRow;
                cout << "Enter in O's col: ";
                cin >> playerCol;
            }

            cout << "Playing O at row " << playerRow << " and column " << playerCol << endl;

            board.setSquare(playerRow, playerCol, player);
        }
        else if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::O) {
            cout << "AI Agent's turn" << endl;

            //For now, we are using our boardString as the state, but this will change later
            string currState = board.getBoardString();

            int bestAction;
            //This will get the best option for the current state, and we will get the row and column for our choice using this value
            //bestAction = table.getActionMax(remainingActions, currState);

            agentRow = table.getRow(bestAction);
            agentCol = table.getCol(bestAction);

            cout << "Playing X at row " << agentRow << " and column " << agentCol << endl;

            board.setSquare(agentRow, agentCol, agent);
        }
        else {
            cout << "AI Agent's turn" << endl;

            //For now, we are using our boardString as the state, but this will change later
            string currState = board.getBoardString();

            int bestAction;
            //This will get the best option for the current state, and we will get the row and column for our choice using this value
            //bestAction = table.getActionMax(remainingActions, currState);

            agentRow = table.getRow(bestAction);
            agentCol = table.getCol(bestAction);

            cout << "Playing O at row " << agentRow << " and column " << agentCol << endl;

            board.setSquare(agentRow, agentCol, agent);
        }
        board.printBoard();
    }

    if (board.getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
        cout << "** X wins! **" << endl;
    }
    else if (board.getBoardState() == TicTacToeBoard::BOARD_STATE::O_WIN) {
        cout << "** O wins! **" << endl;
    }
    else {
        cout << "** Draw **" << endl;
    }
}