#include <iostream>
#include "Qalgorithm.h"
#include <set>
#include <random>
#include "DeepQalgorithm.h"
using namespace std;

struct Node {

    TicTacToeBoard* board;
    Node* parent;
    vector<Node*> children;
};

void createBoardStrings(set<string>& boards);
void createHelper(Node* pNode, set<string>& boards);

int main()
{
    srand(time(0));

    /*set<string> uniqueBoardStrings;
    createBoardStrings(uniqueBoardStrings);
    int episodes = 1000000;

    cout << "Number of Unique Board Strings: " << uniqueBoardStrings.size() << endl;

    vector<string> boardStrings(uniqueBoardStrings.begin(), uniqueBoardStrings.end());

    Qalgorithm al(0.5, 0.1, 0.9, {"TL", "TM", "TR", "ML", "MM", "MR", "BL", "BM", "BR"}, boardStrings);
    
    al.iterate(episodes);
    TicTacToeBoard::SQUARE_OCCUPANT player = TicTacToeBoard::SQUARE_OCCUPANT::O;
    

    char yOrN = 'y';
    while (yOrN == 'y') {
        cout << "Playing a TicTacToe game" << endl << endl;

        al.playGame(player);

        cout << "would you like to play again? (enter y for yes or any other key for no)" << endl;
        cin >> yOrN;
        cin.get();
    }

    al.getQtable()->printTable();*/

    string startingBoard = "---------";

    DeepQalgorithm DQN(0.000002, 0.9, 0.5, 3000, 8, 25000, {9, 10, 10, 9});
   
    DQN.trainNetworks();
    char yOrN = 'y';

    do {

        DQN.playGame(startingBoard);
        cout << "Would you like to play again?" << endl;
        cin >> yOrN;
        cin.get();

    } while (yOrN == 'y');
    

    return 0;
}

//Creates our string state labels
void createBoardStrings(set<string>& boards) {
    Node* nHead = new Node;

    nHead->parent = nullptr;
    nHead->board = new TicTacToeBoard("---------");
    boards.insert(nHead->board->getBoardString());

    createHelper(nHead, boards);

    delete nHead->board;
    nHead->board = 0;
    delete nHead;
    nHead = 0;

}

//Recurrsive helper to createBoardStrings
void createHelper(Node* pNode, set<string>& boards) {

    if (pNode->board->getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {

        TicTacToeBoard::PLAYER_TURN turn = pNode->board->getPlayerTurn();
        TicTacToeBoard::SQUARE_OCCUPANT mark;

        if (turn == TicTacToeBoard::PLAYER_TURN::O_TURN) {
            mark = TicTacToeBoard::O;
        }
        else {
            mark = TicTacToeBoard::X;
        }

        for (int row = 0; row < pNode->board->getBoardDimension(); row++) {
            for (int col = 0; col < pNode->board->getBoardDimension(); col++) {

                if (pNode->board->getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY) {
                    Node* child = new Node;
                    child->parent = pNode;

                    child->board = new TicTacToeBoard(pNode->board->getBoardString());
                    child->board->setSquare(row, col, mark);

                    if (child->board->getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN) {
                        if (child->board->getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
                            boards.insert(child->board->getBoardString());
                        }
                    }
                    
                    pNode->children.push_back(child);

                    createHelper(child, boards);

                    delete child->board;
                    child->board = 0;
                    delete child;
                    child = 0;
                }
            }
        }

    }

}