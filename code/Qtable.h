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

    int getMax(vector<double> actions);

private:
    vector<int> actions;
    vector<int> states;

    vector<vector<double>> rewards;

    

};