#include <iostream>
#include "Qalgorithm.h"
using namespace std;

int main()
{

    //Biggest questions for this are state generation/decision, difference between Q(A, S) and reward in our actual algorithm, and possible 
    //reworks to some functions in Qtable/Qalgorithm regarding actions
    Qalgorithm al(0.1, 0.5, 0.2);

    al.iterate(20);

    return 0;
}
