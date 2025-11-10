#include "Qnetwork.h"

using namespace std;

Qnetwork::Qnetwork(vector<int>& architecture, double learningRate, vector<vector<double>>& trainingData, vector<vector<double>>& labelData) : Neural_Network(architecture, trainingData, labelData, learningRate, 0, false) {
	
}

vector<double> Qnetwork::predictQActions(vector<double>& input) {
	return predict(input);
}
