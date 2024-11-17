// 8.Implement the sum of subset.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void printSubset(int subset[], int size);
void sumOfSubsets(int set[], int subset[], int n, int subsetSize, int total, int nodeIndex, int targetSum, int* found);

// Function to print a solution (a valid subset)
void printSubset(int subset[], int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("}\n");
}

// Recursive function to find subsets with sum equal to targetSum
void sumOfSubsets(int set[], int subset[], int n, int subsetSize, int total, int nodeIndex, int targetSum, int* found) {
    // If the total is equal to targetSum, we found a solution
    if (total == targetSum) {
        printSubset(subset, subsetSize);
        *found = 1;  // Set found to true
        return;
    }

    // If total exceeds targetSum or we've explored all elements, return
    if (total > targetSum || nodeIndex >= n) {
        return;
    }

    // Include the current element in the subset and recurse
    subset[subsetSize] = set[nodeIndex];
    sumOfSubsets(set, subset, n, subsetSize + 1, total + set[nodeIndex], nodeIndex + 1, targetSum, found);

    // Exclude the current element from the subset and recurse
    sumOfSubsets(set, subset, n, subsetSize, total, nodeIndex + 1, targetSum, found);
}

int main() {
    int n, targetSum;
    int set[MAX], subset[MAX];
    int found = 0;  // Flag to indicate if a solution is found
    srand(time(0)); // Seed the random number generator

    // Set sizes for the 5 test cases: 5, 10, 15, 20, 25
    int set_sizes[] = {5, 10, 15, 20, 25};

    // Loop for 5 test cases with different increasing set sizes
    for (int i = 0; i < 5; i++) {
        // Set the current set size
        n = set_sizes[i];

        // Generate random elements for the set (values between 1 and 20)
        printf("\nTest case %d (Set size: %d):\n", i + 1, n);
        for (int j = 0; j < n; j++) {
            set[j] = rand() % 20 + 1; // Random values between 1 and 20
        }

        // Random target sum between 10 and 30
        targetSum = rand() % 21 + 10; // Random target sum between 10 and 30
        printf("Set: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", set[j]);
        }
        printf("\nTarget Sum: %d\n", targetSum);

        clock_t start, end;
        double cpu_time_used;
        
        // Start time measurement
        start = clock();

        // Call the recursive function to find all subsets that sum to targetSum
        sumOfSubsets(set, subset, n, 0, 0, 0, targetSum, &found);

        // End time measurement
        end = clock();

        // Measure execution time
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (!found) {
            printf("No solution found.\n");
        }
        
        // Print the execution time for the current test case
        printf("Execution time: %f seconds\n", cpu_time_used);
    }

    return 0;
}