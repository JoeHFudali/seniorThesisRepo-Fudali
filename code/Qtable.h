#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Qtable {
public:

    Qtable();

    void constructTable(vector<int> actionInputs);



    vector<int> getStates();
    vector<int> getActions();

    void setQValue(int state, int action, double value);

    vector<vector<double>> getRewards();

    //Change this to getActionMax
    int getActionMax(vector<int> actionsRemaining, int currState);

    int getRow(int action);
    int getCol(int action);

private:
    vector<int> actions;
    vector<int> states;

    vector<vector<double>> rewards;

    

};