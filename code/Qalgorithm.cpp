#include "Qalgorithm.h"

using namespace std;

//Constrctor mostly used to set up our constant values, such as the epsilon-greedy value.

Qalgorithm::Qalgorithm(double eps, double alp, double gam) {
    epsilon = eps;
    alpha = alp;
    gamma = gam;

}

void Qalgorithm::iterate(int episodes) {

    for(int i = 0; i < episodes; i++) {
        int randNum = rand() % 2;
        cout << randNum << endl;
    }
}

Qtable Qalgorithm::getQTable() {
    return table;
}