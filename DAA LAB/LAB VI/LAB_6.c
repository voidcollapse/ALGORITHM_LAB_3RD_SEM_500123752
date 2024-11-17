#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <windows.h>  // for QueryPerformanceCounter and QueryPerformanceFrequency

#define INF INT_MAX
#define REPEAT 10000  // Increased repetitions for more accurate timing

int minDistance(int dist[], bool sptSet[], int V);
void dijkstra(int graph[20][20], int src, int V);
void bellmanFord(int graph[20][3], int V, int E, int src);
double calculateExecutionTimeDijkstra(void (*func)(int[][20], int, int), int graph[20][20], int src, int V);
double calculateExecutionTimeBellmanFord(void (*func)(int[][3], int, int, int), int graph[20][3], int V, int E, int src);

// Function to find the vertex with the minimum distance
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Dijkstra's algorithm
void dijkstra(int graph[20][20], int src, int V) {
    int dist[V];
    bool sptSet[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

// Bellman-Ford algorithm
void bellmanFord(int graph[20][3], int V, int E, int src) {
    int dist[V];
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];
            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
}

// Utility function to calculate execution time for Dijkstra using QueryPerformanceCounter
double calculateExecutionTimeDijkstra(void (*func)(int[][20], int, int), int graph[20][20], int src, int V) {
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);  // Get the frequency of the high-resolution timer
    QueryPerformanceCounter(&start); // Start time

    for (int i = 0; i < REPEAT; i++) {
        func(graph, src, V);  // Run the algorithm
    }

    QueryPerformanceCounter(&end); // End time

    // Calculate elapsed time in seconds and convert to nanoseconds
    double elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e9;

    return elapsedTime / REPEAT; // Average time in nanoseconds
}

// Utility function to calculate execution time for Bellman-Ford using QueryPerformanceCounter
double calculateExecutionTimeBellmanFord(void (*func)(int[][3], int, int, int), int graph[20][3], int V, int E, int src) {
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);  // Get the frequency of the high-resolution timer
    QueryPerformanceCounter(&start); // Start time

    for (int i = 0; i < REPEAT; i++) {
        func(graph, V, E, src);  // Run the algorithm
    }

    QueryPerformanceCounter(&end); // End time

    // Calculate elapsed time in seconds and convert to nanoseconds
    double elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e9;

    return elapsedTime / REPEAT; // Average time in nanoseconds
}

// Test function with 5 cases
void compareAlgorithms() {
    // Graphs input data for Dijkstra
    int graph1[20][20] = {
        {0, 4, 1, 0},
        {0, 0, 2, 5},
        {0, 0, 0, 3},
        {0, 0, 0, 0}
    };

    int graph2[20][20] = {
        {0, 3, 2, 0, 0, 0},
        {0, 0, 0, 7, 4, 0},
        {0, 0, 0, 1, 0, 5},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };

    int graph3[20][20] = {
        {0, 6, 2, 5, 0, 0, 0, 0},
        {0, 0, 0, 1, 4, 0, 0, 0},
        {0, 0, 0, 0, 0, 5, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int graph4[20][20] = {
        {0, 2, 5, 0, 0},
        {0, 0, 0, 1, 2},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0}
    };

    int graph5[20][20] = {
        {0, 1, 2, 0, 0, 0},
        {0, 0, 0, 3, 4, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0}
    };

    // Graphs input data for Bellman-Ford (converted to edge list)
    int graph1_edges[20][3] = {
        {0, 1, 4}, {0, 2, 1}, {1, 2, 2}, {1, 3, 5}, {2, 3, 3}
    };
    int graph2_edges[20][3] = {
        {0, 1, 3}, {0, 2, 2}, {1, 3, 7}, {1, 4, 4}, {2, 3, 1}, {2, 5, 5}, {3, 5, 2}, {4, 5, 1}
    };
    int graph3_edges[20][3] = {
        {0, 1, 6}, {0, 2, 2}, {0, 3, 5}, {1, 3, 1}, {1, 4, 4}, {2, 5, 5}, {3, 6, 3}, {5, 6, 1}
    };
    int graph4_edges[20][3] = {
        {0, 1, 2}, {0, 2, 5}, {1, 3, 1}, {1, 4, 2}, {2, 3, 3}, {3, 4, 4}
    };
    int graph5_edges[20][3] = {
        {0, 1, 1}, {0, 2, 2}, {1, 3, 3}, {1, 4, 4}, {2, 5, 1}, {3, 4, 2}, {4, 5, 2}
    };

    // Test each graph
    printf("Time taken for Dijkstra's algorithm:\n");
    printf("Graph 1: %.3f nanoseconds\n", calculateExecutionTimeDijkstra(dijkstra, graph1, 0, 4));
    printf("Graph 2: %.3f nanoseconds\n", calculateExecutionTimeDijkstra(dijkstra, graph2, 0, 6));
    printf("Graph 3: %.3f nanoseconds\n", calculateExecutionTimeDijkstra(dijkstra, graph3, 0, 8));
    printf("Graph 4: %.3f nanoseconds\n", calculateExecutionTimeDijkstra(dijkstra, graph4, 0, 5));
    printf("Graph 5: %.3f nanoseconds\n", calculateExecutionTimeDijkstra(dijkstra, graph5, 0, 6));

    printf("\nTime taken for Bellman-Ford algorithm:\n");
    printf("Graph 1: %.3f nanoseconds\n", calculateExecutionTimeBellmanFord(bellmanFord, graph1_edges, 5, 5, 0));
    printf("Graph 2: %.3f nanoseconds\n", calculateExecutionTimeBellmanFord(bellmanFord, graph2_edges, 6, 8, 0));
    printf("Graph 3: %.3f nanoseconds\n", calculateExecutionTimeBellmanFord(bellmanFord, graph3_edges, 8, 9, 0));
    printf("Graph 4: %.3f nanoseconds\n", calculateExecutionTimeBellmanFord(bellmanFord, graph4_edges, 5, 5, 0));
    printf("Graph 5: %.3f nanoseconds\n", calculateExecutionTimeBellmanFord(bellmanFord, graph5_edges, 6, 5, 0));
}

int main() {
    compareAlgorithms();  // Compare Dijkstra and Bellman-Ford
    return 0;
}