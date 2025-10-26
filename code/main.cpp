#include <iostream>
#include "Qalgorithm.h"
#include <set>
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

    //Biggest questions for this are state generation/decision, difference between Q(A, S) and reward in our actual algorithm, and possible 
    //reworks to some functions in Qtable/Qalgorithm regarding actions

    set<string> uniqueBoardStrings;
    createBoardStrings(uniqueBoardStrings);
    //for (string board : uniqueBoardStrings) {
    //    cout << board << endl;
    //}
    cout << "Number of Unique Board Strings: " << uniqueBoardStrings.size() << endl;

    vector<string> boardStrings(uniqueBoardStrings.begin(), uniqueBoardStrings.end());
    cout << "works!" << endl;
    Qalgorithm al(0.1, 0.5, 0.2, {"Top Left", "Top Middle", "Top Right", "Middle Left", "Middle", "Middel Right", "Bottom Left", "Bottom Middle", "Bottom Right"}, boardStrings);

    //al.iterate(20);


    return 0;
}

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
                    boards.insert(child->board->getBoardString());

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
