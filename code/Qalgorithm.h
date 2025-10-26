#include <iostream>
#include <ctime>
#include "Qtable.h"
#include "TicTacToeBoard.h"

using namespace std;

class Qalgorithm {
public:
    Qalgorithm(double eps, double alp, double gam, vector<string> actionLabels, vector<string> stateLabels);

    //We will include a "run" function that takes the Q-table, plays games of TicTacToe,
    //and alters our table's values depending on our episode results

    void iterate(int episodes);
    void playGame(TicTacToeBoard::SQUARE_OCCUPANT player);

    Qtable getQTable();

private:

    void randomBoxPlayer(vector<int>& remainingActions, TicTacToeBoard& board, TicTacToeBoard::SQUARE_OCCUPANT occupant);

    Qtable table;
    double epsilon;
    double alpha;
    double gamma;
};