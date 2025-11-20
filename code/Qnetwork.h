#pragma once
#include "Layer.h"

using namespace std;

//This class needs to be worked on more to better resemble the Neural Network. I'll mostly keep it the same, especially in the Nueron and Layer classes. 
//What I do need to change is when the network begins to train (in conjunction with my DeepQalgorithm class), and how the back propogation works (since we
//are utilizng an unsupervised ML example).

//ANSWER - just copy the NN code and edit some of it (training to not have labels, back propogation somehow converted, etc.)

class Qnetwork {
public:

	Qnetwork(vector<int>& architecture, double lr, int nti);
	~Qnetwork();

	void copyNetwork(Qnetwork* networkToCopyFrom);

	void adjustNetwork(double error, int action, vector<double> state);

	vector<double> predictQActions(vector<double>& input);

	int getTrainingIterations();

private:

	Layer* firstLayer;
	double learningRate;
	int numberOfTrainingIterations;

};