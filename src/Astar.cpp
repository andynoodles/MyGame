#include "Astar.hpp"

// A* search algorithm function definition
std::vector<std::pair<int, int>> aStarSearch(std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal) {
    // Define movement directions (up, down, left, right)
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    // Dimensions of the grid
    int rows = grid.size();
    int cols = grid[0].size();

    // Priority queue for open list
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;

    // Create start node
    Node* startNode = new Node(start.first, start.second, 0, 0, nullptr);
    openList.push(startNode);

    // Create visited array to keep track of visited nodes
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    visited[start.first][start.second] = true;

    // Main A* search loop
    while (!openList.empty()) {
        // Get the node with the lowest total cost from the open list
        Node* currentNode = openList.top();
        openList.pop();

        // Check if current node is the goal
        if (currentNode->x == goal.first && currentNode->y == goal.second) {
            // Goal reached, construct path
            std::vector<std::pair<int, int>> path;
            while (currentNode != nullptr) {
                path.push_back({ currentNode->x, currentNode->y });
                currentNode = currentNode->parent;
            }
            // Output path in reverse order
            std::cout << "Path: ";
            for (int i = path.size() - 1; i >= 0; i--) {
                std::cout << "(" << path[i].first << "," << path[i].second << ") ";
            }
            std::cout << std::endl;

            return path;
        }

        // Expand current node
        for (int i = 0; i < 4; i++) {
            int newX = currentNode->x + dx[i];
            int newY = currentNode->y + dy[i];

            // Check if new position is within grid boundaries and not blocked
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] != 1 && !visited[newX][newY]) {
                // Calculate cost and heuristic for the new node
                int newCost = currentNode->cost + 1; // Assuming each movement has a cost of 1
                int newHeuristic = abs(newX - goal.first) + abs(newY - goal.second); // Manhattan distance as heuristic

                // Create new node
                Node* newNode = new Node(newX, newY, newCost, newHeuristic, currentNode);
                openList.push(newNode);
                visited[newX][newY] = true;
            }
        }
    }

    //std::cout << "No path found!" << std::endl;
    std::vector<std::pair<int, int>> path;
    return path;
}
