#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>
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
		vector<char> vec1;
		vec1.push_back('1');
		vec1.push_back('2');
		vec1.push_back('*');
		vector<char> vec2;
		vec2.push_back('4');
		vec2.push_back('5');
		vec2.push_back('6');
		vector<char> vec3;
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
        char tile1, tile2, tile3;
        cout << "Enter first row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<char> v1;
        v1.push_back(tile1);
        v1.push_back(tile2);
        v1.push_back(tile3);
        t->eightpuz.push_back(v1);
        cout << "Enter second row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<char> v2;
        v2.push_back(tile1);
        v2.push_back(tile2);
        v2.push_back(tile3);
        t->eightpuz.push_back(v2);
        cout << "Enter third row\n";
        cin >> tile1 >> tile2 >> tile3;
        vector<char> v3;
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
    cout << "Choose your algorithm: 1 is for Uniform Cost Search, 2 is for Misplaced Tile Heuristic and 3 is for Euclidean distance heuristic"<< endl;
    if(choice == 1){
        UniformCostSearch();
    }
    else if(choice ==2){
        MisplacedTileH();
    }
    else if(choice ==3){
        EuclideanDistH();
    }
    else{
        cout <<"Please choose an answer of 1 2 or 3" << endl;
        return;
    }

}

void puzzle::UniformCostSearch(){

}
void puzzle::MisplacedTileH(){

}
void puzzle::EuclideanDistH(){

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
