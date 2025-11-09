#pragma once
#include <iostream>
#include <vector>
#include "Neural_Network.h"

using namespace std;

class DeepQalgorithm {
public:

	DeepQalgorithm();
	~DeepQalgorithm();


	double calculateLoss();


private:

	struct ExReplay {
		string startState;
		int action;
		double reward;
		string newState;
	};

	vector<ExReplay> ExRepayBuffer;
	Neural_Network Qnetwork;
	Neural_Network Tnetwork;

	double epsilon;
	double alpha;
	double gamma;


};
