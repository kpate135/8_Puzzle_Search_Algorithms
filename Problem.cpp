#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

enum class Operator { 
  MOVE_LEFT = 0,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  NONE
};

enum class SearchType {
    Uniform = 0,
    Misplaced,
    Euclidean
};

class Node {
    public:
        Node(const vector<vector<int>>& _state, int _g_n, int _h_n, Node* _parent, Operator _op) : 
            state(_state), g_n(_g_n), h_n(_h_n), parent(_parent), op(_op) 
            {
                this->cost = g_n + h_n;
            } //updated constructor for g(n) and h(n) values 

        vector<vector<int>> get_state() const {
            return state;
        }

        void set_state(vector<vector<int>>& _state) {
            this->state = _state;
        }

        int get_g_n() const {
            return g_n;
        }

        void set_g_n(int _g_n) {
            this->g_n = _g_n;
        }

        int get_h_n() const {
            return h_n;
        }

        void set_h_n(int _h_n) {
            this->h_n = _h_n;
        }

        int get_cost() const {
            return cost;
        }

        void set_cost(int _cost) {
            this->cost = _cost;
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
        
        int cost; //g(n) + h(n)

        int g_n; //the cost to reach this node (g(n), the path from initial state to this node, as indicated by the parent pointers)
        
        int h_n; //heuristic for cost from current node to goal node

};

class Problem { //defining the problem space 
    private:
        vector<vector<int>> initial_state;
        vector<vector<int>> goal_state;
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

        Node* apply_operator(const Problem& problem, Node* node, Operator op, SearchType searchType) const {
            Node* childNode = new Node(problem.get_initial_state(), 0, 0, nullptr, Operator::NONE);
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

            childNode->set_g_n(node->get_g_n() + 1); //update g_n value (same for all search types)
            
            switch (searchType) { //update heuristic h(n) of childNode based on the Search type.
                case SearchType::Uniform:
                    childNode->set_h_n(0); //update h_n value, 0 for UCS
                    break;
                case SearchType::Misplaced:
                    childNode->set_h_n(problem.computeMisplacedHeuristic(childState, problem.get_goal_state()));
                    break;
                case SearchType::Euclidean:
                    childNode->set_h_n(problem.computeEuclideanHeuristic(childState, problem.get_goal_state()));
                    break;
                default:
                    break;
            }
            childNode->set_state(childState);
            childNode->set_cost(childNode->get_g_n() + childNode->get_h_n()); //update cost f(n) = g(n) + h(n)
            childNode->set_parent(node);
            childNode->set_operator(op);
            return childNode;
        }

        //compute the cost of applying an operator
        int compute_operator_cost(const vector<vector<int>>& state, Operator op) const {
            return 1;
        }

        //compute the Misplaced Tile heuristic
        int computeMisplacedHeuristic(const vector<vector<int>>& currState, const vector<vector<int>>& goalState) const {
            int h;
            for (int i = 0; i < currState.size(); ++i) {
                for (int j = 0; j < currState.size(); ++j) {
                    if (currState[i][j] != goalState[i][j]) { //increment h for every tile not matching goal state
                        ++h;
                    }
                }
            }
            return h;
        }


        //Compute the Euclidean Distance heuristic
        int computeEuclideanHeuristic(const vector<vector<int>>& currState, const vector<vector<int>>& goalState) const {
            int h = 0;
            for (int i = 0; i < currState.size(); ++i) {
                for (int j = 0; j < currState.size(); ++j) {
                    if (currState[i][j] != 0) {
                        //find the corresponding row and col of currState[i][j] in the goal state.
                        int goalRow;
                        int goalCol;
                        for (int row = 0; row < goalState.size(); ++row) {
                            for (int col = 0; col < goalState.size(); ++col) {
                                if (goalState[row][col] == currState[i][j]) {
                                    goalRow = row;
                                    goalCol = col;
                                    break;
                                }
                            }
                        }
                        h += sqrt(pow(i - goalRow, 2) + pow(j - goalCol, 2));
                    }
                }
            }
            return h;
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
                    if (currNode->get_cost() > childNode->get_cost()) { //if matching currNode in frontier has higher PATH-COST then we want to replace it with childNode
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
                    newFrontier.push({childNode->get_cost(), childNode}); //want to add our matching state childNode (with better PATH-COST) instead.
                    continue;
                }
                newFrontier.push({currNode->get_cost(), currNode});
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
    Node* initial_node = new Node(problem.get_initial_state(), 0, 0, nullptr, Operator::NONE);
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
            Node* child = problem.apply_operator(problem, currNode, op, SearchType::Uniform);
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

vector<Operator> A_Star_MisplacedTile(const Problem& problem) {
    Node* initial_node = new Node(problem.get_initial_state(), 0, 0, nullptr, Operator::NONE);
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier;
    unordered_set<string> explored;
    frontier.push({problem.computeMisplacedHeuristic(problem.get_initial_state(), problem.get_goal_state()), initial_node});

    //perform the search
    while (!frontier.empty()) {
        Node* currNode = frontier.top().second;
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
            Node* child = problem.apply_operator(problem, currNode, op, SearchType::Misplaced);
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

    return {}; //search failed
}

vector<Operator> A_Star_EuclideanDistance(const Problem& problem) {
    Node* initial_node = new Node(problem.get_initial_state(), 0, 0, nullptr, Operator::NONE);
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> frontier;
    unordered_set<string> explored;
    frontier.push({problem.computeEuclideanHeuristic(problem.get_initial_state(), problem.get_goal_state()), initial_node});

    //perform the search
    while (!frontier.empty()) {
        Node* currNode = frontier.top().second;
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
            Node* child = problem.apply_operator(problem, currNode, op, SearchType::Euclidean);
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

    return {}; //search failed
}