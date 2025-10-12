#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Qtable {
public:

    Qtable();

    void constructTable();





private:
    vector<string> actions;
    vector<string> states;

    vector<vector<double>> rewards;

};