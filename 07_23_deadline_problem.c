#include <stdio.h>
#include <stdlib.h> // For qsort
#include <stdbool.h> // For bool type

// Represents a job with an ID, deadline, and profit
typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

// Comparison function for qsort to sort jobs in descending order of profit
int compareJobs(const void* a, const void* b) {
    Job* jobA = (Job*)a;
    Job* jobB = (Job*)b;
    // We want to sort in descending order, so we do jobB->profit - jobA->profit
    return (jobB->profit - jobA->profit);
}

// Finds the maximum deadline value in the array of jobs
int findMaxDeadline(Job arr[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deadline > max) {
            max = arr[i].deadline;
        }
    }
    return max;
}

/**
 * @brief Implements the Job Sequencing with Deadline problem.
 * @param arr An array of Job structs.
 * @param n The number of jobs in the array.
 */
void printJobScheduling(Job arr[], int n) {
    // 1. Sort all jobs according to decreasing order of profit
    qsort(arr, n, sizeof(Job), compareJobs);

    // 2. Find the maximum deadline to determine the size of the result array
    int maxDeadline = findMaxDeadline(arr, n);

    // Array to store the sequence of jobs, representing time slots
    char result[maxDeadline];
    // Array to keep track of free time slots, initialized to false (free)
    bool slot[maxDeadline];

    for (int i = 0; i < maxDeadline; i++) {
        slot[i] = false;
    }

    int totalProfit = 0;

    // 3. Iterate through all given jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (starting from the last possible slot)
        // We go from (deadline - 1) down to 0
        for (int j = arr[i].deadline - 1; j >= 0; j--) {
            // If the slot is free
            if (slot[j] == false) {
                // Add this job to the result sequence
                result[j] = arr[i].id;
                // Mark this slot as occupied
                slot[j] = true;
                // Add job's profit to total
                totalProfit += arr[i].profit;
                // Break from the inner loop as we've found a slot
                break;
            }
        }
    }

    // Print the resulting job sequence and total profit
    printf("The optimal sequence of jobs to maximize profit is:\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i]) {
            printf("%c ", result[i]);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

// Main function to drive the program
int main() {
    Job arr[] = {
        {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27},
        {'d', 1, 25},  {'e', 3, 15}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Given jobs:\n");
    printf("Job ID\tDeadline\tProfit\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\n", arr[i].id, arr[i].deadline, arr[i].profit);
    }
    printf("\n");

    printJobScheduling(arr, n);

    return 0;
}
