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
        double randNum = double(rand()) / RAND_MAX;

        //We will use a dictionary or a similar container (enum?) to store/access our current state and the number associated with it

        int currentState;
        int currentAction;

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


        int nextState;

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