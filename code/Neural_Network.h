#pragma once
#include <vector>
#include "Layer.h"

using namespace std;

class Neural_Network {
public:
    Neural_Network(vector<int>& architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti, bool doTrain);
    ~Neural_Network();
    vector<double> predict(vector<double>& input);


private:
    Layer* firstLayer;
    double learningRate;
    int numberOfTrainingIterations;

    void train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
};