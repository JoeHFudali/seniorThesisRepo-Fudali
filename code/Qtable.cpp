#include "Qtable.h"
#include <vector>

using namespace std;

Qtable::Qtable() {
    actions = {"Top Left", "Top Middle", "Top Right", 
               "Middle Left", "Middle", "Middle Right",
               "Bottom Left", "Bottom Middle", "Bottom Right"};

    //We will initialize states to have all combinations of taken spots.
    //This won't account for type of symbol (X or O), just how many are taken
    //and where they are taken.

    for(int i = 0; i < states.size(); i++) {
        for(int j = 0; j < actions.size(); j++) {
            rewards[i][j] = 0.0;
        }
    }
}