#include <iostream>
#include "Problem3.cpp"
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <ctime>
#include <unordered_map>

using namespace std;

vector<vector<int>> initial_state;
vector<vector<int>> goal_state = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};


void createPuzzle(int x){
    if(x == 0){
        initial_state = {{0, 1, 2}, {3, 6, 8}, {4, 7, 5}};
    }
    else{
        cout << "Enter your own puzzle:\n";
        int tile1, tile2, tile3;
        cout << "Enter first row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v1;
        v1.push_back(tile1);
        v1.push_back(tile2);
        v1.push_back(tile3);
        initial_state.push_back(v1);
        cout << "Enter second row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v2;
        v2.push_back(tile1);
        v2.push_back(tile2);
        v2.push_back(tile3);
        initial_state.push_back(v2);
        cout << "Enter third row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v3;
        v3.push_back(tile1);
        v3.push_back(tile2);
        v3.push_back(tile3);
        initial_state.push_back(v3);           
    }
}

void algorithmChoice(int x){
    int time_start;
    int time_end;
    int time;
    Problem problem(initial_state, goal_state);
    cout << "Now choose the algorithm: " << endl;
    cout << "\t0 - Uniform Cost Search" << endl;
    cout << "\t1 - A* with the Misplaced Tile Heuristic" << endl;
    cout << "\t2 - A* with the Euclidean Distance Heuristic" << endl;
    cin >> x;
    if(x == 0){
        cout << "Thank you for choosing: A* with the Misplaced Tile Heuristic" << endl;
        cout << "The Goal State: " << endl;
        for (int i = 0; i < goal_state.size(); ++i) {
        for (int j = 0; j < goal_state[i].size(); ++j) {
            cout << goal_state[i][j] << " ";
        }
        cout << endl;
        }
        cout << endl;
        cout << "Initial State: " << endl;
        for (int i = 0; i < initial_state.size(); ++i) {
        for (int j = 0; j < initial_state[i].size(); ++j) {
            cout << initial_state[i][j] << " ";
        }
        cout << endl;
        }
        cout << endl;
        time_start = clock();
        vector<Operator> solution = UniformCostSearch(problem);
        time_end = clock();
        time = time_end - time_start;
        unordered_map<Operator, string> operatorString;
        int i = 0;
        for (Operator op : problem.get_operators()) {
        if (i == 0) {
            operatorString[op] = "MOVE_LEFT";
        }
        else if (i == 1) {
            operatorString[op] = "MOVE_RIGHT";
        }
        else if (i == 2) {
            operatorString[op] = "MOVE_UP";
        }
        else if (i == 3) {
            operatorString[op] = "MOVE_DOWN";
        }
        else if (i == 4) {
            operatorString[op] = "NONE";
        }
        ++i; 
    }

        cout << "The Solution Is: " << endl;
        for (int i = 0; i < solution.size(); ++i) {
        cout << operatorString[solution[i]] << "  ";
        } 
        cout << "Took " << time << " ms" << endl;
    }
    else if(x == 1){
        cout << "Thank you for choosing: A* with the Misplaced Tile Heuristic" << endl;
        cout << "The Goal State: " << endl;
        for (int i = 0; i < goal_state.size(); ++i) {
        for (int j = 0; j < goal_state[i].size(); ++j) {
            cout << goal_state[i][j] << " ";
        }
        cout << endl;}
        cout << endl;
        cout << "Initial State: " << endl;
        for (int i = 0; i < initial_state.size(); ++i) {
        for (int j = 0; j < initial_state[i].size(); ++j) {
            cout << initial_state[i][j] << " ";
        }
        cout << endl;
        }
        cout << endl;
        time_start = clock();
        vector<Operator> solution  = A_Star_MisplacedTile(problem);
        time_end = clock();
        time = time_end - time_start;
        unordered_map<Operator, string> operatorString;
     int i = 0;
        for (Operator op : problem.get_operators()) {
        if (i == 0) {
            operatorString[op] = "MOVE_LEFT";
        }
        else if (i == 1) {
            operatorString[op] = "MOVE_RIGHT";
        }
        else if (i == 2) {
            operatorString[op] = "MOVE_UP";
        }
        else if (i == 3) {
            operatorString[op] = "MOVE_DOWN";
        }
        else if (i == 4) {
            operatorString[op] = "NONE";
        }
        ++i; 
    }

        cout << "The Solution Is: " << endl;
        for (int i = 0; i < solution.size(); ++i) {
        cout << operatorString[solution[i]] << "  ";
    } 
        cout << "Took " << time << " ms" << endl;
    }
    else if (x == 2){
        cout << "Thank you for choosing: A* with the Misplaced Tile Heuristic" << endl;
        cout << "The Goal State: " << endl;
        for (int i = 0; i < goal_state.size(); ++i) {
        for (int j = 0; j < goal_state[i].size(); ++j) {
            cout << goal_state[i][j] << " ";
        }
        cout << endl;}
        cout << endl;
        cout << "Initial State: " << endl;
        for (int i = 0; i < initial_state.size(); ++i) {
        for (int j = 0; j < initial_state[i].size(); ++j) {
            cout << initial_state[i][j] << " ";
        }
        cout << endl;
        }
        cout << endl;
        time_start = clock();
        vector<Operator> solution = A_Star_EuclideanDistance(problem);
        time_end = clock();
        time = time_end - time_start;
        unordered_map<Operator, string> operatorString;
        int i = 0;
        for (Operator op : problem.get_operators()) {
        if (i == 0) {
            operatorString[op] = "MOVE_LEFT";
        }
        else if (i == 1) {
            operatorString[op] = "MOVE_RIGHT";
        }
        else if (i == 2) {
            operatorString[op] = "MOVE_UP";
        }
        else if (i == 3) {
            operatorString[op] = "MOVE_DOWN";
        }
        else if (i == 4) {
            operatorString[op] = "NONE";
        }
        ++i; 
    }

        cout << "The Solution Is: " << endl;
        for (int i = 0; i < solution.size(); ++i) {
        cout << operatorString[solution[i]] << "  ";
    } 
        cout << "Took " << time << " ms" << endl;
    }
    
}

void intro(){
    int choice;

    cout << "Welcome to the CS170 - AI Project 1. This project is attempting to solve several puzzles ";
    cout << "using different algorithm types. Please wait as we list out the possible options to choose: " << endl; //random dialog
    cout << "First please choose from the following: "<< endl;
    cout << "\t0 - Use Default Puzzle" << endl;
    cout << "\t1 - Enter Your Own Puzzle" << endl;
    cout << "Choice: ";
    cin >> choice;

    createPuzzle(choice);
    if(choice == 0){
        cout << "Thank you for choosing the Default Puzzle" << endl;
    }
    else if(choice == 1){
        cout << "Thank you for Creating Your Own Puzzle" << endl;
    }
    algorithmChoice(choice);
}
