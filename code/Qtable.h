#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include "TicTacToeBoard.h"

using namespace std;

class Qtable {
public:

    Qtable();
    ~Qtable();

    void constructTable(vector<string> actionLabels, vector<string> stateLabels);



    vector<string> getStates();
    vector<string> getActions();

    void setQValue(int action, string boardString, double value);

    unordered_map<string, vector<double>>* getRewards();

    //Change this to getActionMax
    int getActionMax(string currState);

    int getRow(int action);
    int getCol(int action);

    void printTable();

private:

    vector<string> actionStrings;
    vector<string> stateStrings;

    unordered_map<string, vector<double>>* rewards;

    

};