// 4. Implement the activity selection problem to get a clear understanding of greedy approach.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity with start, finish times, and an id (activity number)
typedef struct Activity{
    int start;
    int finish;
    int id; // Activity number
} Activity;

// Comparison function to sort activities based on finish time
int compare(const void *a, const void *b) {
    return ((Activity*)a)->finish - ((Activity*)b)->finish;
}

// Function to implement Activity Selection using Greedy Algorithm
void activitySelection(Activity activities[], int n) {
    // Sort the activities based on finish time
    qsort(activities, n, sizeof(Activity), compare);

    // The first activity is always selected
    printf("Selected activities:\n");
    printf("Activity Number %d: Start: %d\t Finish: %d\n", activities[0].id, activities[0].start, activities[0].finish);

    // Last finish time
    int lastFinishTime = activities[0].finish;

    // Iterate over the remaining activities
    for (int i = 1; i < n; i++) {
        // If the start time of the current activity is greater than or equal to the finish time of the last selected activity
        if (activities[i].start >= lastFinishTime) {
            // Select the activity
            printf("Activity Number %d: Start: %d\t Finish: %d\n", activities[i].id, activities[i].start, activities[i].finish);
            lastFinishTime = activities[i].finish;
        }
    }
}

int main() {
    // Define the activities with their start and finish times and activity numbers (ids)
    Activity activities[] = {
        {1, 2, 1},  // Activity 1
        {3, 4, 2},  // Activity 2
        {0, 6, 3},  // Activity 3
        {5, 7, 4},  // Activity 4
        {8, 9, 5},  // Activity 5
        {5, 9, 6}   // Activity 6
    };
    int n = sizeof(activities) / sizeof(activities[0]);

    // Call the activity selection function
    activitySelection(activities, n);

    return 0;
}