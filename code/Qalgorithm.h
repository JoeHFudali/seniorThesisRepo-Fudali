#include <iostream>
#include "Qtable.h"

using namespace std;

class Qalgorithm {
public:
    Qalgorithm(double eps, double alp, double gam);

    //We will include a "run" function that takes the Q-table, plays games of TicTacToe,
    //and alters our table's values depending on our episode results

    void iterate(int episodes);

    Qtable getQTable();

private:
    Qtable table;
    double epsilon;
    double alpha;
    double gamma;
};