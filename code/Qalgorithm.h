#include <iostream>
#include <ctime>
#include "Qtable.h"
#include "TicTacToeBoard.h"

using namespace std;

class Qalgorithm {
public:
    Qalgorithm();
    Qalgorithm(double eps, double alp, double gam, vector<string> actionLabels, vector<string> stateLabels);
    ~Qalgorithm();

    //We will include a "run" function that takes the Q-table, plays games of TicTacToe,
    //and alters our table's values depending on our episode results

    void iterate(int episodes);
    void playGame(TicTacToeBoard::SQUARE_OCCUPANT player);

    Qtable* getQtable();

    void SaveData(string outputFile, int episodes);
    void LoadData(string inputFile);

private:

    void randomBoxPlayer(TicTacToeBoard& board, TicTacToeBoard::SQUARE_OCCUPANT occupant);
    int getRandIndex(string boardString);

    Qtable* table;
    double epsilon;
    double alpha;
    double gamma;
};