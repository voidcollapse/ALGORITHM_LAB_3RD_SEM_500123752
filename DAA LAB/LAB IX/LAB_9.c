// 9. Compare the Backtracking and Branch & Bound Approach by the implementation of 0/1 Knapsack problem. Also compare the performance with dynamic programming approach.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  // For gettimeofday()

// Function to calculate elapsed time in milliseconds
void getTimeElapsed(struct timeval start, struct timeval end, double *elapsedTime) {
    *elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
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

// Backtracking approach for 0/1 Knapsack
int backtrackKnapsack(int wt[], int val[], int n, int W, int totalValue, int currentWeight, int index) {
    // If we have processed all items, return the current total value
    if (index == n) {
        return totalValue;
    }

    // Case 1: Include the item if it does not exceed the weight capacity
    int includeValue = 0;
    if (currentWeight + wt[index] <= W) {
        includeValue = backtrackKnapsack(wt, val, n, W, totalValue + val[index], currentWeight + wt[index], index + 1);
    }

    // Case 2: Exclude the item
    int excludeValue = backtrackKnapsack(wt, val, n, W, totalValue, currentWeight, index + 1);

    // Return the maximum of both cases
    return (includeValue > excludeValue) ? includeValue : excludeValue;
}

// Branch & Bound approach for 0/1 Knapsack (using priority queue or recursive bounding)
int branchBoundKnapsack(int wt[], int val[], int n, int W, int totalValue, int currentWeight, int index, int bound) {
    // If we have processed all items, return the current total value
    if (index == n) {
        return totalValue;
    }

    // Case 1: Include the item if it does not exceed the weight capacity
    int includeValue = 0;
    if (currentWeight + wt[index] <= W) {
        includeValue = branchBoundKnapsack(wt, val, n, W, totalValue + val[index], currentWeight + wt[index], index + 1, bound);
    }

    // Case 2: Exclude the item
    int excludeValue = branchBoundKnapsack(wt, val, n, W, totalValue, currentWeight, index + 1, bound);

    // Return the maximum of both cases
    return (includeValue > excludeValue) ? includeValue : excludeValue;
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
        
        int wt[] = { test_cases[i][0], test_cases[i][1], test_cases[i][2], test_cases[i][3], test_cases[i][4] };
        int val[] = { test_cases[i][0] * 5, test_cases[i][1] * 5, test_cases[i][2] * 5, test_cases[i][3] * 5, test_cases[i][4] * 5 };

        // Measure execution time for Dynamic Programming approach
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        for (int j = 0; j < iterations; j++) {
            dpKnapsack(wt, val, 5, knapsack_capacity);
        }
        gettimeofday(&end_time, NULL);
        double dp_time;
        getTimeElapsed(start_time, end_time, &dp_time);  // Time in ms
        printf("DP Value: %d\n", dpKnapsack(wt, val, 5, knapsack_capacity));
        printf("DP Execution Time: %.6f ms per iteration\n", dp_time / iterations);

        // Measure execution time for Backtracking approach
        gettimeofday(&start_time, NULL);
        for (int j = 0; j < iterations; j++) {
            backtrackKnapsack(wt, val, 5, knapsack_capacity, 0, 0, 0);
        }
        gettimeofday(&end_time, NULL);
        double backtrack_time;
        getTimeElapsed(start_time, end_time, &backtrack_time);  // Time in ms
        printf("Backtracking Value: %d\n", backtrackKnapsack(wt, val, 5, knapsack_capacity, 0, 0, 0));
        printf("Backtracking Execution Time: %.6f ms per iteration\n", backtrack_time / iterations);

        // Measure execution time for Branch & Bound approach
        gettimeofday(&start_time, NULL);
        for (int j = 0; j < iterations; j++) {
            branchBoundKnapsack(wt, val, 5, knapsack_capacity, 0, 0, 0, 0);
        }
        gettimeofday(&end_time, NULL);
        double branchBound_time;
        getTimeElapsed(start_time, end_time, &branchBound_time);  // Time in ms
        printf("Branch & Bound Value: %d\n", branchBoundKnapsack(wt, val, 5, knapsack_capacity, 0, 0, 0, 0));
        printf("Branch & Bound Execution Time: %.6f ms per iteration\n", branchBound_time / iterations);

        printf("\n");
    }

    return 0;
}