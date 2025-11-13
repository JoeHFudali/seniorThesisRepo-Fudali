#pragma once
#include "Neural_Network.h"

using namespace std;

//This class needs to be worked on more to better resemble the Neural Network. I'll mostly keep it the same, especially in the Nueron and Layer classes. 
//What I do need to change is when the network begins to train (in conjunction with my DeepQalgorithm class), and how the back propogation works (since we
//are utilizng an unsupervised ML example).

class Qnetwork : Neural_Network {
public:

	Qnetwork(vector<int>& architecture, double learningRate, vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
	~Qnetwork();

	void backPropogate(double error);

	vector<double> predictQActions(vector<double>& input);

private:
	Layer* firstLayer;
	double learningRate;
	int numberOfTrainingIterations;

	//void train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData);


};