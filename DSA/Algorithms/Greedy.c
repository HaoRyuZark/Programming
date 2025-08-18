#include <stdio.h>

/* 
 * Greedy algorithms
 *
 * Greedy Choice: A global optimal solution can be reached by choosing the optimal choice at each step.
 *
 * Optimal Substructure: A problem has an optimal substructure if an optimal solution to the entire problem contains
 * the optimal solutions to the sub-problems.
 *
 * */

//Example Problem: Select as much activities as possible.

typedef struct {
    int start;
    int end;
} Activity;

// Function to sort activities by end time using simple Bubble Sort

void sort_activities(Activity activities[], int n) {

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (activities[j].end > activities[j+1].end) {
                // Swap
                Activity temp = activities[j];
                activities[j] = activities[j+1];
                activities[j+1] = temp;
            }
        }
    }
}

// Function to select the maximum number of activities
void activity_selection(Activity activities[], int n) {

    // Sort activities by end time
    sort_activities(activities, n);

    printf("Selected activities:\n");

    // The first activity always gets selected
    int count = 1;
    printf("Activity 0: Start = %d, End = %d\n", activities[0].start, activities[0].end);
    int last_end = activities[0].end;

    // Consider the rest of the activities
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= last_end) {
            printf("Activity %d: Start = %d, End = %d\n", i, activities[i].start, activities[i].end);
            last_end = activities[i].end;
            count++;
        }
    }

    printf("\nMaximum number of activities = %d\n", count);
}

int main() {

    Activity activities[] = {
        {1, 2},
        {3, 4},
        {0, 6},
        {5, 7},
        {8, 9},
        {5, 9}
    };

    int n = sizeof(activities) / sizeof(activities[0]);

    activity_selection(activities, n);

    return 0;
}



