#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TicTacToeBoard.h"

using namespace std;

class Qtable {
public:

    Qtable();

    void constructTable(vector<string> actionLabels, vector<string> stateLabels);



    vector<string> getStates();
    vector<string> getActions();

    void setQValue(int action, int state, double value);

    vector<vector<double>> getRewards();

    //Change this to getActionMax
    int getActionMax(vector<int> actionsRemaining, int currState);

    int getRow(int action);
    int getCol(int action);

    int getState(string boardString);

    void printTable();

private:

    vector<string> actionStrings;
    vector<string> stateStrings;

    vector<vector<double>> rewards;

    

};