#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include "Node.h"
#include "Compare.h"

using namespace std;

class EightPuzzle {

public:
    EightPuzzle();
    ~EightPuzzle();
    void makeNew(vector<vector<int>> &grid);
    void algChoice(int &a);

private:
    static bool checkGoalState(vector<vector<int>> &grid);

    void search(int h_n, int g_n);
    int manhattan(vector<vector<int>> &grid);
    int misplaced(vector<vector<int> > &grid);
    void expandNode();
    void moveUp(int xpos, int ypos, Node n);
    void moveDown(int xpos, int ypos, Node n);
    void moveLeft(int xpos, int ypos, Node n);
    void moveRight(int xpos, int ypos, Node n);

    priority_queue<Node, vector<Node>, Compare> queue;
    vector<vector<int>> defaultGrid;
    int totalNodes;
    int max_size;
    int alg;

};

/*
 * Makes the default puzzle/grid and the goal state grid here.
 */
EightPuzzle::EightPuzzle() {

    //clear variables
    this->totalNodes = 0;
    this->max_size = 0;
    this->defaultGrid.clear();
    priority_queue<Node, vector<Node>, Compare> empty;
    swap(queue, empty);

    //setup default grid
    vector<int> vect1{0, 7, 2};
    this->defaultGrid.push_back(vect1);
    vector<int> vect2{4, 6, 1};
    this->defaultGrid.push_back(vect2);
    vector<int> vect3{3, 5, 8};
    this->defaultGrid.push_back(vect3);

}

EightPuzzle::~EightPuzzle(){
    //destructor
}

/*
 * Assigns the custom puzzle/grid here.
 */
void EightPuzzle::makeNew(vector<vector<int>> &grid) {
    this->defaultGrid = grid;
}

/*
 * Selects the algorithm type and assigns the heuristic value
 */
void EightPuzzle::algChoice(int &a) {
    this->alg = a;

    int h_n = 0;
    int g_n = 0;

    if (this->alg == 1) { //uniform cost search
        h_n = 0;
    } else if (this->alg == 2) { //misplaced tile search
        h_n = misplaced(this->defaultGrid);
    } else if (this->alg == 3) { //manhattan distance
        h_n = manhattan(this->defaultGrid);
    } else {
        cout << "No algorithm was selected" << endl;
    }

    search(h_n, g_n);
}

/*
 * Primary function that searchs for the goal state
 */
void EightPuzzle::search(int h_n, int g_n) {
    //initial node
    Node *initialNode = new Node(h_n, g_n, this->defaultGrid);

    //push initial node to queue
    queue.push(*initialNode);

    //print top node in queue
    cout << "Expanding State" << endl;
    Node tempNode = queue.top();
    tempNode.printNode();

    //loop through and expand nodes
    while (true) {

        //check if queue empty
        if (queue.empty()) {
            cout << "No solution was found" << endl;
            return;

        //if not empty, continue expanding
        } else {

            tempNode = queue.top();

            //if goal state reached
            if (checkGoalState(tempNode.getGrid())) {
                cout << endl << "Goal!!" << endl << endl;
                cout << "To solve this problem " << this->totalNodes << " nodes were expanded." << endl;
                cout << "The maximum number of nodes in the queue at one time was " << this->max_size << endl;
                cout << "Depth of the goal node was " << tempNode.g_n << endl;
                break;

            //goal state not yet reached
            } else {
                cout << endl << "The best state to expand with a g(n) = " << tempNode.g_n << " and h(n) = " << tempNode.h_n << " is..." << endl;
                tempNode.printNode();
                cout << "Expanding this node..." << endl;

                expandNode();
                queue.pop();
            }
        }
    }
}

void EightPuzzle::expandNode() {

    Node currNode = this->queue.top();
    int xpos = -1;
    int ypos = -1;

    //look for blank position
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            if (currNode.grid[i][j] == 0) {
                xpos = j;
                ypos = i;
            }

        }
    }

    //expand node in each direction and add to queue
    moveUp(xpos, ypos, currNode);
    moveDown(xpos, ypos, currNode);
    moveRight(xpos, ypos, currNode);
    moveLeft(xpos, ypos, currNode);


    //update max_size of queue
    int curr_size = this->queue.size();
    this->max_size = max(this->max_size, curr_size);

}

void EightPuzzle::moveUp(int xpos, int ypos, Node n) {

    vector<vector<int>> newGrid = n.grid;
    int h_n = -1;
    int g_n = -1;

    if (ypos != 0) {
        //swap blank position on grid
        swap(newGrid[ypos][xpos], newGrid[ypos - 1][xpos]);

        //assign the correct h(n) value based on selected algorithm
        if (this->alg == 1)
            h_n = 0;
        else if (this->alg == 2)
            h_n = misplaced(newGrid);
        else if (this->alg == 3)
            h_n = manhattan(newGrid);

        //increment the g(n) value based on current node's value
        g_n = n.g_n + 1;

        //make new node and push
        Node *newNode = new Node(h_n, g_n, newGrid);
        this->queue.push(*newNode);
        totalNodes++;

    }

}

void EightPuzzle::moveDown(int xpos, int ypos, Node n) {

    vector<vector<int>> newGrid = n.grid;
    int h_n = -1;
    int g_n = -1;

    if (ypos != 2) {
        //swap blank position on grid
        swap(newGrid[ypos][xpos], newGrid[ypos + 1][xpos]);

        //assign the correct h(n) value based on selected algorithm
        if (this->alg == 1)
            h_n = 0;
        else if (this->alg == 2)
            h_n = misplaced(newGrid);
        else if (this->alg == 3)
            h_n = manhattan(newGrid);

        //increment the g(n) value based on current node's value
        g_n = n.g_n + 1;

        //make new node and push
        Node *newNode = new Node(h_n, g_n, newGrid);
        this->queue.push(*newNode);
        this->totalNodes++;

    }
}

void EightPuzzle::moveLeft(int xpos, int ypos, Node n) {

    vector<vector<int>> newGrid = n.grid;
    int h_n = -1;
    int g_n = -1;

    if (xpos != 2) {
        //swap blank position on grid
        swap(newGrid[ypos][xpos], newGrid[ypos][xpos + 1]);

        //assign the correct h(n) value based on selected algorithm
        if (this->alg == 1)
            h_n = 0;
        else if (this->alg == 2)
            h_n = misplaced(newGrid);
        else if (this->alg == 3)
            h_n = manhattan(newGrid);

        //increment the g(n) value based on current node's value
        g_n = n.g_n + 1;

        //make new node and push
        Node *newNode = new Node(h_n, g_n, newGrid);
        this->queue.push(*newNode);
        this->totalNodes++;

    }
}

void EightPuzzle::moveRight(int xpos, int ypos, Node n) {

    vector<vector<int>> newGrid = n.grid;
    int h_n = -1;
    int g_n = -1;

    if (xpos != 0) {
        //swap blank position on grid
        swap(newGrid[ypos][xpos], newGrid[ypos][xpos - 1]);

        //assign the correct h(n) value based on selected algorithm
        if (this->alg == 1)
            h_n = 0;
        else if (this->alg == 2)
            h_n = misplaced(newGrid);
        else if (this->alg == 3)
            h_n = manhattan(newGrid);

        //increment the g(n) value based on current node's value
        g_n = n.g_n + 1;

        //make new node and push
        Node *newNode = new Node(h_n, g_n, newGrid);
        this->queue.push(*newNode);
        this->totalNodes++;

    }
}

int EightPuzzle::manhattan(vector<vector<int> > &grid) {

    int manhattanSum = 0;

    for(unsigned int i = 0; i < 3; i++) {
        for(unsigned int j = 0; j < 3; j++) {
            int num = grid[i][j];
            if (num) {
                manhattanSum = manhattanSum +
                               abs((int)j - ((num - 1) % 3)) +
                               abs((int)i - ((num - 1) / 3));
            }
        }
    }

    return manhattanSum;
}

int EightPuzzle::misplaced(vector<vector<int>> &grid) {

    //for every position on grid count the number of misplaced tiles
    int misplacedSum = 0;
    if (grid[0][0] != 1)
        misplacedSum++;
    if (grid[0][1] != 2)
        misplacedSum++;
    if (grid[0][2] != 3)
        misplacedSum++;
    if (grid[1][0] != 4)
        misplacedSum++;
    if (grid[1][1] != 5)
        misplacedSum++;
    if (grid[1][2] != 6)
        misplacedSum++;
    if (grid[2][0] != 7)
        misplacedSum++;
    if (grid[2][1] != 8)
        misplacedSum++;

    return misplacedSum;
}

bool EightPuzzle::checkGoalState(vector<vector<int>> &grid) {
    static vector<vector<int>> goalState;
    static bool init = false;

    //make sure goalState vector only initialized once for efficiency
    if (!init) {
        //goal state grid
        vector<int> vect1{1, 2, 3};
        goalState.push_back(vect1);
        vector<int> vect2{4, 5, 6};
        goalState.push_back(vect2);
        vector<int> vect3{7, 8, 0};
        goalState.push_back(vect3);
        init = true;
    }

    if (goalState == grid)
        return true;
    else
        return false;
}

#endif // EIGHTPUZZLE_H
