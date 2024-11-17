// 2. Implement divide and conquer based merge sort and quick sort algorithms and compare their performance for the same set of elements.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to print an array (for debugging purposes)
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Merge Sort Helper Functions

// Merges two subarrays of arr[].
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively divide the array
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the two halves
        merge(arr, left, mid, right);
    }
}

// Quick Sort Helper Functions

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort the subarrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to generate random numbers for the test cases
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0 and 999
    }
}

// Performance comparison for different array sizes
void comparePerformance(int arr[], int size) {
    int *arrCopyForMergeSort = malloc(sizeof(int) * size);
    int *arrCopyForQuickSort = malloc(sizeof(int) * size);
    if (!arrCopyForMergeSort || !arrCopyForQuickSort) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Copy array to preserve original for both sorts
    for (int i = 0; i < size; i++) {
        arrCopyForMergeSort[i] = arr[i];
        arrCopyForQuickSort[i] = arr[i];
    }

    // Measure time for Quick Sort
    clock_t start = clock();
    quickSort(arrCopyForQuickSort, 0, size - 1);
    clock_t end = clock();
    double quickSortTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Measure time for Merge Sort
    start = clock();
    mergeSort(arrCopyForMergeSort, 0, size - 1);
    end = clock();
    double mergeSortTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Output the time taken by both algorithms
    printf("Array Size: %d\n", size);
    printf("Time taken for Quick Sort: %.6f seconds\n", quickSortTime);
    printf("Time taken for Merge Sort: %.6f seconds\n\n", mergeSortTime);

    free(arrCopyForMergeSort);
    free(arrCopyForQuickSort);
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Different array sizes to test
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Test for each array size
    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int arr[size];

        // Generate random array for each test size
        generateRandomArray(arr, size);

        // Compare performance for each size
        comparePerformance(arr, size);
    }

    return 0;
}