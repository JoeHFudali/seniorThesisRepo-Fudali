#pragma once
#include <iostream>
#include <vector>
#include "Qnetwork.h"
#include "TicTacToeBoard.h"

using namespace std;

class DeepQalgorithm {
public:

	DeepQalgorithm();
	DeepQalgorithm(double lr, double discount, double greedy, int bufferSize, int batchSize);
	~DeepQalgorithm();

	void trainNetworks();
	double calculateMeanError(double qValue, double tValue);
	void backPropogate(double error);
	
	void collectData();

	void playGame();

private:

	struct ExReplay {
		string startState;
		int action;
		double reward;
		string newState;
	};

	vector<ExReplay> sampleExperiences(int batchSize);
	int getRandAction(vector<double> actions);
	int getMaxAction(vector<double> actions);

	void randomBoxPlayer(vector<double> stateNums);

	vector<ExReplay> ExReplayBuffer;
	Qnetwork* qNetwork;
	Qnetwork* tNetwork;

	//Our output layer for both of these NN will be the number of actions we can take.

	double epsilon;
	double alpha;
	double gamma;

	int batch;

	TicTacToeBoard* board;
};
