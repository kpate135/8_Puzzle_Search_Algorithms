#include <iostream>
#include <string>
#include <vector>
#include "puzzle.cpp"
using namespace std;

void StartInit(){ //introduction prompt
    puzzle x;

    int userChoice;
    cout << "Welcome to the CS170 - AI Project 1. This project is attempting to solve several puzzles ";
    cout << "using different algorithm types. Please wait as we list out the possible options to choose: " << endl; //random dialog
    cout << "First please choose from the following: "<< endl;
    cout << "\t0 - Use Default Puzzle" << endl;
    cout << "\t1 - Enter Your Own Puzzle" << endl;
    cout << "Choice: ";
    cin >> userChoice;

    if(userChoice == 1 || userChoice == 0){
        x.makePuzzle(userChoice);
    }
    else {
        cout << "User Choice For Puzzle Not Accepted...Restarting Program..." << endl;
        cout << endl;
        StartInit();
        }
    cout << endl;
    cout << "Now choose the algorithm: " << endl;
    cout << "\t0 - Uniform Cost Search" << endl;
    cout << "\t1 - A* with the Misplaced Tile Heuristic" << endl;
    cout << "\t2 - A* with the Euclidean Distance Heuristic" << endl;
    cin >> userChoice;

    if( userChoice == 0 || userChoice == 1 || userChoice == 2){
        //call Uniform Cost Algorith,
        x.algorithmChoice(userChoice);
    }
    else{
        cout << "User Choice For Algorithm Not Accepted...Restarting Program..." << endl;
        cout << endl;
        StartInit();
    }
}