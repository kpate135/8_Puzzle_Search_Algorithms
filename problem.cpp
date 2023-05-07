#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

class Tile;

enum class Operator { 
  MOVE_LEFT = 0,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  NONE
};

class Node {
    public:
        Node(const vector<vector<int>>& _state, int _cost, Node* _parent, Operator _op) :
            state(_state), cost(_cost), parent(_parent), op(_op) {}

       Node(const vector<vector<int>>& _state, int _cost, Node* _parent, Operator _op, int _heur) :
            state(_state), cost(_cost), parent(_parent), op(_op), heur(_heur) {}


        vector<vector<int>> get_state() const {
            return state;
        }

        void set_state(vector<vector<int>>& _state) {
            this->state = _state;
        }

        int get_cost() const {
            return cost;
        }

        int get_heuristic() const{
            return heur;
        }

        int get_fn() const{
            return fn;
        }

        int get_efn() const{
            return efn;
        }

        void set_cost(int _cost) {
            this->cost = _cost;
        }
        void set_hn(int _heur){
            this->heur = _heur;
        }

        void set_fn(int _fn){
            this->fn = _fn;
        }

        void set_efn(int _efn){
            this->efn = _efn;
        }

        Node* get_parent() const {
            return parent;
        }

        void set_parent(Node* _parent) {
            this->parent = _parent;
        }

        Operator get_operator() const {
            return op;
        }

        void set_operator(Operator _op) {
            this->op = _op;
        }
        /*
        Node makeChildNode(const Problem& problem, Node* parent, Operator op) { //added this based off optional reading, might not need idk
            vector<vector<int>> new_state = problem.apply_operator(parent->get_state(), op); //new child state after applying given operator to parent state
            int new_cost = parent->get_cost() + 1;
            return Node(new_state, new_cost, parent, op);
        }
        */
        vector<Operator> get_path() const { //returns the path of moves/operators from intiial state to goal state. //get the path from the root to this node
            vector<Operator> path;
            Node* curr = const_cast<Node*>(this);
            while (curr->get_parent() != nullptr) {
                path.push_back(curr->get_operator());
                curr = curr->get_parent();
            }
            reverse(path.begin(), path.end());
            return path;
        }

    private:
        vector<vector<int>> state; //the state of the puzzle in the state space to which the node corresponds
                
        Node* parent; //a pointer to the parent node (the node in the search tree that generated this node)

        Operator op; //the operator applied to the parent to reach/generate this node
        
        int cost; //the cost to reach this node (g(n), the path from initial state to this node, as indicated by the parent pointers)

        int heur; //heuristic cost for the system (h(n), estimated distance)

        int fn; // f(n) = g(n) + h(n)

        int efn; // the eculdiean f(n) = g(n) + sqrt(h(n))

};

class Problem { //defining the problem space 
    private:
        vector<vector<int>> initial_state;
        vector<vector<int>> goal_state;
        int h;
    public:
        Problem(vector<vector<int>> _initial_state, vector<vector<int>> _goal_state) {
            initial_state = _initial_state;
            goal_state = _goal_state;
        }
          
        vector<vector<int>> get_initial_state() const {
            return initial_state;
        }

        vector<vector<int>> get_goal_state() const {
            return goal_state;
        }

        vector<Operator> get_operators() const {
            return {Operator::MOVE_LEFT, Operator::MOVE_RIGHT, Operator::MOVE_UP, Operator::MOVE_DOWN};
        }

        Node* apply_operator(const Problem& problem, Node* node, Operator op)  const{
            Node* childNode = new Node(problem.get_initial_state(), 0, nullptr, Operator::NONE);
            //find indices of the blank tile
            int row, col;
            vector<vector<int>> nodeState = node->get_state();
            for (int i = 0; i < nodeState.size(); ++i) {
                for (int j = 0; j < nodeState.size(); ++j) {
                    if (nodeState[i][j] == 0) {
                        row = i;
                        col = j;
                        break;
                    }
                }
            }

            //apply operator
            vector<vector<int>> childState = node->get_state();
            switch (op) {
                case Operator::MOVE_LEFT:
                    if (col > 0) {
                        swap(childState[row][col], childState[row][col - 1]);
                    }
                    break;
                case Operator::MOVE_RIGHT:
                    if (col < nodeState.size() - 1) {
                        swap(childState[row][col], childState[row][col + 1]);
                    }
                    break;
                case Operator::MOVE_UP:
                    if (row > 0) {
                        swap(childState[row][col], childState[row - 1][col]);
                    }
                    break;
                case Operator::MOVE_DOWN:
                    if (row < nodeState.size() - 1) {
                        swap(childState[row][col], childState[row + 1][col]);
                    }
                    break;
                default:
                    break;

            }

            int tempCount = 0;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j< 3; j++){
                    if(nodeState.at(i).at(j) != goal_state.at(i).at(j)){
                        tempCount++;
                    }}}
            childNode->set_state(childState);
            childNode->set_cost(node->get_cost() + 1);
            childNode->set_parent(node);
            childNode->set_operator(op);
            childNode->set_hn(node->get_heuristic());
            childNode->set_fn(node->get_cost() + 1 + node->get_heuristic() + tempCount);
            //childNode->set_efn(node->get_cost() + node->get_heuristic());
            return childNode;
        }

        //compute the cost of applying an operator
        int compute_operator_cost(const vector<vector<int>>& state, Operator op) const {
            return 1;
        }

        int compute_eculdiean(const vector<vector<int>>&state, const vector<vector<int>>& goalState){
            int tempCount = 0;
            for(int i = 0; i < state.size(); i++){
                for(int j = 0; j < state.size(); j++){
                    for(int row = 0; row < state.size(); row++){
                        for(int col = 0; col < state.size(); col++ ){
                            if(state.at(i).at(j) == goalState.at(i).at(j)){
                                tempCount += pow((i-row), 2);
                                tempCount += pow((j-col), 2);
                            }}}}}
            return sqrt(tempCount); //distance from the goal
        }

        int compute_heuristic( const vector<vector<int>>&state, const vector<vector<int>>& goalState) {
            int tempCount = 0;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j< 3; j++){
                    if(state.at(i).at(j) != goalState.at(i).at(j)){
                        tempCount++;
                    }}}
            return tempCount;
        }

        string stateToString(const vector<vector<int>>& state) const {
            string stateString = "";
            for (int i = 0; i < state.size(); ++i) {
                for (int j = 0; j < state[i].size(); ++j) {
                    stateString += to_string(state[i][j]);
                }
            }
            return stateString;
        }

        pair<bool, bool> isInFrontier(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            vector<vector<int>> childState = childNode->get_state();
            while (!frontier.empty()) { //bool 1 is if inFrontier, bool 2 is if child state inFrontier WITH higher PATH-COST
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currState == childState) {
                    if (childNode->get_cost() > currNode->get_cost()) {
                        return {true, true};
                    }
                    return {true, false};
                }
            }
            return {false, false};
        }
        pair<bool, bool> isInFrontier1(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            vector<vector<int>> childState = childNode->get_state();
            while (!frontier.empty()) { //bool 1 is if inFrontier, bool 2 is if child state inFrontier WITH higher PATH-COST
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currState == childState) {
                    if (childNode->get_fn() > currNode->get_fn()) {
                        return {true, true};
                    }
                    return {true, false};
                }
            }
            return {false, false};
        }

        pair<bool, bool> isInFrontier2(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            vector<vector<int>> childState = childNode->get_state();
            while (!frontier.empty()) { //bool 1 is if inFrontier, bool 2 is if child state inFrontier WITH higher PATH-COST
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currState == childState) {
                    if (childNode->get_efn() > currNode->get_efn()) {
                        return {true, true};
                    }
                    return {true, false};
                }
            }
            return {false, false};
        }
        
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> replaceFrontierNode(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> newFrontier;
            while (!frontier.empty()) {
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currNode->get_state() == childNode->get_state()) {
                    continue;
                }
                newFrontier.push({currNode->get_cost(), currNode});
            }
            return newFrontier;
        }

        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> replaceFrontierNode1(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> newFrontier;
            while (!frontier.empty()) {
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currNode->get_state() == childNode->get_state()) {
                    continue;
                }
                newFrontier.push({currNode->get_fn(), currNode});
            }
            return newFrontier;
        }


        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> replaceFrontierNode2(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier, Node* childNode) const {
            priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> newFrontier;
            while (!frontier.empty()) {
                Node* currNode = frontier.top().second;
                frontier.pop();
                vector<vector<int>> currState = currNode->get_state();
                if (currNode->get_state() == childNode->get_state()) {
                    continue;
                }
                newFrontier.push({currNode->get_efn(), currNode});
            }
            return newFrontier;
        }

        /*
        bool checkExplored(const vector<vector<int>>& state) const {
            
        }
        
        void expand(const vector<vector<int>>& currState) {
            vector<Operator> operators = this->get_operators();
            for (Operator op : operators) {
                vector<vector<int>> new_state = this->apply_operator(currState, op);
                int new_cost = curr_node->get_cost() + this->compute_operator_cost(currState, op);
                Node* new_node = new Node(new_state, new_cost, curr_node, op);
                frontier.push({new_cost, new_node});
            }
        }
        */
};


vector<Operator> UniformCostSearch(const Problem& problem) {
    Node* initial_node = new Node(problem.get_initial_state(), 0, nullptr, Operator::NONE);
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier; //int, Node* pair (sorted by lowest path cost g(n))
    //unordered_set<vector<vector<int>>> explored; //efficient checking for repeated states
    unordered_set<string> explored;
    //unordered_set<Node*> inFrontier; //unordered_set<pair<vector<vector<int>>, int>> //if the set bases what's unique based on the 2d array states
    //unordered_map<string, int> inFrontier;
    frontier.push({0, initial_node});
    //inFrontier[initial_node->get_state()] = initial_node->get_cost();

    //perform the search
    while (!frontier.empty()) {
        Node* currNode = frontier.top().second; //choose the lowest-cost node in frontier to explore
        frontier.pop();

        //check if the state is the goal state
        vector<vector<int>> currState = currNode->get_state();
        if (currState == problem.get_goal_state()) {
            vector<Operator> path = currNode->get_path();
            delete currNode;
            return path;
        }

        string stateString = problem.stateToString(currState);
        explored.insert(stateString);
        for (Operator op : problem.get_operators()) {
            if (op == Operator::NONE) {
                continue;
            }
            Node* child = problem.apply_operator(problem, currNode, op);
            vector<vector<int>> childState = child->get_state();
            string childStateString = problem.stateToString(childState); 
            pair<bool, bool> checkChild = problem.isInFrontier(frontier, child);
            bool inFrontier = checkChild.first;
            bool higherPathCost = checkChild.second;

            if (explored.find(childStateString) == explored.end() || !inFrontier) { //childState is not in explored set or frontier.
                frontier.push({child->get_cost(), child});
            }
            else if (inFrontier && higherPathCost) {
                frontier = problem.replaceFrontierNode(frontier, child);
            }
        }
    }

    return {}; //frontier empty, search failed
}


vector<Operator> AStarMisH(const Problem& problem){
    Node* initial_node = new Node(problem.get_initial_state(), 0, nullptr, Operator::NONE);
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier; 

    unordered_set<string> explored;

     frontier.push({0, initial_node});

     while (!frontier.empty()) {
        Node* currNode = frontier.top().second; //choose the lowest-cost node in frontier to explore
        frontier.pop();

        //check if the state is the goal state
        vector<vector<int>> currState = currNode->get_state();
        if (currState == problem.get_goal_state()) {
            vector<Operator> path = currNode->get_path();
            delete currNode;
            return path;
        }

        string stateString = problem.stateToString(currState);
        explored.insert(stateString);
        for (Operator op : problem.get_operators()) {
            if (op == Operator::NONE) {
                continue;
            }
            Node* child = problem.apply_operator(problem, currNode, op);
            vector<vector<int>> childState = child->get_state();
            string childStateString = problem.stateToString(childState); 
            pair<bool, bool> checkChild = problem.isInFrontier1(frontier, child);
            bool inFrontier = checkChild.first;
            bool higherPathCost = checkChild.second;

            if (explored.find(childStateString) == explored.end() || !inFrontier) { //childState is not in explored set or frontier.
                frontier.push({child->get_fn(), child});
            }
            else if (inFrontier && higherPathCost) {
                frontier = problem.replaceFrontierNode1(frontier, child);
            }
        }
    }

    return {}; //frontier empty, search failed
}


vector<Operator> AStarEucH(const Problem& problem){
    Node* initial_node = new Node(problem.get_initial_state(), 0, nullptr, Operator::NONE);
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier; 

    unordered_set<string> explored;

     while (!frontier.empty()) {
        Node* currNode = frontier.top().second; //choose the lowest-cost node in frontier to explore
        frontier.pop();

        //check if the state is the goal state
        vector<vector<int>> currState = currNode->get_state();
        if (currState == problem.get_goal_state()) {
            vector<Operator> path = currNode->get_path();
            delete currNode;
            return path;
        }

        string stateString = problem.stateToString(currState);
        explored.insert(stateString);
        for (Operator op : problem.get_operators()) {
            if (op == Operator::NONE) {
                continue;
            }
            Node* child = problem.apply_operator(problem, currNode, op);
            vector<vector<int>> childState = child->get_state();
            string childStateString = problem.stateToString(childState); 
            pair<bool, bool> checkChild = problem.isInFrontier2(frontier, child);
            bool inFrontier = checkChild.first;
            bool higherPathCost = checkChild.second;

            if (explored.find(childStateString) == explored.end() || !inFrontier) { //childState is not in explored set or frontier.
                frontier.push({child->get_efn(), child});
            }
            else if (inFrontier && higherPathCost) {
                frontier = problem.replaceFrontierNode2(frontier, child);
            }
        }
    }

    return {}; //frontier empty, search failed
}