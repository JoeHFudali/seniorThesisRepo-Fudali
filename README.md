# Senior Thesis Repo: [something with using a Neural Network and Q-learning to play basic games optimally]
This repository is provided to help you build your senior thesis project. You will edit it to store your specification documents, code, and weekly checkins.

First, fork this repo (this makes a copy of it associated with your account) and then clone it to your machine (this makes a copy of your fork on your personal machine). You can then use an editor and a GitHub client to manage the repository.

### Markdown
This file is called README.md. It is a [Markdown file](https://en.wikipedia.org/wiki/Markdown). Markdown is a simple way to format documents. When a Markdown-ready viewer displays the contents of a file, it formats it to look like HTML. However, Markdown is significantly easier to write than HTML. VSCode supports displaying Markdown in a preview window. GitHub uses Markdown extensively including in every repo's description file, ```README.md```.

All Markdown files end with the extension ```.md```. There is a Markdown tutorial [here](https://www.markdowntutorial.com/) and a Markdown cheatsheet [here](https://www.markdownguide.org/cheat-sheet/).

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
The purpose of this document is to outline the methods and concepts used to create a program that can play basic games, from Tic Tac Toe up to ones on the Atari. This includes Q-learning/Q tables, a method of training a program to take the best actions that result in the highest rewards. I will also be utilizing a Neural Network to futher the Q-learning program into a deep Q-learning program, in order to further imporve the program's "game playing" ability. [add more later]

The key goals of the program are:
- To properly utilize Neural Networks
- To properly utilize Q-learning
- To connect both of the concepts above
- To use this program to play basic games
- W.I.P.

### Scope
This program is intended to learn how to play simple games through deep Q-learning/reinforcement learning. The system will handle:
- Base Tic Tac Toe.
- 5 by 5 Tic Tac Toe.
- Possibly Atari games.

### Definitions, Acronyms, and Abbreviations
W.I.P.

## Overview
Reinforcement learning is a sub-field in Machine Learning that aims to create a program that can learn the most optimal strategies to play simple games. It does this through Q-learning and a Q-table filled with different action/state combinations, with each combination containing a reward value. Over time, we update this value to get to a place where our table finalizes a table with the correct reward values. We can go further than this and combine a Neural Network with Q-learning to have the learning process both become more efficient and take much less time to complete [W.I.P.]

### System Features:
[W.I.P.]

## Use Cases

### Use Case 1.1: Base Tic Tac Toe
- **Actors**: Human Player and Reinforcement Learning Program.
- **Overview**: The human player plays games of Tic Tac Toe against a program that acts optimally.

**Typical Course of Events**:
1. A random "coin toss" determines who goes first, and that player puts down their first.
2. If the program went first, user continues with it's turn normally. If the player went first, the program will go through a Q-learning table, and use a Neural Network to determine the best course of action to win. 
3. The Process repeats until either one player looses or a tie is reached.

**Alternative Courses**:
- **Step 1/2**: User enters coordinates that do not correspong to an existing/open position.
  1. Displays error - Not a valid position [if taken - position is already filled, choose a different position] [if non-existent - position is outside of the Tic Tac Toe Board, choose a different position].
  2. Go back to step 2.

### Use Case 1.2: 5 by 5 Tic Tac Toe
- **Actors**: Human Player and Reinforcement Learning Program.
- **Overview**: The human player plays modified games of Tic Tac Toe (in this case, a 5 by 5 board instead of a 3 by 3 board) against a program that acts optimally.

**Typical Course of Events**:
1. A random "coin toss" determines who goes first, and that player puts down their first.
2. If the program went first, user continues with it's turn normally. If the player went first, the program will go through a Q-learning table, and use a Neural Network to determine the best course of action to win. (This will be expanded upon for the 5 by 5, mostly for the Neural Network/Q-table size)
3. The Process repeats until either one player looses or a tie is reached.

**Alternative Courses**:
- **Step 1/2**: User enters coordinates that do not correspong to an existing/open position.
  1. Displays error - Not a valid position [if taken - position is already filled, choose a different position] [if non-existent - position is outside of the Tic Tac Toe Board, choose a different position].
  2. Go back to step 2.

### Use Case 1.3: Atari Game (only if time permits)
- **Actors**: Reinforcement Learning Program.
- **Overview**: The Program will learning how to effectively play an Atari game.

**Typical Course of Events**:
1. Introduce the program to the game with only a base Q-table, and randomly set the weights for the Neural Network.
2. Have the program train on the game, updating the Q-table and weights for the N.N.
3. Run the Game at a point where the Q-table/N.N. weights have reached a state where the program has noticably imporved.

**Alternative Courses**:
- **Step ???**: W.I.P.
  1. 
