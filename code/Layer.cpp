#include "Layer.h"

double Layer::learningRate = 0.5;

Layer::Layer() {
    nextLayer = NULL;
    previousLayer = NULL;
}

Layer::Layer(int numOfInputs, int numOfOutputs) {
    for(int i = 0; i < numOfOutputs; i++) {
        Neuron newNeuron(numOfInputs);
        Neurons.push_back(newNeuron);
    }

    nextLayer = NULL;
    previousLayer = NULL;
}

void Layer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs) {
    vector<double> neuronOutputs;

    setLayerInputs(layerInputs);

    for(int neuronIndex = 0; neuronIndex < Neurons.size(); neuronIndex++) {
        Neurons[neuronIndex].activate(layerInputs);
        neuronOutputs.push_back(Neurons[neuronIndex].getActivationValue());

    }

    setLayerOutputs(neuronOutputs);
}

void Layer::moveFroward(vector<double>& layerInputs, vector<double>& predicatedOutputs) {
    vector<double> neuronOutputs;

    for(int neuronIndex = 0; neuronIndex < Neurons.size(); neuronIndex++) {
        Neurons[neuronIndex].activate(layerInputs);
        neuronOutputs.push_back(Neurons[neuronIndex].getActivationValue());
    }

    if(getNextLayer() != NULL) {
        getNextLayer()->moveFroward(neuronOutputs, predicatedOutputs);
    }
    else {
        predicatedOutputs = neuronOutputs;
    }


}

void Layer::moveForwardQ(vector<double>& layerInputs, vector<double>& predictedOutputs, double error, int action) {
    vector<double> neuronOutputs;

    setLayerInputs(layerInputs);

    for (int neuronIndex = 0; neuronIndex < Neurons.size(); neuronIndex++) {
        Neurons[neuronIndex].activate(layerInputs);
        neuronOutputs.push_back(Neurons[neuronIndex].getActivationValue());
    }
    setLayerOutputs(neuronOutputs);

    if (getNextLayer() != NULL) {

        getNextLayer()->moveForwardQ(neuronOutputs, predictedOutputs, error, action);
    }
    else {
        prepareBackPropogation(error, action);
    }
}

void Layer::moveForwardQ(vector<double>& layerInputs, vector<double>& predictedOutputs, vector<double> errors, int action) {
    vector<double> neuronOutputs;

    setLayerInputs(layerInputs);

    for (int neuronIndex = 0; neuronIndex < Neurons.size(); neuronIndex++) {
        Neurons[neuronIndex].activate(layerInputs);
        neuronOutputs.push_back(Neurons[neuronIndex].getActivationValue());
    }
    setLayerOutputs(neuronOutputs);

    if (getNextLayer() != NULL) {

        getNextLayer()->moveForwardQ(neuronOutputs, predictedOutputs, errors, action);
    }
    else {
        backPropagate(errors);
    }
}

void Layer::prepareBackPropogation(double error, int action) {

    vector<double> newErrors(Neurons[action].getWeights().size() - 1);
    for (int i = 0; i < newErrors.size(); i++) {
        newErrors[i] = 0.0;
    }

    vector<double> inputs = getLayerInputs();
    inputs.insert(inputs.begin(), 1.0);

    vector<double> newWeights = Neurons[action].getWeights();

    for (int weightIndex = 1; weightIndex < newWeights.size(); weightIndex++) {
        newErrors[weightIndex - 1] += (error * newWeights[weightIndex]);

    }


    for (int weightIndex = 0; weightIndex < newWeights.size(); weightIndex++) {
        newWeights[weightIndex] = newWeights[weightIndex] + (getLearningRate() * error * inputs[weightIndex]);

    }

    Neurons[action].setWeights(newWeights);
    getPreviousLayer()->backPropagate(newErrors);
}


void Layer::backPropagate(vector<double>& errors) {

    

    vector<double> newErrors(getLayerInputs().size());
    for(int i = 0; i < getLayerInputs().size(); i++) {
        newErrors[i] = 0.0;
    }

    vector<double> inputs = getLayerInputs();
    inputs.insert(inputs.begin(), 1.0);

    for(int neuronIndex = 0; neuronIndex < Neurons.size(); neuronIndex++) {
        Neurons[neuronIndex].calculateError(errors[neuronIndex]);

        vector<double> weights = Neurons[neuronIndex].getWeights();

        for(int weightIndex = 1; weightIndex < weights.size(); weightIndex++) {
            newErrors[weightIndex - 1] += (Neurons[neuronIndex].getError() * weights[weightIndex]);

        }

        for(int weightIndex = 0; weightIndex < weights.size(); weightIndex++) {
            weights[weightIndex] = weights[weightIndex] + (getLearningRate() * Neurons[neuronIndex].getError() * inputs[weightIndex]);

        }

        Neurons[neuronIndex].setWeights(weights);
    }
    
    getPreviousLayer()->backPropagate(newErrors);
}

void Layer::setLayerInputs(vector<double>& inputs) {
    layerInputs.clear();
    layerInputs.insert(layerInputs.end(), inputs.begin(), inputs.end());
}

vector<double> Layer::getLayerInputs() {
    return layerInputs;
}

void Layer::setLayerOutputs(vector<double>& outputs) {
    layerOutputs.clear();
    layerOutputs.insert(layerOutputs.end(), outputs.begin(), outputs.end());
}

vector<double> Layer::getLayerOutputs() {
    return layerOutputs;
}

void Layer::setNextLayer(Layer* nl) {
    nextLayer = nl;
    nextLayer->setPreviousLayer(this);
}

void Layer::setPreviousLayer(Layer* pl) {
    previousLayer = pl;
}

Layer* Layer::getNextLayer() {
    return nextLayer;
}

Layer* Layer::getPreviousLayer() {
    return previousLayer;
}

double Layer::getLearningRate() {
    return learningRate;
}

void Layer::setLearningRate(double lr) {
    learningRate = lr;
}

Neuron Layer::getNeuron(int index) {
    return Neurons[index];
}

void Layer::setNeuronWeights(int index, vector<double> value) {
    Neurons[index].setWeights(value);
}

int Layer::getNumberNeurons() {
    return Neurons.size();
}

