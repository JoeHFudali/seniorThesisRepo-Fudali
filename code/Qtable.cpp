#include "Qtable.h"
#include <vector>

using namespace std;

Qtable::Qtable() {
    

    //We will initialize states to have all combinations of taken spots.
    //This won't account for type of symbol (X or O), just how many are taken
    //and where they are taken.

    //EDIT: This has changed and we are now using every board string combo as aa state. This results in 5478 unique board strings.
}


//Builds out the table based on inputed action/state labels
void Qtable::constructTable(vector<string> actionLabels, vector<string> stateLabels) {

    rewards.resize(stateLabels.size());
    for (int i = 0; i < rewards.size(); i++) {
        rewards[i].resize(actionLabels.size());
    }

    //For now, we will assume X wins are desired by the agent, and O wins are losses

    for (int i = 0; i < stateLabels.size(); i++) {
        for (int j = 0; j < actionLabels.size(); j++) {
            TicTacToeBoard tempBoard(stateLabels[i]);
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

//Returns the state label strings (board strings)
vector<string> Qtable::getStates() {
    return stateStrings;
}

//Returns the action labels ("TL", "MM", "BR", etc.)
vector<string> Qtable::getActions() {
    return actionStrings;
}

//Reward table setter
void Qtable::setQValue(int action, int state, double value) {
    rewards[state][action] = value;
}

//Reward table getter
vector<vector<double>> Qtable::getRewards() {
    return rewards;
}

//Returns the index of the action with the max reward result, given a current state and a list of avaliable actions
int Qtable::getActionMax(vector<int> actionsRemaining, int currState) {
    double biggest = rewards[currState][actionsRemaining[0]];
    int retVal = 0;
    for (int i = 0; i < actionsRemaining.size(); i++) {
        if (rewards[currState][actionsRemaining[i]] > biggest) {
            biggest = rewards[currState][actionsRemaining[i]];
            retVal = i;
        }
    }

    return retVal;
}

//Action row getter
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


//Action column getter
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

//State getter
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

//Prints out our rewards table, actions acting as the columns and states as the rows
void Qtable::printTable() {
    cout << "     ";
    for (int i = 0; i < actionStrings.size(); i++) {
        cout << right << setw(5) <<  "|" << actionStrings[i];
    }
    cout << right << setw(5) << "|" << endl;
    cout << "---------+------+------+------+------+------+------+------+------+------+----------------------------" << endl;


    for (int i = 0; i < stateStrings.size(); i++) {
        cout << stateStrings[i] << "|";
        for (int j = 0; j < actionStrings.size(); j++) {
            cout << right << setw(6) << rewards[i][j] << "|";
        }
        cout << endl;
   }
}