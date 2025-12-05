# Senior Thesis Repo: Reinforcement Learning in Tic-Tac-Toe
This repository is provided to help you build your senior thesis project. You will edit it to store your specification documents, code, and weekly checkins.

First, fork this repo (this makes a copy of it associated with your account) and then clone it to your machine (this makes a copy of your fork on your personal machine). You can then use an editor and a GitHub client to manage the repository.

#### Images
If you would like to add images to a Markdown file, place them in the ```docs/images/``` directory in this repo and reference them using markdown like this:

```
![alt text](relative/path/to/image)
```

Here is how to add the Carthage logo to a Markdown file (you can see the image in the repo right now):

```
![Carthage Firebird Logo](docs/images/firebirdLogo.jpg)
```
![Carthage Firebird Logo](docs/images/firebirdLogo.jpg)

This ensures that images are correctly linked and displayed when viewing the documentation on GitHub or any Markdown-supported platform.

## Code
The ```code``` directory is used to store your code. You can put it all in one directory or you can create subdirectories.

I have added a ```main.cpp``` file to get you started. Feel free to remove it.

If you have any questions feel free to ask me! I'll answer professor questions, customer questions, and give advice if asked.

# Sample Spec

Below is an example of a project specification.  

## Software Requirements Specification for a Deep Q-learning program

## Introduction

### Purpose
The purpose of this document is to outline the methods and concepts used to create a program that can learn to play the game Tic-Tac-Toe. This includes Q-learning, a method of training a program to take the best actions that result in the highest rewards. I will also be utilizing a Neural Network to change our algorithm into a Deep Q-learning method. 

The key goals of the program are:
- To properly utilize Q-learning to play Tic-Tac-Toe
- To properly utilize Neural Networks in Deep Q-learning to play Tic-Tac-Toe
- To give me experience in the Machine Learning area of Reinforcement Learning

### Scope
This program is intended to learn how to play simple games through deep Q-learning/reinforcement learning. The system will handle:
- Playing games of Tic-Tac-Toe with Q-learning or Deep Q-learning
- Saving/Loading of created "models"

### Definitions, Acronyms, and Abbreviations
DQN -> Deep Q Network
Q-table -> storage of our data that determines the "quality" of specific state/action combos.
NN -> Neural Network
MSE -> Means Squared Error


## Overview
Reinforcement learning is a sub-field in Machine Learning that aims to create a program that can learn the most optimal strategies to play simple games. We are utilizing a specific Reinforcement Learning method called Q-learning. It does this through a Q-table filled with different action/state combinations, with each combination containing a "quality" value. Over time, we update this value to get to a place where our table finalizes a table with the correct Q-values. We can go further than this and combine a Neural Network with Q-learning to complete larger and more dynamic problems where our environment is constantly changing. 

### System Features:
1. **Agent Training**: Allows for the newly initialized agent to learn the optimal ways to play a game of TicTacToe, either through Q-learning or Deep Q-learning.
2. **Game Playing**: Allows for a user to play a game with the AI Agent after training.
3. **Saving and Loading**: Allows for the user to save an agent's specific Q-table values/NN weights after training, and for future use if user does not desire to traing the Agent for a long period of time

## Use Cases

### Use Case 1.1: Training the Agent through Q-learning
- **Actors**: AI Agent and "Randomly-Selecting" Agent
- **Overview**: The AI agent will pick actions, go through with them, and record/update results in it's Q-table. The random agent also randomly plays actions, which is also "recorded and updated".

**Typical Course of Events**
1. Greedy-Epsilon Selection of action to take.
2. AI Agent takes the action.
3. Records result of action (new state/action q-values, reward for taking action).
4. Updates Q-table value of the state/action pair just taken.
5. "Randomly-Selecting" Agent plays in an empty spot, and it's results are recorded and updated.
6. Reduce our Greedy-Epsilon value by a very, very small amount.
7. Go back to step 1, repeat an "episode-count" amount of times.

**Alternative Courses**
- **Steps 4/5**: AI Agent or "Randomly-Selecting" agent force the board into a terminal state
  1. Record results (-1.0 reward for AI loss, 1.0 reward for AI win, 0.0 reward for Tie, and set our next state to our current state)
  2. Update Q-values accordingly
  3. Reset our Tic-Tac-Toe board to be empty

### Use Case 1.2: Tic-Tac-Toe Game with Base Q-learning
- **Actors**: Human Player and AI Agent.
- **Overview**: The human player plays games of Tic Tac Toe against a program that utilizes a basic Q-learning algorithm.

**Typical Course of Events**:
1. Computer program will go first.
2. The program will go through a Q-learning table, and pick the highest value to determine the best course of action to win.
3. Player then takes their turn
4. The Process repeats until either one looses or a tie is reached.

**Alternative Courses**:
- **Steps 1/2**: User enters coordinates that do not correspong to an existing/open position.
  1. Displays error - Not a valid position [if taken - position is already filled, choose a different position] [if non-existent - position is outside of the Tic Tac Toe Board, choose a different position].
  2. Go back to step 2.
 

### Use Case 1.3: Training the Agent throught Deep Q-learning
- **Actors**: AI Agent and "Randomly-Selecting" Agent
- **Overview**: The AI agent will first create experience replays, sample a selection of them, and train the Policy Neural Network on them through back-propagating the result of a MSE loss of the specific experience you are utilizing. The random agent also randomly plays actions to ensure the board state is primed for the AI Agent's turn.

**Typical Course of Events**
1. Program generates an experience replay (Using a Epsilon-Greedy method), recording the starting state, the resulting state, the action taken to get there, and the reward for taking that action in that state.
2. Randomly-Selecting Agent plays an avaliable action, updating the board so it's always the AI agent's turn
3. Stores experiences in the Experience Replay Buffer
4. Reduce our Greedy-Epsilon value by a very, very small amount.
5. Training function samples these experiences, taking a set amount of them randomly.
6. Converts starting state of select experience into doubles, before feeding them into our Policy NN to get action double results. Adjust results to mask invalid actions
7. Set a variable to our selected action in the current experience
8. Repeat Step 6 for our Target NN.
9. Take the highest output for the Target NN, and using our MSE loss equation, retrieve an error. 
10. We backpropagate this error on the current experience's action output Neuron in our Policy NN.
11. Go back to step 1, repeat an "episode-count" amount of times. Every 100 iterations, update our Target NN to have the same weights as our Policy NN.

**Alternative Courses**
- **Steps 1/2**: AI Agent or "Randomly-Selecting" Agent brings the board to a terminal state
  1. If AI Agent wins, set reward to 1.0, if we get a draw, set reward to -0.1, if AI Agent loses, set reward to -1.0
  2. Record our Experience accordingly
  3. Reset our Tic-Tac-Toe board to be empty
     
- **Step 5**: Experience Replay Buffer is smaller than our set batch size for experiences to sample
  1. Select an amount of random replays based on the current buffers size, and proceed as usual.
     
- **Step 5**L Experience Replay Buffer is full
  1. Delete the first experience, and proceed as usual
     
- **Step 9**: our current board state is now terminal
  1. Instead of using an MSE loss equation, just set the error to be our reward value, and proceed as usual

### Use Case 1.4: Tic-Tac-Toe Game with Deep Q-learning
- **Actors**: Human Player and AI Agent.
- **Overview**: The human player plays games of Tic Tac Toe against a program that utilizes a Deep Q-learning algorithm.

**Typical Course of Events**:
1. Computer program will go first.
2. The program will translate the Tic-Tac-Toe board into doubles, feed it into a Neural Network, and pick the highest value output Neuron to determine the best course of action to win.
3. Player then takes their turn
4. The Process repeats until either one looses or a tie is reached.

**Alternative Courses**:
- **Steps 1/2**: User enters coordinates that do not correspong to an existing/open position.
  1. Displays error - Not a valid position [if taken - position is already filled, choose a different position] [if non-existent - position is outside of the Tic Tac Toe Board, choose a different position].
  2. Go back to step 2.
