#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node {

public:
    Node(int &h_n, int &g_n, vector<vector<int>> &grid);
    ~Node();
    void printNode();
    vector<vector<int>>& getGrid();

    //public variables
    vector<vector<int>> grid;
    int h_n;
    int g_n;

};

Node::Node(int &h_n, int &g_n, vector<vector<int>> &grid) {
    this->h_n = h_n;
    this->g_n = g_n;
    this->grid = grid;
}

Node::~Node() {

}

void Node::printNode() {
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            cout << this->grid[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>>& Node::getGrid() {
    return this->grid;
}


#endif // NODE_H
