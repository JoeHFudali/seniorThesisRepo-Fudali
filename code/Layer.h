#pragma once
#include "Neuron.h"
#include <vector>

using namespace std;

class Layer {
public:
    Layer();
    Layer(int numOfInputs, int numOfOutputs);

    virtual void feedForward(vector<double>& layerInputs, vector<double>& networkOutputs);
    virtual void backPropagate(vector<double>& errors);
    void moveFroward(vector<double>& layerInputs, vector<double>& predictedOutputs);

    void setNextLayer(Layer* nl);
    Layer* getNextLayer();
    void setPreviousLayer(Layer* pl);
    Layer* getPreviousLayer();

    void setLayerInputs(vector<double>& inputs);
    vector<double> getLayerInputs();
    void setLayerOutputs(vector<double>& outputs);
    vector<double> getLayerOutputs();

    static double getLearningRate();
    static void setLearningRate(double lr);
    
private:

    vector<Neuron> Neurons;
    vector<double> layerInputs;
    vector<double> layerOutputs;
    Layer* nextLayer;
    Layer* previousLayer;
    static double learningRate;

};