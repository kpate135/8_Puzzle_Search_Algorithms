#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
//#include "eightpuzzle.cpp"
#include "Problem.cpp"
#include <unordered_map>
#include <ctime>

using namespace std;

int main()
{
    //StartInit();
    //vector<vector<int>> initial_state = {{1, 2, 3}, {0, 5, 6}, {7, 8, 4}}; 
    //vector<vector<int>> initial_state = {{1, 2, 0}, {4, 5, 3}, {7, 8, 6}}; //Easy
    vector<vector<int>> initial_state = {{0, 1, 2}, {4, 5, 3}, {7, 8, 6}}; //doable
    //vector<vector<int>> initial_state = {{8, 7, 1}, {6, 0, 2}, {5, 4, 3}}; //Oh Boy

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

    int time_start_uniform = clock();
    vector<Operator> solution = UniformCostSearch(problem);
    int time_end_uniform = clock();
    int time_uniform = time_end_uniform - time_start_uniform;
    cout << "Uniform Cost Search took " << time_uniform << "ms." << endl;

    cout << "The Uniform Cost Search Solution Is: " << endl; //print solution
    for (int i = 0; i < solution.size(); ++i) {
        Operator op = solution[i];
        switch (op) {
            case Operator::MOVE_LEFT:
                cout << "MOVE_LEFT" << " ";
                break;
            case Operator::MOVE_RIGHT:
                cout << "MOVE_RIGHT" << " ";
                break;
            case Operator::MOVE_UP:
                cout << "MOVE_UP" << " ";
                break;
            case Operator::MOVE_DOWN:
                cout << "MOVE_DOWN" << " ";
                break;
            case Operator::NONE:
                cout << "NONE" << " ";
                break;
            default:
                break;
        }        
    }
    cout << endl << endl;

    int time_start_misplaced = clock();
    vector<Operator> solutionMisplaced = A_Star_MisplacedTile(problem);
    int time_end_misplaced = clock();
    int time_misplaced = time_end_misplaced - time_start_misplaced;
    cout << "Misplaced Search took " << time_misplaced << "ms." << endl;

    cout << "The A* Misplaced Tile Heuristic Solution Is: " << endl; //print solution
    for (int i = 0; i < solutionMisplaced.size(); ++i) {
        Operator op = solutionMisplaced[i];
        switch (op) {
            case Operator::MOVE_LEFT:
                cout << "MOVE_LEFT" << " ";
                break;
            case Operator::MOVE_RIGHT:
                cout << "MOVE_RIGHT" << " ";
                break;
            case Operator::MOVE_UP:
                cout << "MOVE_UP" << " ";
                break;
            case Operator::MOVE_DOWN:
                cout << "MOVE_DOWN" << " ";
                break;
            case Operator::NONE:
                cout << "NONE" << " ";
                break;
            default:
                break;
        }        
    }
    cout << endl << endl;   

    int time_start_euclidean = clock();
    vector<Operator> solutionEuclidean = A_Star_EuclideanDistance(problem);
    int time_end_euclidean = clock();
    int time_euclidean = time_end_euclidean - time_start_euclidean;
    cout << "Euclidean Search took " << time_euclidean << "ms." << endl;

    cout << "The A* Euclidean Distance Heuristic Solution Is: " << endl; //print solution
    for (int i = 0; i < solutionEuclidean.size(); ++i) {
        Operator op = solutionEuclidean[i];
        switch (op) {
            case Operator::MOVE_LEFT:
                cout << "MOVE_LEFT" << " ";
                break;
            case Operator::MOVE_RIGHT:
                cout << "MOVE_RIGHT" << " ";
                break;
            case Operator::MOVE_UP:
                cout << "MOVE_UP" << " ";
                break;
            case Operator::MOVE_DOWN:
                cout << "MOVE_DOWN" << " ";
                break;
            case Operator::NONE:
                cout << "NONE" << " ";
                break;
            default:
                break;
        }        
    }
    cout << endl << endl;   

    return 0;
}