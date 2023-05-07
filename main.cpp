#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
//#include "eightpuzzle.cpp"
#include "Problem.cpp"
#include <unordered_map>

using namespace std;

int main()
{
    //StartInit();
    //vector<vector<int>> initial_state = {{1, 2, 3}, {0, 5, 6}, {7, 8, 4}};
    vector<vector<int>> initial_state = {{0, 1, 2}, {4, 5, 3}, {7, 8, 6}};
    cout << "Initial State: " << endl;
    for (int i = 0; i < initial_state.size(); ++i) {
        for (int j = 0; j < initial_state[i].size(); ++j) {
            cout << initial_state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    vector<vector<int>> goal_state = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    cout << "Goal State: " << endl;
    for (int i = 0; i < goal_state.size(); ++i) {
        for (int j = 0; j < goal_state[i].size(); ++j) {
            cout << goal_state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    Problem problem(initial_state, goal_state);
    //vector<Operator> solution = UniformCostSearch(problem);
    vector<Operator> solution = AStarMisH(problem);
    //vector<Operator> solution = AStarEucH(problem);
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

    return 0;
}