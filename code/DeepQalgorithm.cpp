#include "DeepQalgorithm.h"
#include "random"

using namespace std;

DeepQalgorithm::DeepQalgorithm() {
	alpha = 0.1;

	gamma = 0.9;

	epsilon = 0.5;

	ExReplayBuffer.resize(10000);
	vector<int> architecture = { 9, 5, 5, 9 };

	batch = 9;

	board = new TicTacToeBoard();
	qNetwork = new Qnetwork(architecture, 0.3, 1000);
	tNetwork = new Qnetwork(architecture, 0.3, 1000);
}

DeepQalgorithm::DeepQalgorithm(double learningRate, double discount, double greedy, int bufferSize, int batchSize, int numEpisodes, vector<int> architecture) {
	alpha = learningRate;
	gamma = discount;
	epsilon = greedy;

	batch = batchSize;

	ExReplayBuffer.resize(bufferSize);

	board = new TicTacToeBoard();

	qNetwork = new Qnetwork(architecture, alpha, numEpisodes);
	tNetwork = new Qnetwork(architecture, alpha, numEpisodes);

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
		int randIndex = rand() % ExReplayBuffer.size();
		retVals.push_back(ExReplayBuffer[randIndex]);
	}

	return retVals;
}

void DeepQalgorithm::collectData() {
	//Very crude implementation for our collection function that fills our Experience Replay Buffer, will fix after some consultation with the professor
	for (int i = 0; i < ExReplayBuffer.size(); i++) {
		double reward = -1.0;

		string boardState = board->getBoardString();
		vector<double> stateNums = convertStringToNeuronInput(boardState);

		//cout << board->getBoardString() << endl;

		string newBoardString;
		

		random_device rd;
		mt19937 gen(rd());

		uniform_real_distribution<> dis(0.0, 1.0);

		double randNum = dis(gen);

		int currentAction;

		//vector<double> actionProbs = qNetwork->predictQActions(stateNums);



		if (randNum < epsilon) {
			currentAction = getRandAction(boardState);

		}
		else {
			currentAction = getMaxAction(stateNums);
		}

		int row = board->getRow(currentAction);
		int col = board->getCol(currentAction);

		board->setSquare(row, col, TicTacToeBoard::SQUARE_OCCUPANT::X);

		newBoardString = board->getBoardString();

		if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {

			if (board->getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
				reward = 10.0;
			}
			ExReplay newReplay;
			newReplay.startState = boardState;
			newReplay.action = currentAction;
			newReplay.reward = reward;
			newReplay.newState = newBoardString;
			//cout << newReplay.startState << " " << newReplay.newState << endl;

			ExReplayBuffer[i] = newReplay;

			board->resetBoard();
		}
		else {
			ExReplay newReplay;
			newReplay.startState = boardState;
			newReplay.action = currentAction;
			newReplay.reward = reward;
			newReplay.newState = newBoardString;
			//cout << newReplay.startState << " " << newReplay.newState << endl;

			ExReplayBuffer[i] = newReplay;


			stateNums = convertStringToNeuronInput(newBoardString);
			boardState = newBoardString;

			randomBoxPlayer(boardState);


			if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
				board->resetBoard();
			}
		}
		

		if (epsilon > 0.1) {
			epsilon *= .9999;
		}

	}

}

int DeepQalgorithm::getRandAction(string state) {
	vector<int> choices;

	for (int i = 0; i < state.size(); i++) {
		if (state[i] == '-') {
			choices.push_back(i);
		}

	}

	int randIndex = rand() % choices.size();

	return choices[randIndex];
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

double DeepQalgorithm::getNextStateMaxAction(vector<double> actions, TicTacToeBoard b) {
	double action = actions[0];
	int row, col;
	for (int i = 0; i < actions.size(); i++) {
		row = b.getRow(i);
		col = b.getCol(i);
		if (actions[i] > action && b.getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY) {
			action = actions[i];
		}
	}

	return action;
}


void DeepQalgorithm::randomBoxPlayer(string state) {
	//Come back to this later, this code is far from complete, just need it to get our replay buffer filler looking good.
	int actionChoice = getRandAction(state);

	int row = board->getRow(actionChoice);
	int col = board->getCol(actionChoice);

	board->setSquare(row, col, TicTacToeBoard::SQUARE_OCCUPANT::O);


}

void DeepQalgorithm::trainNetworks() {

	for (int m = 0; m < qNetwork->getTrainingIterations(); m++) {
		cout << m << endl;
		vector<ExReplay> sampleBatch = sampleExperiences(batch);

		for (int i = 0; i < sampleBatch.size(); i++) {

			vector<double> stateNums;
			vector<double> futureStateNums;
			double highestTargetValue;

			stateNums = convertStringToNeuronInput(sampleBatch[i].startState);

			vector<double> actionProbs = qNetwork->predictQActions(stateNums);


			double choice = actionProbs[sampleBatch[i].action];

			futureStateNums = convertStringToNeuronInput(sampleBatch[i].newState);

			vector<double> futureActionProbs = tNetwork->predictQActions(futureStateNums);

			TicTacToeBoard trainingBoard(sampleBatch[i].newState);
			if (trainingBoard.getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
				highestTargetValue = getNextStateMaxAction(futureActionProbs, trainingBoard);



				highestTargetValue *= gamma;
				highestTargetValue += sampleBatch[i].reward;
			}
			else {
				highestTargetValue = sampleBatch[i].reward;
			}


			double error = (highestTargetValue - choice) * (highestTargetValue - choice);

			qNetwork->adjustNetwork(error, sampleBatch[i].action, stateNums);

		}

		if (m % 100 == 0) {
			tNetwork->copyNetwork(qNetwork);
		}
	}
	
}

vector<double> DeepQalgorithm::convertStringToNeuronInput(string boardString) {
	vector<double> retVals;

	for (char occupant : boardString) {
		if(occupant != '-') {
			retVals.push_back(-10.0);
		}
		else {
			retVals.push_back(-1.0);
		}
	}

	return retVals;
}


void DeepQalgorithm::playGame(string startBoard) {

	TicTacToeBoard pBoard(startBoard);

	cout << "You will be playing as O and the agent will play as X" << endl << endl;

	pBoard.printBoard();

	int agentRow, agentCol, playerRow, playerCol;

	while (pBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {

		cout << "X's turn" << endl << endl;
		vector<double> currentBoardState = convertStringToNeuronInput(pBoard.getBoardString());
		int action = getMaxAction(qNetwork->predictQActions(currentBoardState));

		agentRow = pBoard.getRow(action);
		agentCol = pBoard.getCol(action);

		cout << "Playing X at row " << agentRow << " and column " << agentCol << endl << endl;
		pBoard.setSquare(agentRow, agentCol, TicTacToeBoard::SQUARE_OCCUPANT::X);

		pBoard.printBoard();

		if (pBoard.getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
			break;
		}

		cout << "O's turn" << endl << endl;

		cout << "Enter in O's row: ";
		cin >> playerRow;
		cout << "Enter in O's col: ";
		cin >> playerCol;

		while ((playerRow < 0 || playerCol < 0)
			|| (playerRow > pBoard.getBoardDimension() - 1 || playerCol > pBoard.getBoardDimension() - 1)
			|| (pBoard.getSquare(playerRow, playerCol) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)) {
			cout << "Oops! You entered a position that either doesn't exist or is already taken. Please enter a valid position!" << endl;

			cout << "Enter in O's row: ";
			cin >> playerRow;
			cout << "Enter in O's col: ";
			cin >> playerCol;
		}

		

		cout << "Playing O at row " << playerRow << " and column " << playerCol << endl;

		pBoard.setSquare(playerRow, playerCol, TicTacToeBoard::SQUARE_OCCUPANT::O);

	}

	if (pBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
		cout << "**X wins!**" << endl;
	}
	else if (pBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::O_WIN) {
		cout << "**O wins!**" << endl;
	}
	else {
		cout << "**Draw!**" << endl;
	}
}