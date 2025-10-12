#include "Qtable.h"
#include <vector>

using namespace std;

Qtable::Qtable() {
    vector<string> actionLabels = {"Top Left", "Top Middle", "Top Right", 
               "Middle Left", "Middle", "Middle Right",
               "Bottom Left", "Bottom Middle", "Bottom Right"};

    //We will initialize states to have all combinations of taken spots.
    //This won't account for type of symbol (X or O), just how many are taken
    //and where they are taken.

    for(int i = 0; i < states.size(); i++) {
        for(int j = 0; j < actions.size(); j++) {
            rewards[i][j] = 0.0;
        }
    }
}

void Qtable::constructTable(vector<int> actionInputs) {
    actions = actionInputs;
}

vector<int> Qtable::getStates() {
    return states;
}

vector<int> Qtable::getActions() {
    return actions;
}


void Qtable::setQValue(int state, int action, double value) {
    rewards[state][action] = value;
}


vector<vector<double>> Qtable::getRewards() {
    return rewards;
}

int Qtable::getMax(vector<double> actions) {
    double biggest = actions[0];
    int retVal = 0;

    for (int i = 0; i < actions.size(); i++) {
        if (actions[i] > biggest) {
            biggest = actions[i];
            retVal = i;
        }
    }


    return retVal;
}

