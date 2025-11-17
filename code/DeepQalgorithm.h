#pragma once
#include <iostream>
#include <vector>
#include "Qnetwork.h"
#include "TicTacToeBoard.h"

using namespace std;

class DeepQalgorithm {
public:

	DeepQalgorithm();
	DeepQalgorithm(double lr, double discount, double greedy, int bufferSize, int batchSize, int numEpisodes, vector<int> architecture);
	~DeepQalgorithm();

	void trainNetworks();
	void collectData();

	vector<double> convertStringToNeuronInput(string boardString);

	void playGame(string startBoard);

private:

	struct ExReplay {
		string startState;
		int action;
		double reward;
		string newState;
	};

	vector<ExReplay> sampleExperiences(int batchSize);
	int getRandAction(string state);
	int getMaxAction(vector<double> actions);
	double getNextStateMaxAction(vector<double> actions, TicTacToeBoard b);

	void randomBoxPlayer(string state);

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
