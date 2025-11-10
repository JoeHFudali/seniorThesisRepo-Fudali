#include "Neural_Network.h"
#include <iostream>
#include "Neuron.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"

using namespace std;

Neural_Network::Neural_Network(vector<int>& architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti, bool doTrain) {
    numberOfTrainingIterations = nti;

    Layer::setLearningRate(lr);

    Layer* currentLayer = new InputLayer(architecture[0]);
    firstLayer = currentLayer;

    for(int i = 1; i < architecture.size() - 1; i++) {
        Layer* nextLayer = new HiddenLayer(architecture[i - 1], architecture[i]);
        currentLayer->setNextLayer(nextLayer);
        currentLayer = nextLayer;
    }
    
    currentLayer->setNextLayer(new OutputLayer(architecture[architecture.size() - 2], architecture[architecture.size() - 1]));

    if (doTrain) {
        train(trainingData, labelData);
    }
    
}




Neural_Network::~Neural_Network() {
    Layer* currentLayer = firstLayer;

    while(currentLayer != NULL) {
        Layer* deletePointer = currentLayer;
        currentLayer = currentLayer->getNextLayer();
        delete deletePointer;
        //deletePointer = 0 ?????
    }
}

void Neural_Network::train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData) {
    for(int iterNum = 0; iterNum < numberOfTrainingIterations; iterNum++) {
        for(int i = 0; i < trainingData.size(); i++) {
            firstLayer->feedForward(trainingData[i], labelData[i]);
        }
    }
}

vector<double> Neural_Network::predict(vector<double>& input) {
    vector<double> results;
    firstLayer->getNextLayer()->moveFroward(input, results);
    return results;
}