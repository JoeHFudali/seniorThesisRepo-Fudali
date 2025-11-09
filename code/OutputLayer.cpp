#include "OutputLayer.h"
#include <iostream>

using namespace std;

OutputLayer::OutputLayer(int numOfInputs, int numOfOutputs) : Layer(numOfInputs, numOfOutputs) {
    //do nothing
}

void OutputLayer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs) {
    Layer::feedForward(layerInputs, networkOutputs);

    vector<double> neuronOutputs = getLayerOutputs();
    vector<double> errors;

    for(int i = 0; i < neuronOutputs.size(); i++) {
        errors.push_back(networkOutputs[i] - neuronOutputs[i]);
    }

    backPropagate(errors);
}