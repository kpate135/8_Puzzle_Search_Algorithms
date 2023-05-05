#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include "eightpuzzle.cpp"

using namespace std;

int main()
{
	puzzle x;

	int puzzleChoice = 0;
    cout << "Welcome to Project 3 8-puzzle solver.\n";
    cout << "Type \"1\" to enter a default puzzle, or \"2\" to enter your own puzzle\n";
    cin >> puzzleChoice;
	x.makePuzzle(puzzleChoice);

	int achoice = 0;
	cout << "Enter your choice of algorithm:\n";
	cout << "\t1) Uniform Cost Search\n";
	cout << "\t2) A* with Misplaced Tile Heuristic\n";
	cout << "\t3) A* with Euclidean distance heuristic\n";
	cin >> achoice;
	x.algorithmChoice(achoice);
    
    return 0;
}