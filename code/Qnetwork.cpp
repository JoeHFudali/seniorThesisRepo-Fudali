#include "Qnetwork.h"
#include <iostream>
#include "Neuron.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"


using namespace std;

Qnetwork::Qnetwork(vector<int>& architecture, double lr, int nti) {
    numberOfTrainingIterations = nti;
    generalArchitecture = architecture;

    Layer::setLearningRate(lr);

    Layer* currentLayer = new InputLayer(generalArchitecture[0]);
    firstLayer = currentLayer;

    for (int i = 1; i < generalArchitecture.size() - 1; i++) {
        Layer* nextLayer = new HiddenLayer(generalArchitecture[i - 1], generalArchitecture[i]);
        currentLayer->setNextLayer(nextLayer);
        currentLayer = nextLayer;
    }

    currentLayer->setNextLayer(new OutputLayer(generalArchitecture[generalArchitecture.size() - 2], generalArchitecture[generalArchitecture.size() - 1]));

}

Qnetwork::Qnetwork() {
    //Do nothing, will call constructor later
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
    Layer* currentLayer = firstLayer;

    while (currentLayer != NULL) {
        Layer* deletePointer = currentLayer;
        currentLayer = currentLayer->getNextLayer();
        delete deletePointer;
        deletePointer = 0;
    }

    currentLayer = new InputLayer(generalArchitecture[0]);
    firstLayer = currentLayer;

    for (int i = 1; i < generalArchitecture.size() - 1; i++) {
        Layer* nextLayer = new HiddenLayer(generalArchitecture[i - 1], generalArchitecture[i]);
        currentLayer->setNextLayer(nextLayer);
        currentLayer = nextLayer;
    }

    currentLayer->setNextLayer(new OutputLayer(generalArchitecture[generalArchitecture.size() - 2], generalArchitecture[generalArchitecture.size() - 1]));


    Layer* currentOutsideLayer = networkToCopyFrom->firstLayer->getNextLayer();
    currentLayer = firstLayer->getNextLayer();
    
    while (currentLayer != NULL) {
        for (int j = 0; j < currentLayer->getNumberNeurons(); j++) {
            const vector<double> newWeights = currentOutsideLayer->getNeuron(j).getWeights();
            currentLayer->setNeuronWeights(j, newWeights);
        }
        currentOutsideLayer = currentOutsideLayer->getNextLayer();
        currentLayer = currentLayer->getNextLayer();
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