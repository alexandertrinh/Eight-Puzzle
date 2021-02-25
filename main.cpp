#include <iostream>
#include <vector>
#include "EightPuzzle.h"

using namespace std;

int main()
{
    EightPuzzle puzzle;
    vector<vector<int>> grid;
    int a, b, c; //used for inputs

    cout << "Welcome to Alex Trinh's 8-Puzzle Solver." << endl;
    cout << "Type \"1\" to use default puzzle, or \"2\" to enter your own." << endl;
    cin >> a;

    if (a == 2) { //enter your own
        cout << "\tEnter your puzzle, use a zero to represent the blank" << endl;
        cout << "\tEnter the first row, use space or tabs between numbers ";

        cin >> a >> b >> c;
        vector<int> tempVect;
        tempVect.push_back(a);
        tempVect.push_back(b);
        tempVect.push_back(c);
        grid.push_back(tempVect);
        tempVect.clear();

        cout << "\tEnter the second row, use space or tabs between numbers ";

        cin >> a >> b >> c;
        tempVect.push_back(a);
        tempVect.push_back(b);
        tempVect.push_back(c);
        grid.push_back(tempVect);
        tempVect.clear();

        cout << "\tEnter the third row, use space or tabs between numbers ";

        cin >> a >> b >> c;
        tempVect.push_back(a);
        tempVect.push_back(b);
        tempVect.push_back(c);
        grid.push_back(tempVect);
        tempVect.clear();
        cout << endl;

        //grid is now complete, send to puzzle object
        puzzle.makeNew(grid);

    }

    cout << "\tEnter your choice of algorithm" << endl;
    cout << "\t   1.  Uniform Cost Search" << endl;
    cout << "\t   2.  A* with the Misplaced Tile heuristic" << endl;
    cout << "\t   3.  A* with the Manhattan distance heuristic" << endl;
    cout << endl;

    cin >> a;
    cout << endl;

    puzzle.algChoice(a);


    return 0;
}
