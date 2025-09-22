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
- **Registrar**: The official responsible for maintaining student records, managing course schedules, and overseeing the registration process.
- **Student Information System (SIS)**: A university-wide database that stores student records, course information, and academic data.
- **GPA**: Grade Point Average, a numerical representation of a student's academic performance.
- **Semester**: A division of the academic year, typically consisting of a Fall and Spring term, in which courses are offered and completed.
- **Waitlist**: A system that allows students to reserve a spot in a full course, subject to availability if another student drops the course.
- **Prerequisite**: A course or requirement that must be completed before a student can enroll in a more advanced course.
- **User Role**: A designation for system access levels, such as student, registrar, or faculty member, each with different permissions within the system.
- **Concurrent Enrollment**: The ability for students to be enrolled in multiple courses during the same academic term.

## Overview
The Mahoney University Registration System is a web-based platform designed to automate the course registration process for students and faculty. It serves as the primary interface for students to manage their academic schedules and for university staff to oversee the course offerings and registration workflows.

### System Features:
1. **Secure Login**: Ensures that only authorized users (students, faculty, and staff) have access to the system, with user authentication based on university credentials.
2. **Course Search**: Allows students to browse available courses by department, term, and subject, with filtering options based on course availability, schedule, and prerequisites.
3. **Course Registration**: Students can add or drop courses, view class schedules, and receive notifications of any conflicts or unmet prerequisites.
4. **Grades and Transcripts**: Provides students with access to their grades from current and past semesters, as well as the ability to request official transcripts.
5. **Registrar Management Tools**: The Registrar’s Office can create, modify, and delete course sections, set enrollment limits, and manage waitlists.

The system is designed with scalability in mind, allowing it to handle thousands of students registering simultaneously during peak periods. It will integrate with the university’s existing Student Information System (SIS) and is built using modern web technologies to ensure ease of use, reliability, and performance.

The following sections detail the specific use cases that the system will support, describing how students and staff will interact with the system during typical operations.

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
