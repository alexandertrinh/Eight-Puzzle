#ifndef COMPARE_H
#define COMPARE_H

#include <iostream>
#include "Node.h"

using namespace std;

class Compare {

public:

    bool operator()(Node node1, Node node2) {

        return (node1.h_n + node1.g_n) > (node2.h_n + node2.g_n);
    }
};

#endif // COMPARE_H
