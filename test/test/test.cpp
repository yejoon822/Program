//
//  test.cpp
//  test
//
//  Created by 신예준 on 2/28/25.
//
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>

using namespace std;

#define ROW 10
#define COL 10

// Direction vectors (Up, Down, Left, Right)
const int dRow[4] = {-1, 1, 0, 0};
const int dCol[4] = {0, 0, -1, 1};

// Node structure
struct Node {
    int row, col;
    double cost, heuristic, total;
    
    Node(int r, int c, double g, double h)
        : row(r), col(c), cost(g), heuristic(h), total(g + h) {}

    // Operator overloading for priority queue
    bool operator>(const Node& other) const {
        return total > other.total;
    }
};

// Manhattan Distance heuristic
double heuristic(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

// A* Algorithm
void aStarSearch(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<int, unordered_map<int, pair<int, int>>> parent; // Stores parent nodes

    pq.emplace(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    unordered_map<int, unordered_map<int, double>> costSoFar;
    costSoFar[start.first][start.second] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // If reached the goal
        if (current.row == goal.first && current.col == goal.second) {
            cout << "Path found!\n";
            vector<pair<int, int>> path;
            pair<int, int> node = goal;
            while (node != start) {
                path.push_back(node);
                node = parent[node.first][node.second];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            // Print Path
            for (auto p : path) {
                cout << "(" << p.first << ", " << p.second << ") -> ";
            }
            cout << "Goal\n";
            return;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dRow[i];
            int newCol = current.col + dCol[i];

            if (newRow >= 0 && newRow < ROW && newCol >= 0 && newCol < COL && grid[newRow][newCol] == 0) {
                double newCost = costSoFar[current.row][current.col] + 1;

                if (!costSoFar.count(newRow) || !costSoFar[newRow].count(newCol) || newCost < costSoFar[newRow][newCol]) {
                    costSoFar[newRow][newCol] = newCost;
                    double h = heuristic(newRow, newCol, goal.first, goal.second);
                    pq.emplace(newRow, newCol, newCost, h);
                    parent[newRow][newCol] = {current.row, current.col};
                }
            }
        }
    }
    cout << "No path found!\n";
}

int main() {
    vector<vector<int>> grid(ROW, vector<int>(COL, 0));

    // Obstacles in the grid (1 represents obstacle)
    grid[3][4] = 1;
    grid[3][5] = 1;
    grid[4][5] = 1;
    grid[5][5] = 1;
    grid[6][5] = 1;

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {9, 9};

    cout << "A* Pathfinding Algorithm:\n";
    aStarSearch(grid, start, goal);

    return 0;
}


