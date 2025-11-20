#include "Qnetwork.h"
#include <iostream>
#include "Neuron.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"


using namespace std;

Qnetwork::Qnetwork(vector<int>& architecture, double lr, int nti) {
    numberOfTrainingIterations = nti;

    Layer::setLearningRate(lr);

    Layer* currentLayer = new InputLayer(architecture[0]);
    firstLayer = currentLayer;

    for (int i = 1; i < architecture.size() - 1; i++) {
        Layer* nextLayer = new HiddenLayer(architecture[i - 1], architecture[i]);
        currentLayer->setNextLayer(nextLayer);
        currentLayer = nextLayer;
    }

    currentLayer->setNextLayer(new OutputLayer(architecture[architecture.size() - 2], architecture[architecture.size() - 1]));

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

void Qnetwork::copyNetwork(Qnetwork* networkToCopyFrom) {
    Layer* currentOutsideLayer = networkToCopyFrom->firstLayer;
    Layer* currentLayer = firstLayer;

    while (currentOutsideLayer != NULL) {
        Layer layerInfo = *currentOutsideLayer;
        *currentLayer = layerInfo;

        currentLayer = currentLayer->getNextLayer();
        currentOutsideLayer = currentOutsideLayer->getNextLayer();
    }
}

vector<double> Qnetwork::predictQActions(vector<double>& input) {
    vector<double> results;
    firstLayer->getNextLayer()->moveFroward(input, results);
    return results;
}

void Qnetwork::adjustNetwork(double error, int action, vector<double> state) {
    vector<double> results;
    firstLayer->getNextLayer()->moveForwardQ(state, results, error, action);
    

    //Go to the output layer and selectivly update the network until we can't go back anymore.
}

int Qnetwork::getTrainingIterations() {
    return numberOfTrainingIterations;
}