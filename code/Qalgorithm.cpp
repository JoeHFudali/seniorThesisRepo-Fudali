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
            if (turn == TicTacToeBoard::PLAYER_TURN::X_TURN) {
                mark = TicTacToeBoard::SQUARE_OCCUPANT::X;
            }
            else {
                mark = TicTacToeBoard::SQUARE_OCCUPANT::O;
            }

            int row = table.getRow(currentAction);
            int col = table.getCol(currentAction);
            
            board.setSquare(row, col, mark);

            //Now we need to make that action non-choosable.


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