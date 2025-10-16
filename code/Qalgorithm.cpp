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

        //string boardString = "---------";
       //TicTacToeBoard board(boardString);

        //We will put the entirety of the below code into a while loop that looks something like this:
        //while(board.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
        // ** code below will be here **
        // }


        double randNum = double(rand()) / RAND_MAX;

        //We will use a dictionary or a similar container (enum?) to store/access our current state and the number associated with it
  

        int currentState;
        int currentAction;

       
        //currentState = getState(board.getBoardString()); getState will look through the afformentioned dictionary and retrieve the index for table use


        //We will need to minimize our actions here based on our current state before deciding the best action.

        if (randNum < epsilon) {
            int randIndex = rand() % (table.getActions().size());

            currentAction = table.getActions()[randIndex];

        }
        else {
            currentAction = table.getMax(table.getRewards()[currentState]);
             
        }

        //Do something like b1.setSquare() based on what our action is and what is represents (coords in this case)
        //We get new state based on new board string, our reward from the cross state/action done, and check if we are done

        //TicTacToeBoard::PLAYER_TURN turn = b1.getPlayerTurn();
        //TicTacToeBoard::SQUARE_OCCUPANT mark;
        //if(turn == TicTacToeBoard::PLAYER_TURN::X_TURN) {
        // mark = "X";
        //}
        //else {
        // mark = "O";
        //}
        //int row = table.getRow(action);
        //int col = table.getCol(action); These functions will go to our actions and return what coords they affect
        // 
        //board.setSquare(row, col, mark);


        int nextState;
        //nextState = getState(board.getBoardString()); This line just takes our new board and returns the index in the Qtable where it is located

        int nextAction = table.getMax(table.getRewards()[nextState]);

        double currentQValue = table.getRewards()[currentState][currentAction];

        double newValue = currentQValue + alpha * (currentQValue + gamma * table.getRewards()[nextState][nextAction] - currentQValue);

        table.setQValue(currentState, currentAction, newValue);

        currentState = nextState;


    }


}

Qtable Qalgorithm::getQTable() {
    return table;
}