#include "Qtable.h"
#include <vector>

using namespace std;

Qtable::Qtable() {
    

    //We will initialize states to have all combinations of taken spots.
    //This won't account for type of symbol (X or O), just how many are taken
    //and where they are taken.

    
}

void Qtable::constructTable(vector<string> actionLabels, vector<string> stateLabels) {
    for (int i = 0; i < actionLabels.size(); i++) {
        actions.push_back(i);
    }

    for (int i = 0; i < stateLabels.size(); i++) {
        states.push_back(i);
    }

    rewards.resize(actions.size());
    for (int i = 0; i < rewards.size(); i++) {
        rewards[i].resize(states.size());
    }


    for (int i = 0; i < actions.size(); i++) {
        for (int j = 0; j < states.size(); j++) {
            rewards[i][j] = 0.0;
        }
    }

    actionStrings = actionLabels;
    stateStrings = stateLabels;

    printTable();

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

int Qtable::getActionMax(vector<int> actionsRemaining, int currState) {
    double biggest = rewards[currState][0];
    int retVal = 0;

    for (int i = 0; i < actions.size(); i++) {
        if (rewards[currState][actionsRemaining[i]] > biggest) {
            biggest = rewards[currState][actionsRemaining[i]];
            retVal = i;
        }
    }


    return retVal;
}

int Qtable::getRow(int action) {
    if (action == 0 || action == 1 || action == 2) {
        return 0;
    }
    else if (action == 3 || action == 4 || action == 5) {
        return 1;
    }
    else if (action == 6 || action == 7 || action == 8) {
        return 2;
    }
    else {
        return 0;
        //Will replace this with an exception class throw
    }
}

int Qtable::getCol(int action) {
    if (action == 0 || action == 3 || action == 6) {
        return 0;
    }
    else if (action == 1 || action == 4 || action == 7) {
        return 1;
    }
    else if (action == 2 || action == 5 || action == 8) {
        return 2;
    }
    else {
        return 0;
        //Will replace this with an exception class throw
    }
}

void Qtable::printTable() {
    cout << "         ";
    for (int i = 0; i < 8; i++) {
        cout << "| " << stateStrings[i] << " |";
    }
    cout << "|" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;


    for (int i = 0; i < actions.size(); i++) {
        cout << actionStrings[i] << " Fill |    ";
        for (int j = 0; j < 8; j++) {
            cout << rewards[i][j] << "    |    ";
        }
        cout << endl;
   }
}