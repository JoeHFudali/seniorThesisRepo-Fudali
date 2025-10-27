#include "Qtable.h"
#include <vector>

using namespace std;

Qtable::Qtable() {
    

    //We will initialize states to have all combinations of taken spots.
    //This won't account for type of symbol (X or O), just how many are taken
    //and where they are taken.

    
}

void Qtable::constructTable(vector<string> actionLabels, vector<string> stateLabels) {

    rewards.resize(actionLabels.size());
    for (int i = 0; i < rewards.size(); i++) {
        rewards[i].resize(stateLabels.size());
    }

    //For now, we will assume X wins are desired by the agent, and O wins are losses

    for (int i = 0; i < actionLabels.size(); i++) {
        for (int j = 0; j < stateLabels.size(); j++) {
            TicTacToeBoard tempBoard(stateLabels[j]);
            if (tempBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
                rewards[i][j] = 1.0;
            }
            else if (tempBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::O_WIN) {
                rewards[i][j] = -1.0;
            }
            else {
                rewards[i][j] = 0.0;
            }
        }
    }

    actionStrings = actionLabels;
    stateStrings = stateLabels;


}

vector<string> Qtable::getStates() {
    return stateStrings;
}

vector<string> Qtable::getActions() {
    return actionStrings;
}


void Qtable::setQValue(int action, int state, double value) {
    rewards[action][state] = value;
}


vector<vector<double>> Qtable::getRewards() {
    return rewards;
}

int Qtable::getActionMax(vector<int> actionsRemaining, int currState) {
    double biggest = rewards[actionsRemaining[0]][currState];
    int retVal = 0;
    for (int i = 0; i < actionsRemaining.size(); i++) {
        if (rewards[actionsRemaining[i]][currState] > biggest) {
            biggest = rewards[actionsRemaining[i]][currState];
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

int Qtable::getState(string boardString) {
    int retVal = 0;

    for (int i = 0; i < stateStrings.size(); i++) {
        if (stateStrings[i] == boardString) {
            retVal = i;
            return retVal;
        }
    }

    retVal = -1;
    return retVal;
}

void Qtable::printTable() {
    cout << "         ";
    for (int i = 0; i < 8; i++) {
        cout << "| " << stateStrings[i] << " |";
    }
    cout << "|" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;


    for (int i = 0; i < actionStrings.size(); i++) {
        cout << actionStrings[i] << " Fill |    ";
        for (int j = 0; j < 8; j++) {
            cout << rewards[i][j] << "    |    ";
        }
        cout << endl;
   }
}