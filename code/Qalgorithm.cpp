#include "Qalgorithm.h"
#include <random>

using namespace std;


Qalgorithm::Qalgorithm() {
    epsilon = 0;
    alpha = 0;
    gamma = 0;

    table = new Qtable();
}

//Constrctor mostly used to set up our constant values, such as the epsilon-greedy value. 

Qalgorithm::Qalgorithm(double eps, double alp, double gam, vector<string> actionLabels, vector<string> stateLabels) {
    epsilon = eps;
    alpha = alp;
    gamma = gam;

    table = new Qtable();
    table->constructTable(actionLabels, stateLabels);
}

//Destructor to delete the table pointer
Qalgorithm::~Qalgorithm() {
    delete table;
    table = 0;
}

//Training function for our algorithm
void Qalgorithm::iterate(int episodes) {

    TicTacToeBoard::SQUARE_OCCUPANT mark = TicTacToeBoard::SQUARE_OCCUPANT::X;
    TicTacToeBoard::SQUARE_OCCUPANT oppMark = TicTacToeBoard::SQUARE_OCCUPANT::O;

    for(int i = 0; i < episodes; i++) {


        string boardString = "---------";
        TicTacToeBoard board(boardString);

        double reward = 0.0;

        //We will put the entirety of the below code into a while loop that looks something like this:
        while(board.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
         //** code below will be here **
            
            random_device rd;
            mt19937 gen(rd());

            uniform_real_distribution<> dis(0.0, 1.0);

            double randNum = dis(gen);

            //We will use a dictionary or a similar container (enum?) to store/access our current state and the number associated with it
            int currentAction;


            string currentState = board.getBoardString(); //getState will look through the afformentioned dictionary and retrieve the index for table use
           
            //We will need to minimize our actions here based on our current state before deciding the best action.

            if (randNum < epsilon) {
                currentAction = getRandIndex(currentState);

            }
            else {
                currentAction = table->getActionMax(currentState);
                
            }

            //Do something like b1.setSquare() based on what our action is and what is represents (coords in this case)
            //We get new state based on new board string, our reward from the cross state/action done, and check if we are done

            int row = table->getRow(currentAction);
            int col = table->getCol(currentAction);
            
            board.setSquare(row, col, mark);


            //Actual Q-algorithm below, first for when we get an agent win

            if (board.getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
                reward = 1.0;

                string nextState = currentState;
                
                int nextAction = table->getActionMax(nextState);

                double currentQValue = (*table->getRewards())[currentState][currentAction];

                double newValue = currentQValue + alpha * (reward + gamma * (*table->getRewards())[nextState][nextAction] - currentQValue);

                table->setQValue(currentAction, currentState, newValue);

                break;
            }

            randomBoxPlayer(board, oppMark);
            

            string nextState = board.getBoardString();

            if (board.getBoardState() == TicTacToeBoard::BOARD_STATE::O_WIN) {
                reward = -1.0;
                nextState = currentState;
            }
            
            int nextAction = table->getActionMax(nextState);

            double currentQValue = (*table->getRewards())[currentState][currentAction];
            
            double newValue = currentQValue + alpha * (reward + gamma * (*table->getRewards())[nextState][nextAction] - currentQValue);

            table->setQValue(currentAction, currentState, newValue);
            
         }
        //Our learning rate decays over time
        if (epsilon > 0.1) {
            epsilon *= .9999;
        }

    }

    
}

Qtable* Qalgorithm::getQtable() {
    return table;
}

//Training helper that plays against the algorithm
void Qalgorithm::randomBoxPlayer(TicTacToeBoard& board, TicTacToeBoard::SQUARE_OCCUPANT occupant) {
    //Also come back to this later, since it uses a random index (that cannot be so random)
    int actionChoice = getRandIndex(board.getBoardString());

    int row = table->getRow(actionChoice);
    int col = table->getCol(actionChoice);

    board.setSquare(row, col, occupant);


}

//Function that selects a random action index based on the actions we can still take
int Qalgorithm::getRandIndex(string boardString) {
    vector<int> choices;
    for (int i = 0; i < boardString.size(); i++) {
        if (boardString[i] == '-') {
            choices.push_back(i);
        }
    }

    return choices[rand() % choices.size()];
}

//Function that lets you play a game of TicTacToe through the terminal with the algorithm
void Qalgorithm::playGame(TicTacToeBoard::SQUARE_OCCUPANT player) {

    string boardString = "---------";

    string outputMark, agentMark;
    TicTacToeBoard::SQUARE_OCCUPANT agent;

    int playerRow, playerCol, agentRow, agentCol;

    if (player == TicTacToeBoard::SQUARE_OCCUPANT::X) {
        outputMark = "X";
        agentMark = "O";
        agent = TicTacToeBoard::SQUARE_OCCUPANT::O;
    }
    else {
        outputMark = "O";
        agentMark = "X";
        agent = TicTacToeBoard::SQUARE_OCCUPANT::X;
    }

    cout << "You will be playing as: " << outputMark << endl;
    cout << "The AI will be playing as: " << agentMark << endl << endl;

    TicTacToeBoard board(boardString);

    board.printBoard();

    //Play TicTacToe game very similar to our Heuristic assignment. I will just substitute the heuristic algorithm to find the max in our qTable
    //given a specific state. Will finish later

    while (board.getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
        //For now, our board string will represent our current state

        //Player turn (X)
        if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::X) {
            cout << "Enter in X's row: ";
            cin >> playerRow;
            cout << "Enter in X's col: ";
            cin >> playerCol;

            while ((playerRow < 0 || playerCol < 0)
                || (playerRow > board.getBoardDimension() - 1 || playerCol > board.getBoardDimension() - 1)
                || (board.getSquare(playerRow, playerCol) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)) {
                cout << "Oops! You entered a position that either doesn't exist or is already taken. Please enter a valid position!" << endl;

                cout << "Enter in X's row: ";
                cin >> playerRow;
                cout << "Enter in X's col: ";
                cin >> playerCol;
            }

            int choice = playerRow * 3 + playerCol;

            cout << "Playing X at row " << playerRow << " and column " << playerCol << endl;

            board.setSquare(playerRow, playerCol, player);


        }
        //Player turn (O)
        else if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::O_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::O) {
            cout << "Enter in O's row: ";
            cin >> playerRow;
            cout << "Enter in O's col: ";
            cin >> playerCol;

            while ((playerRow < 0 || playerCol < 0)
                || (playerRow > board.getBoardDimension() - 1 || playerCol > board.getBoardDimension() - 1) 
                || (board.getSquare(playerRow, playerCol) != TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)) {
                cout << "Oops! You entered a position that either doesn't exist or is already taken. Please enter a valid position!" << endl;

                cout << "Enter in O's row: ";
                cin >> playerRow;
                cout << "Enter in O's col: ";
                cin >> playerCol;
            }

            int choice = playerRow * 3 + playerCol;
            int index = 0;

            cout << "Playing O at row " << playerRow << " and column " << playerCol << endl;

            board.setSquare(playerRow, playerCol, player);
        }
        //Agent Turn (X)
        else if (board.getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN && player == TicTacToeBoard::SQUARE_OCCUPANT::O) {
            cout << "AI Agent's turn" << endl;

            //For now, we are using our boardString as the state, but this will change later
            string currState = board.getBoardString();

            //This will get the best option for the current state, and we will get the row and column for our choice using this value
            int bestAction = table->getActionMax(currState);

            agentRow = table->getRow(bestAction);
            agentCol = table->getCol(bestAction);

            cout << "Playing X at row " << agentRow << " and column " << agentCol << endl;

            board.setSquare(agentRow, agentCol, agent);
        }
        //Agent turn (O)
        else {
            cout << "AI Agent's turn" << endl;

            //For now, we are using our boardString as the state, but this will change later
            string currState = board.getBoardString();

            //This will get the best option for the current state, and we will get the row and column for our choice using this value
            int bestAction = table->getActionMax(currState);

            agentRow = table->getRow(bestAction);
            agentCol = table->getCol(bestAction);

            cout << "Playing O at row " << agentRow << " and column " << agentCol << endl;

            board.setSquare(agentRow, agentCol, agent);
        }
        board.printBoard();
    }

    if (board.getBoardState() == TicTacToeBoard::BOARD_STATE::X_WIN) {
        cout << "** X wins! **" << endl << endl;
    }
    else if (board.getBoardState() == TicTacToeBoard::BOARD_STATE::O_WIN) {
        cout << "** O wins! **" << endl << endl;
    }
    else {
        cout << "** Draw **" << endl << endl;
    }
}

void Qalgorithm::SaveData(string outputFile, int episodes) {
    ofstream fout;

    fout.open(outputFile);

    if (fout.is_open()) {
        fout << episodes << " ";
        fout << alpha << " ";
        fout << gamma << " ";
        fout << epsilon << endl;

        for (string actionLabel : table->getActions()) {
            fout << actionLabel << " ";
        }
        fout << "\n";

        for (string stateLabel : table->getStates()) {
            fout << stateLabel << " ";
        }
        fout << "\n";


        for (int i = 0; i < table->getStates().size(); i++) {
            for (int j = 0; j < table->getActions().size(); j++) {
                fout << (*table->getRewards())[table->getStates()[i]][j] << " ";
            }
            fout << "\n";
        }
        
        cout << "Data succesfully saved!" << endl;
    }
    else {
        cerr << "Error. File could not be opened!" << endl;
    }

    fout.close();
}

void Qalgorithm::LoadData(string inputFile) {
    ifstream fin;

    fin.open(inputFile);
    string episodes;

    if (fin.is_open()) {
        
        fin >> episodes;
        fin >> alpha;
        fin >> gamma;
        fin >> epsilon;

        vector<string> loadedActions;
        string action;
        for (int i = 0; i < 9; i++) {
            fin >> action;
            loadedActions.push_back(action);
        }

        vector<string> loadedStates;
        string state;
        for (int i = 0; i < 2423; i++) {
            fin >> state;
            loadedStates.push_back(state);
        }
        table = new Qtable();
        table->constructTable(loadedActions, loadedStates);



        double rewardVal;

        for (int i = 0; i < table->getStates().size(); i++) {
            for (int j = 0; j < table->getActions().size(); j++) {
                fin >> rewardVal;
                table->setQValue(j, table->getStates()[i], rewardVal);
            }
        }

        cout << "Succesfully loaded the file" << endl;

        cout << "The number of episodes this algorithm trained on was: " << episodes << endl;
        cout << "Alpha value: " << alpha << endl;
        cout << "Gamma value: " << gamma << endl;
        cout << "Epsilon value: " << epsilon << endl;

        cout << "Resulting Q-table:" << endl;

        table->printTable();
    }
    else {
        cerr << "Error. Could not open file." << endl;
    }

    fin.close();
}