#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <cmath>
#include "problem.cpp"
#include "eightpuzzle.h"

using namespace std;

puzzle::puzzle(){
    root = NULL;
}

void puzzle::makePuzzle(int x){
    tile* t = new tile;
    t->child1 = NULL;
    t->child2 = NULL;
    t->child3 = NULL;
    t->child4 = NULL;
    t->parent = NULL;
    t->heuristic = 0;
    t->moveCost = 0;
    if(x == 1){
        cout << "Default puzzle will be:\n";
		vector<int> vec1;
		vec1.push_back('1');
		vec1.push_back('2');
		vec1.push_back('*');
		vector<int> vec2;
		vec2.push_back('4');
		vec2.push_back('5');
		vec2.push_back('6');
		vector<int> vec3;
		vec3.push_back('7');
		vec3.push_back('5');
		vec3.push_back('8');
		t->eightpuz.push_back(vec1);
		t->eightpuz.push_back(vec2);
		t->eightpuz.push_back(vec3);

		root = t;
		q.push(root);
		list.push_back(root->eightpuz);
		printPuzzle(root);
    }
    if(x == 2){
        cout << "Enter your own puzzle:\n";
        int tile1, tile2, tile3;
        cout << "Enter first row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v1;
        v1.push_back(tile1);
        v1.push_back(tile2);
        v1.push_back(tile3);
        t->eightpuz.push_back(v1);
        cout << "Enter second row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v2;
        v2.push_back(tile1);
        v2.push_back(tile2);
        v2.push_back(tile3);
        t->eightpuz.push_back(v2);
        cout << "Enter third row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<int> v3;
        v3.push_back(tile1);
        v3.push_back(tile2);
        v3.push_back(tile3);
        t->eightpuz.push_back(v3);                
    }
}

bool puzzle::validPuzzle(tile* curr){ //checks valid puzzle 1-9 i - k for 3 values 
    bool valid = false;
    for(int i = 1; i < 9; ++i){
        for(int j = 0; i < 3; j++){
            for(int k = 0; k < 3; k++){
                if(curr->eightpuz.at(i).at(j) == (char)k || curr->eightpuz.at(i).at(j) == '*'){
                    valid = true;
                }
                if((i == 2) && (j == 2) && valid == false){
                    return false; 
                }
            }
        }
        valid = false;
    }
    return true;
}

void puzzle::algorithmChoice(int x){
    if(root == NULL){
        cout << "No puzzle" << endl;
        return;
    }
    if(!validPuzzle(root)){
        cout << "Puzzle is not valid" << endl;
        return;
    }
    choice = x;
    //cout << "Choose your algorithm: 1 is for Uniform Cost Search, 2 is for Misplaced Tile Heuristic and 3 is for Euclidean distance heuristic"<< endl;
    if(choice == 1){
        vector<vector<int>> goal_puzzle;
        const int arr1[] = {1 ,2 , 3};
        const int arr2[] = {4 ,5 , 6};
        const int arr3[] = {7 ,8 , 0};  //can be zero as well to indicate the blank. Have to ask user to use *
        //const char arr3[] = {'7' ,'8' , '0'}; 
        vector<int> row1 (arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
        vector<int> row2 (arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
        vector<int> row3 (arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
        goal_puzzle.push_back(row1);
        goal_puzzle.push_back(row2);
        goal_puzzle.push_back(row3);
        tile* t;
        //vector<vector<int>> intial_puzzle = {{t->eightpuz.at(0)(0), }, {}, {}}
        //Problem problem(, goal_puzzle);
        //vector<Operator> solved = UniCostSearch(problem);
    }
    else if(choice ==2){
        MisplacedTileH();
    }
    else if(choice ==3){
        EuclideanDistH();
    }
    else{
        cout <<"Please choose an answer of 0, 1, or 2" << endl;
        return;
    }

}

void puzzle::UniCostSearch(){

}

//needs to check the amount of misplaced tiles which the system will be using
void puzzle::MisplacedTileH(){

}
void puzzle::EuclideanDistH(){

}

//Movement nodes:
//  these nodes have are called to move the information from the given puzzle
//  eventually they will solve the actual puzzle.

void puzzle::topleft(tile *curr) { 
    
}

void puzzle::topmiddle(tile *curr){
}

void puzzle::topright(tile *curr){
}

void puzzle::bottomleft(tile *curr){
}

void puzzle::bottomright(tile *curr){
}

void puzzle::bottommiddle(tile *curr){
}

void puzzle::middleleft(tile *curr){
}

void puzzle::middleright(tile *curr){
}

void puzzle::middlemiddle(tile *curr){
}

void puzzle::HeuristicCal(vector<vector<char>> eightpuz)
{
    int tempvar = 0;
    int counter = 0;
    vector<vector<char>> goal_puzzle;
    const char arr1[] = {'1' ,'2' , '3'};
    const char arr2[] = {'4' ,'5' , '6'};
    const char arr3[] = {'7' ,'8' , '*'};  //can be zero as well to indicate the blank. Have to ask user to use *
    //const char arr3[] = {'7' ,'8' , '0'}; 
    vector<char> row1 (arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
    vector<char> row2 (arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
    vector<char> row3 (arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
    goal_puzzle.push_back(row1);
    goal_puzzle.push_back(row2);
    goal_puzzle.push_back(row3);
}

bool puzzle::completePuzzle(vector<vector<char>> eightpuz){
    vector<vector<char>> rightPuzzle;
    const char arr1[] =  {'1', '2', '3'};
    const char arr2[] =  {'4', '5', '6'};
    const char arr3[] =  {'7', '8', '*'};
    vector<char> v1 (arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
    vector<char> v2 (arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
    vector<char> v3 (arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
    rightPuzzle.push_back(v1);
    rightPuzzle.push_back(v2);
    rightPuzzle.push_back(v3);
    if(eightpuz == rightPuzzle){
        return true;
    }
    else{
        return false;
    }

}

void puzzle::printPuzzle(tile* curr){
    if(curr != root){
		cout << "The best state to expand with a g(n) = ";
		cout << curr->moveCost;
		cout << " and h(n) = ";
		cout << curr->heuristic;
		cout << " is..." << endl;
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << curr->eightpuz.at(i).at(j) << " ";
		}
		cout << endl;
		
	}
	cout << endl;
}