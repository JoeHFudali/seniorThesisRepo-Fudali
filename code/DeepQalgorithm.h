#pragma once
#include <iostream>


using namespace std;

class DeepQalgorithm {
public:

	DeepQalgorithm();
	~DeepQalgorithm();


private:

	struct ExReplay {
		string startState;
		int action;
		double reward;
		string newState;
	};

	double epsilon;
	double alpha;
	double gamma;


};
