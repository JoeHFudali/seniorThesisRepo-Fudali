#include "DeepQalgorithm.h"
#include "random"

using namespace std;

DeepQalgorithm::DeepQalgorithm() {
	alpha = 0.1;

	gamma = 0.9;

	epsilon = 0.5;

	ExReplayBuffer.resize(10000);
	vector<int> architecture = { 9, 12, 12, 9 };

	board = new TicTacToeBoard();
	//Qnetwork = new Neural_Network(architecture)
}

DeepQalgorithm::DeepQalgorithm(double learningRate, double discount, double greedy, int bufferSize) {
	alpha = learningRate;
	gamma = discount;
	epsilon = greedy;

	ExReplayBuffer.resize(bufferSize);

	board = new TicTacToeBoard();

	vector<int> architecture = { 9, 12, 12, 9 };
	vector<vector<double>> stateLabels;
	vector<vector<double>> actionLabels;
	qNetwork = new Qnetwork(architecture, alpha, stateLabels, actionLabels);


	//Set up Networks here
}

DeepQalgorithm::~DeepQalgorithm() {
	delete board;
	board = 0;
}

double DeepQalgorithm::calculateLoss() {

}

void DeepQalgorithm::backPropogate() {

}

vector<DeepQalgorithm::ExReplay> DeepQalgorithm::sampleExperiences(int batchSize) {
	vector<DeepQalgorithm::ExReplay> retVals;

	for (int i = 0; i < batchSize; i++) {
		int randIndex = rand() % ExReplayBuffer.size() + 1;
		retVals.push_back(ExReplayBuffer[randIndex]);
	}

	return retVals;
}

void DeepQalgorithm::collectData() {
	string boardState = board->getBoardString();
	vector<double> stateNums;
	//I will set state nums to be equal to certain values that can be inputed into our predict function
	
	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> dis(0.0, 1.0);

	double randNum = dis(gen);

	int currentAction;

	vector<double> actionProbs = qNetwork->predictQActions(stateNums);


	//We will need to minimize our actions here based on our current state before deciding the best action.

	if (randNum < epsilon) {
		currentAction = getRandIndex(actionProbs);

	}
	else {
		currentAction = table->getActionMax(boardState);

	}
}

int DeepQalgorithm::getRandIndex(vector<double> actions) {
	int randIndex = rand() % actions.size();

	return randIndex
}