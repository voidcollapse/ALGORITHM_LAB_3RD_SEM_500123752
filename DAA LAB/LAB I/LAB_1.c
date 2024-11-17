// 1. Implement the insertion inside iterative and recursive Binary search tree and compare their performance.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a BST Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new BST node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursive insertion
Node* recursiveInsert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = recursiveInsert(root->left, data);
    } else if (data > root->data) {
        root->right = recursiveInsert(root->right, data);
    }
    return root;
}

// Iterative insertion
Node* iterativeInsert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Duplicate data not allowed
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Generate test cases
void generateTestCase(int* arr, int numElements, int caseType) {
    switch (caseType) {
        case 1: // Sorted input
            for (int i = 0; i < numElements; i++) {
                arr[i] = i + 1;
            }
            break;
        case 2: // Reverse sorted input
            for (int i = 0; i < numElements; i++) {
                arr[i] = numElements - i;
            }
            break;
        case 3: // Random input
            for (int i = 0; i < numElements; i++) {
                arr[i] = rand() % (numElements * 5);
            }
            break;
        case 4: // Uniform input
            for (int i = 0; i < numElements; i++) {
                arr[i] = 42; // Insert the same number repeatedly
            }
            break;
        case 5: // Balanced input
            for (int i = 0; i < numElements; i++) {
                arr[i] = (i % 2 == 0) ? (numElements / 2 + i / 2) : (numElements / 2 - i / 2);
            }
            break;
    }
}

// Performance comparison
void performanceComparison(int caseType) {
    Node* rootRecursive = NULL;
    Node* rootIterative = NULL;

    const int NUM_ELEMENTS = 10000; // Reduced for debugging
    int elements[NUM_ELEMENTS];
    generateTestCase(elements, NUM_ELEMENTS, caseType);


    // Measure time for recursive insertion
    clock_t startRecursive = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        rootRecursive = recursiveInsert(rootRecursive, elements[i]);
    }
    clock_t endRecursive = clock();
    double timeRecursive = (double)(endRecursive - startRecursive) / CLOCKS_PER_SEC;

    // Measure time for iterative insertion
    clock_t startIterative = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        rootIterative = iterativeInsert(rootIterative, elements[i]);
    }
    clock_t endIterative = clock();
    double timeIterative = (double)(endIterative - startIterative) / CLOCKS_PER_SEC;

    // Print results
    printf("Case %d:\n", caseType);
    printf("  Time taken by Recursive Insertion: %.6f seconds\n", timeRecursive);
    printf("  Time taken by Iterative Insertion: %.6f seconds\n\n", timeIterative);
    fflush(stdout); // Ensure all output is displayed
}

int main() {
    srand(time(0)); // Seed for random number generation

    for (int caseType = 1; caseType <= 5; caseType++) {
        performanceComparison(caseType);
    }

    return 0;
}