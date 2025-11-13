#include "Qnetwork.h"

using namespace std;

Qnetwork::Qnetwork(vector<int>& architecture, double learningRate, vector<vector<double>>& trainingData, vector<vector<double>>& labelData) : Neural_Network(architecture, trainingData, labelData, learningRate, 0, false) {
	
}

Qnetwork::~Qnetwork() {
    Layer* currentLayer = firstLayer;

    while (currentLayer != NULL) {
        Layer* deletePointer = currentLayer;
        currentLayer = currentLayer->getNextLayer();
        delete deletePointer;
        //deletePointer = 0 ?????
    }
}

vector<double> Qnetwork::predictQActions(vector<double>& input) {
	return predict(input);
}

void Qnetwork::backPropogate(double error) {
    //Go to the output layer and selectivly update the network until we can't go back anymore.
}