#pragma once
#include <iostream>
#include <vector>
#include "Qnetwork.h"
#include "TicTacToeBoard.h"

using namespace std;

class DeepQalgorithm {
public:

	DeepQalgorithm();
	DeepQalgorithm(double lr, double discount, double greedy, int bufferSize);
	~DeepQalgorithm();


	double calculateLoss();
	void backPropogate();
	
	void collectData();

private:

	struct ExReplay {
		string startState;
		int action;
		double reward;
		string newState;
	};

	vector<ExReplay> sampleExperiences(int batchSize);
	int getRandAction(vector<double> actions);

	vector<ExReplay> ExReplayBuffer;
	Qnetwork* qNetwork;
	Neural_Network* Tnetwork;

	//Our output layer for both of these NN will be the number of actions we can take.

	double epsilon;
	double alpha;
	double gamma;

	TicTacToeBoard* board;
};
