#ifndef _EIGHTPUZZLE_H_
#define _EIGHTPUZLLE_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

struct tile{
    tile* child1;
    tile* child2;
    tile* child3;
    tile* child4;
    tile* parent;
    vector<vector<char>> eightpuz;
    int heuristic;
    int moveCost;
};
class Tile_Compare {
public:
    bool operator()(tile* t1, tile* t2)
    {
       if ((t1->moveCost + t1->heuristic) > (t2->moveCost + t2->heuristic)){
            return true;
       }
       return false;
    }
};
class puzzle{
    private:

    tile* root;
    int choice; //algorithm choice
    int totalNodesEx;
    vector<vector<vector<char>>> list;
    priority_queue<tile*, vector<tile*>, Tile_Compare > q; 
    bool goalstate;

    
    public:
    
    puzzle();
    void makePuzzle(int x);//makes puzzle default puzzle or input own puzzle
    void algorithmChoice(int x); //chooses algorithm's of UCS A* with misplaced tile and A* with euclidean dist
    void printPuzzle(tile* curr); //prints puzzle
    void UniformCostSearch();
    void MisplacedTileH();
    void EuclideanDistH();
    void child1(tile*curr, vector<vector<char>> tempv);
    void child2(tile*curr, vector<vector<char>> tempv);
    void child3(tile*curr, vector<vector<char>> tempv);
    void child4(tile*curr, vector<vector<char>> tempv);
    int HeuristicCalU(vector<vector<char>> eightpuz);//calculates the heuristic for A* Misplaced Tile
    int HeuristicCalM(vector<vector<char>> eightpuz);//calculates the heuristic for A* Misplaced Tile
    int HeuristicCalE(vector<vector<char>> eightpuz);//calculates the heuristic for A* Misplaced Tile
    bool validPuzzle(tile* curr); //checks puzzle if puzzle has value of 1-8
    bool completePuzzle(vector<vector<char>> eightpuz);// checks if the puzzle is solved
    
};



#endif