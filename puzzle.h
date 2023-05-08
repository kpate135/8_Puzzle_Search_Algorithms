#ifdef __PUZZLE_H__
#define __PUZZLE_H__

/*
    Next is the libraries being used 
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct tile{
    tile* child1;
    tile* child2;
    tile* child3;
    tile* child4;
    tile* parent;
    vector<vector<char>> eightpuz; //the actual puzzle 
    int hn; //heuristic cost
    int gn; //move cost
};

class operators{
    public:
        bool opperation()(tile* n, tile* m){ 
            //checking to see if we have to move the system
            if((n->gn + n->hn) > (m->gn + m->hn)){ //main check to see which will cost less to activate
                return true;
            }
            return false;
        }
};

class puzzle_class{
    private: 
    tile* root;
    
    int choice;
    int totalNodesEx;

    bool goal;

    vector<vector<vector<char>>> list;
    priority_queue<tile*, vector<tile*>, operators> q; 

    public:

    puzzle_class();

    void PuzzleCreation(int); //choice between default puzzle or your own
    void algorithmC(int); //user choice

    void printPuzzle(tile* curr); //prints the puzzle

    void UniformCostSearch(); //Only uses G(n) to solve 
    void AStarMisplacedTile(); //uses G(n) + H(n) to solve 
    void AStarEuclideanDistH(); //uses G(n) + Dist(H(n)) to solve

    //Top Row 
    void topleft(tile* curr);
    void topcenter(tile* curr);
    void topright(tile* curr);
    
    //Middle Row
    void middleleft(tile* curr);
    void middlecenter(tile* curr);
    void middleright(tile* curr);

    //Bottom Row
    void bottomleft(tile* curr);
    void bottomcenter(tile* curr);
    void bottomright(tile* curr);

    void HeuristicCalculator(vector<vector<char>> eightpuz); 
    //calculates the correct heuristics for the given expansions
    //Only Applies to A* algorithm

    bool validPuzzle(tile* curr); //checks to see if the user inputted correct values
    bool completePuzzle(vector<vector<char>> eightpuz); //checks to see if the puzzle is solved
};

#endif 