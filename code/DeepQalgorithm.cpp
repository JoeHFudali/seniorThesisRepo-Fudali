#include "DeepQalgorithm.h"
#include "random"

using namespace std;

DeepQalgorithm::DeepQalgorithm() {
	alpha = 0.1;

	gamma = 0.9;

	epsilon = 0.5;

	ExReplayBuffer.resize(10000);
	vector<int> architecture = { 9, 12, 12, 9 };

	batch = 9;

	board = new TicTacToeBoard();
	//Qnetwork = new Neural_Network(architecture)
}

DeepQalgorithm::DeepQalgorithm(double learningRate, double discount, double greedy, int bufferSize, int batchSize) {
	alpha = learningRate;
	gamma = discount;
	epsilon = greedy;

	batch = batchSize;

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

	delete qNetwork;
	qNetwork = 0;

	delete tNetwork;
	tNetwork = 0;
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
	//Very crude implementation for our collection function that fills our Experience Replay Buffer, will fix after some consultation with the professor
	for (int i = 0; i < ExReplayBuffer.size(); i++) {
		double reward = 0.0;

		string boardState = board->getBoardString();
		vector<double> stateNums = convertStringToNeuronInput(boardState);

		string newBoardString;
		

		random_device rd;
		mt19937 gen(rd());

		uniform_real_distribution<> dis(0.0, 1.0);

		double randNum = dis(gen);

		int currentAction;

		vector<double> actionProbs = qNetwork->predictQActions(stateNums);



		if (randNum < epsilon) {
			currentAction = getRandAction(actionProbs);

		}
		else {
			currentAction = getMaxAction(actionProbs);
		}

		int row = board->getRow(currentAction);
		int col = board->getCol(currentAction);

		board->setSquare(row, col, TicTacToeBoard::SQUARE_OCCUPANT::X);

		newBoardString = board->getBoardString();

		if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {

			if (board->getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
				reward = 1.0;
			}
			board->resetBoard();
		}

		ExReplay newReplay;
		newReplay.startState = boardState;
		newReplay.action = currentAction;
		newReplay.reward = reward;
		newReplay.newState = newBoardString;

		ExReplayBuffer.push_back(newReplay);



		stateNums = convertStringToNeuronInput(newBoardString);
		boardState = newBoardString;

		randomBoxPlayer(stateNums);
		
		//newBoardString = board->getBoardString();

		if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
			board->resetBoard();
		}


	}

}

int DeepQalgorithm::getRandAction(vector<double> actions) {
	int randIndex = rand() % actions.size();

	return randIndex;
}

int DeepQalgorithm::getMaxAction(vector<double> actions) {
	int index = 0;
	double action = actions[0];
	for (int i = 0; i < actions.size(); i++) {
		if (actions[i] > action) {
			action = actions[i];
			index = i;
		}
	}


	return index;
}


void DeepQalgorithm::randomBoxPlayer(vector<double> stateNums) {
	//Come back to this later, this code is far from complete, just need it to get our replay buffer filler looking good.

	vector<double> actionProbs = qNetwork->predictQActions(stateNums);
	int actionChoice = getRandAction(actionProbs);

	int row = board->getRow(actionChoice);
	int col = board->getCol(actionChoice);

	board->setSquare(row, col, TicTacToeBoard::SQUARE_OCCUPANT::O);


}

void DeepQalgorithm::trainNetworks() {

	for (int j = 0; j < 3; j++) {
		vector<ExReplay> sampleBatch;

		for (int i = 0; i < batch; i++) {
			int randIndex = rand() % ExReplayBuffer.size();
			sampleBatch.push_back(ExReplayBuffer[randIndex]);
		}


		for (int i = 0; i < sampleBatch.size(); i++) {
			TicTacToeBoard trainingBoard(sampleBatch[i].startState);

			vector<double> stateNums;
			vector<double> futureStateNums;
			double highestTargetValue;

			stateNums = convertStringToNeuronInput(sampleBatch[i].startState);

			vector<double> actionProbs = qNetwork->predictQActions(stateNums);


			double choice = actionProbs[sampleBatch[i].action];

			futureStateNums = convertStringToNeuronInput(sampleBatch[i].newState);

			vector<double> futureActionProbs = tNetwork->predictQActions(futureStateNums);
			highestTargetValue = futureActionProbs[0];
			for (double num : futureActionProbs) {
				if (num > highestTargetValue) {
					highestTargetValue = num;
				}
			}

			highestTargetValue *= gamma;
			highestTargetValue += sampleBatch[i].reward;


			double error = (highestTargetValue - choice) * (highestTargetValue - choice);

			//backPropogate(error);


		}
	}

	tNetwork = qNetwork;
	
}

vector<double> DeepQalgorithm::convertStringToNeuronInput(string boardString) {
	vector<double> retVals;

	for (char occupant : boardString) {
		if(occupant == 'X') {
			retVals.push_back(1.0);
		}
		else if (occupant == 'O') {
			retVals.push_back(-1.0);
		}
		else {
			retVals.push_back(0.0);
		}
	}

	return retVals;
}


void DeepQalgorithm::playGame() {

}