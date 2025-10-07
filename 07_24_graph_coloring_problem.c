#include <stdio.h>
#include <stdbool.h>

// Define the number of vertices in the graph
#define V 4

/**
 * @brief Prints the final color assignment for each vertex.
 * @param color The array storing the color for each vertex.
 */
void printSolution(int color[]) {
    for (int i = 0; i < V; i++) {
        printf("Vertex %d ---> Color %d\n", i, color[i]);
    }
}

/**
 * @brief Checks if it's safe to assign a color 'c' to vertex 'v'.
 * * A color assignment is safe if no adjacent vertex of 'v' has the same color 'c'.
 * @param v The vertex to be colored.
 * @param graph The adjacency matrix of the graph.
 * @param color The array storing colors assigned to vertices.
 * @param c The color to be assigned.
 * @return true if it's safe to color, false otherwise.
 */
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        // Check if there is an edge from v to i AND if vertex i is already colored with 'c'
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief The main recursive utility to solve the graph coloring problem.
 * * It uses backtracking to try all possible color combinations.
 * @param graph The adjacency matrix of the graph.
 * @param m The total number of available colors.
 * @param color The array to store the assigned color for each vertex.
 * @param v The current vertex being considered.
 * @return true if a solution is found, false otherwise.
 */
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    // Base case: If all vertices are assigned a color, then we are done
    if (v == V) {
        return true;
    }

    // Try different colors for the current vertex 'v'
    for (int c = 1; c <= m; c++) {
        // Check if the assignment of color 'c' to 'v' is safe
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign the color

            // Recur for the next vertex
            if (graphColoringUtil(graph, m, color, v + 1)) {
                return true;
            }

            // If assigning color 'c' doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }

    // If no color can be assigned to this vertex, return false
    return false;
}

/**
 * @brief The main driver function to initiate the graph coloring process.
 * * It initializes the color array and calls the recursive utility.
 */
int main() {
    // Example graph represented by an adjacency matrix
    // 0 --- 1
    // | \   /
    // |  \ /
    // |   2
    // |  /
    // | /
    // 3
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };

    // Number of colors
    int m = 3;

    // Initialize the color array with 0 (0 means no color is assigned)
    int color[V];
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    // Call the main backtracking function starting from vertex 0
    if (graphColoringUtil(graph, m, color, 0) == false) {
        printf("Solution does not exist for %d colors.\n", m);
    } else {
        printf("Solution exists! The assigned colors are:\n");
        printSolution(color);
    }

    return 0;
}