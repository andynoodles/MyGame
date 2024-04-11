#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "Util/Logger.hpp"
// Define structure for a node
struct Node {
    int x, y; // Coordinates
    int cost; // Cost from start node to this node
    int heuristic; // Heuristic value (distance from this node to goal node)
    Node* parent; // Pointer to parent node

    Node(int _x, int _y, int _cost, int _heuristic, Node* _parent) :
        x(_x), y(_y), cost(_cost), heuristic(_heuristic), parent(_parent) {}

    // Function to calculate total cost
    int getTotalCost() const {
        return cost + heuristic;
    }
};

// Custom comparator for priority queue (min-heap based on total cost)
struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->getTotalCost() > rhs->getTotalCost();
    }
};

// A* search algorithm function declaration
std::vector<std::pair<int, int>> aStarSearch(std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal);

#endif 
