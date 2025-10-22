#include <iostream>
#include "Qalgorithm.h"
using namespace std;

int main()
{
    Qalgorithm al(0.1, 0.5, 0.2);

    al.iterate(20);

    return 0;
}
