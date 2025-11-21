#include "DeepQalgorithm.h"
#include "random"

using namespace std;

DeepQalgorithm::DeepQalgorithm() {
	alpha = 0.1;

	gamma = 0.9;

	epsilon = 0.5;

	buffer = 10000;
	//ExReplayBuffer.resize(10000);
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

	//ExReplayBuffer.resize(bufferSize);
	
	buffer = bufferSize;

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

vector<DeepQalgorithm::ExReplay> DeepQalgorithm::sampleExperiences() {
	vector<DeepQalgorithm::ExReplay> retVals;

	if (ExReplayBuffer.size() < batch) {
		for (int i = 0; i < ExReplayBuffer.size(); i++) {
			int randIndex = rand() % ExReplayBuffer.size();
			retVals.push_back(ExReplayBuffer[randIndex]);
		}
	}
	else {
		for (int i = 0; i < batch; i++) {
			int randIndex = rand() % ExReplayBuffer.size();
			retVals.push_back(ExReplayBuffer[randIndex]);
		}
	}
	return retVals;
}

void DeepQalgorithm::collectData() {
	
	if (ExReplayBuffer.size() == buffer) {
		ExReplayBuffer.erase(ExReplayBuffer.begin());
	}

	double reward =	1.0;

	string boardState = board->getBoardString();
	vector<double> stateNums = convertStringToNeuronInput(boardState);

	//cout << board->getBoardString() << endl;

	string newBoardString;


	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> dis(0.0, 1.0);

	double randNum = dis(gen);

	int currentAction;

	vector<double> actionProbs = qNetwork->predictQActions(stateNums);
	//adjustInvalidOutputs(actionProbs, *board);



	if (randNum < epsilon) {
		currentAction = getRandAction(boardState);

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
			reward = 10.0;
		}
		else if (board->getBoardState() == TicTacToeBoard::BOARD_STATE::DRAW) {
			reward = -1.0;
		}

		ExReplay newReplay;
		newReplay.startState = boardState;
		newReplay.action = currentAction;
		newReplay.reward = reward;
		newReplay.newState = newBoardString;
		//cout << newReplay.startState << " " << newReplay.newState << endl;

		ExReplayBuffer.push_back(newReplay);

		board->resetBoard();
	}
	else {
		ExReplay newReplay;
		newReplay.startState = boardState;
		newReplay.action = currentAction;
		newReplay.reward = reward;
		newReplay.newState = newBoardString;
		//cout << newReplay.startState << " " << newReplay.newState << endl;

		ExReplayBuffer.push_back(newReplay);


		stateNums = convertStringToNeuronInput(newBoardString);
		boardState = newBoardString;

		randomBoxPlayer(boardState);


		if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
			board->resetBoard();
		}
	}


	if (epsilon > 0.05) {
		epsilon *= .9999;
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
	//int row, col;
	double action = double(INT_MIN);
	for (int i = 0; i < actions.size(); i++) {
		//row = b.getRow(i);
		//col = b.getCol(i);
		if (actions[i] > action) {
			action = actions[i];
			index = i;
		}
	}


	return index;
}

double DeepQalgorithm::getNextStateMaxAction(vector<double> actions) {
	double action = actions[0];
	//int row, col;
	for (int i = 0; i < actions.size(); i++) {
		if (actions[i] > action) {
			action = actions[i];
		}
	}

	return action;
}

void DeepQalgorithm::adjustInvalidOutputs(vector<double>& probs, TicTacToeBoard b) {
	int row, col;
	for (int i = 0; i < probs.size(); i++) {
		row = b.getRow(i);
		col = b.getCol(i);
		if (b.getSquare(row, col) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY) {
			probs[i] *= double(INT_MIN);
		}
	}


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
		//cout << m << endl;

		collectData();

		vector<ExReplay> sampleBatch = sampleExperiences();

		for (int i = 0; i < sampleBatch.size(); i++) {

			vector<double> stateNums;
			vector<double> futureStateNums;
			double highestTargetValue;

			TicTacToeBoard trainingBoard(sampleBatch[i].startState);


			stateNums = convertStringToNeuronInput(sampleBatch[i].startState);

			vector<double> actionProbs = qNetwork->predictQActions(stateNums);
			//adjustInvalidOutputs(actionProbs, trainingBoard);


			double choice = actionProbs[sampleBatch[i].action];

			futureStateNums = convertStringToNeuronInput(sampleBatch[i].newState);

			TicTacToeBoard futureTBoard(trainingBoard.getBoardString());
			futureTBoard.setSquare(trainingBoard.getRow(sampleBatch[i].action), trainingBoard.getCol(sampleBatch[i].action), TicTacToeBoard::SQUARE_OCCUPANT::X);

			vector<double> futureActionProbs = tNetwork->predictQActions(futureStateNums);
			//adjustInvalidOutputs(futureActionProbs, futureTBoard);

			
			if (trainingBoard.getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
				highestTargetValue = getNextStateMaxAction(futureActionProbs);



				highestTargetValue *= gamma;
				highestTargetValue += sampleBatch[i].reward;
			}
			else {
				highestTargetValue = sampleBatch[i].reward;
			}


			double error = (highestTargetValue - choice) * (highestTargetValue - choice);

			

			qNetwork->adjustNetwork(error, sampleBatch[i].action, stateNums);

			

			//Come back here to experiment with sending back big errors for invalid moves, and also continue with the masking we are doing with out adjustInvalidOuputs function
			
		}

		if (m % 100 == 0 && m != 0) {

			/*cout << "Before copy" << endl << endl;
			vector<double> inputs = convertStringToNeuronInput(ExReplayBuffer[0].startState);
			vector<double> results = qNetwork->predictQActions(inputs);
			vector<double> cResults = tNetwork->predictQActions(inputs);
			for (int n = 0; n < results.size(); n++) {
				cout << results[n] << " ";
			}
			cout << endl;
			for (int n = 0; n < cResults.size(); n++) {
				cout << cResults[n] << " ";
			}
			cout << endl;*/
			
			tNetwork->copyNetwork(qNetwork);
			
			
			/*cout << "After copy" << endl << endl;
			vector<double> Afterinputs = convertStringToNeuronInput(ExReplayBuffer[0].startState);
			results = qNetwork->predictQActions(Afterinputs);
			cResults = tNetwork->predictQActions(Afterinputs);
			for (int n = 0; n < results.size(); n++) {
				cout << results[n] << " ";
			}
			cout << endl;
			for (int n = 0; n < cResults.size(); n++) {
				cout << cResults[n] << " ";
			}
			cout << endl;*/
			
		}
	}
	
}

vector<double> DeepQalgorithm::convertStringToNeuronInput(string boardString) {
	vector<double> retVals;

	for (char occupant : boardString) {
		if(occupant != '-') {
			retVals.push_back(-1.0);
		}
		else {
			retVals.push_back(0.0);
		}
	}

	return retVals;
}


void DeepQalgorithm::playGame(string startBoard) {

	TicTacToeBoard pBoard(startBoard);

	vector<int> tempArch = { 9, 16, 16, 9 };

	Qnetwork tempNetwork(tempArch, alpha, 15000);

	cout << "You will be playing as O and the agent will play as X" << endl << endl;

	pBoard.printBoard();

	int agentRow, agentCol, playerRow, playerCol;

	while (pBoard.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {

		cout << "X's turn" << endl << endl;
		vector<double> currentBoardState = convertStringToNeuronInput(pBoard.getBoardString());
		vector<double> results = qNetwork->predictQActions(currentBoardState);
		adjustInvalidOutputs(results, pBoard);
		for (double num : results) {
			cout << num << " ";
		}
		cout << endl;

		for (double num : tempNetwork.predictQActions(currentBoardState)) {
			cout << num << " ";
		}			
		cout << endl;

		int action = getMaxAction(results);

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