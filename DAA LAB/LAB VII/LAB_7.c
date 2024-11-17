// 7. Through 0/1 Knapsack problem, analyze the greedy and dynamic programming approach for the same dataset.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  // For gettimeofday()

// Structure to store items
typedef struct {
    int weight;
    int value;
    float ratio;  // value-to-weight ratio
} Item;

// Greedy approach for 0/1 Knapsack
int greedyKnapsack(Item items[], int n, int W) {
    // Sort items by value-to-weight ratio in descending order
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }
    
    // Sort items in decreasing order of ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    int totalValue = 0;
    int currentWeight = 0;
    
    // Greedily select items
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= W) {
            totalValue += items[i].value;
            currentWeight += items[i].weight;
        }
    }
    return totalValue;
}

// Dynamic Programming approach for 0/1 Knapsack
int dpKnapsack(int wt[], int val[], int n, int W) {
    int dp[n + 1][W + 1];
    
    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = (val[i - 1] + dp[i - 1][w - wt[i - 1]] > dp[i - 1][w]) ? 
                            (val[i - 1] + dp[i - 1][w - wt[i - 1]]) : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

void getTimeElapsed(struct timeval start, struct timeval end, double *elapsedTime) {
    // Calculate elapsed time in milliseconds (ms)
    *elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

int main() {
    // Define 5 different test cases
    int test_cases[5][5] = {
        {4, 3, 5, 2, 6},  // Test case 1: Random weights and values
        {10, 20, 30, 40, 50},
        {1, 2, 3, 4, 5},
        {5, 10, 15, 7, 8},
        {3, 6, 7, 12, 14}
    };
    
    int knapsack_capacity = 10;  // Set knapsack capacity for all cases
    int iterations = 10000;  // Number of iterations to average out the time

    for (int i = 0; i < 5; i++) {
        printf("Test Case %d:\n", i + 1);
        Item items[5];
        int wt[] = { test_cases[i][0], test_cases[i][1], test_cases[i][2], test_cases[i][3], test_cases[i][4] };
        int val[] = { test_cases[i][0] * 5, test_cases[i][1] * 5, test_cases[i][2] * 5, test_cases[i][3] * 5, test_cases[i][4] * 5 };
        
        for (int j = 0; j < 5; j++) {
            items[j].weight = wt[j];
            items[j].value = val[j];
        }

        // Measure execution time for Greedy approach
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        for (int j = 0; j < iterations; j++) {
            greedyKnapsack(items, 5, knapsack_capacity);
        }
        gettimeofday(&end_time, NULL);
        double greedy_time;
        getTimeElapsed(start_time, end_time, &greedy_time);  // Time in ms
        printf("Greedy Value: %d\n", greedyKnapsack(items, 5, knapsack_capacity));
        printf("Greedy Execution Time: %.6f ms per iteration\n", greedy_time / iterations);

        // Measure execution time for Dynamic Programming approach
        gettimeofday(&start_time, NULL);
        for (int j = 0; j < iterations; j++) {
            dpKnapsack(wt, val, 5, knapsack_capacity);
        }
        gettimeofday(&end_time, NULL);
        double dp_time;
        getTimeElapsed(start_time, end_time, &dp_time);  // Time in ms
        printf("DP Value: %d\n", dpKnapsack(wt, val, 5, knapsack_capacity));
        printf("DP Execution Time: %.6f ms per iteration\n", dp_time / iterations);
        
        printf("\n");
    }

    return 0;
}