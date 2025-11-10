#pragma once
#include "Neural_Network.h"

using namespace std;

class Qnetwork : Neural_Network {
public:

	Qnetwork(vector<int>& architecture, double learningRate, vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
	~Qnetwork();

	vector<double> predictQActions(vector<double>& input);

private:


};