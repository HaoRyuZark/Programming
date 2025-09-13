#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Swap
void swap(int* a, int* b) {

    int temp = *a;
    *a = *b;
    *b = temp;
}

// Find max
int find_max(int* arr, int n) {
    int max = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Find min
int find_min(int* arr, int n) {
    
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Counting sort only positive numbers
int* counting_sort(int* arr, int n) {
  
    int max = find_max(arr, n);

    int temp_s = max + 1;
    int* temp = calloc(temp_s, sizeof(int)); // Allocate an array of the range 0 to max + 1 

    int i;

    for (i = 0; i < n; i++) { //Count occurrences in the orignial array and update the corresponding index in temp
        temp[arr[i]]++;
    }
     // Accumulative sum of each elment with its predecesors
     // This is the so called Running Sum which tells us how many elements before "index" are less or equal than the index 
     // In other words, eahc temp[index] represents the last position index can appear in the sorted array
    for (i = 1; i < temp_s; i++) {         
        temp[i] = temp[i] + temp[i - 1];
    }

    int* sorted = (int *)malloc(n * sizeof(int)); //create new array to return 
   
    // Placement: We are working our way back to sort original array using the information won in the last step
    // We use i for the current index in our new array and use the value at temp[arr[i] - 1] to get the last occurrence.
    // Then we decrement the value of the last occurence. The minus one is necessary because arrays are zero indexed
    for (i = 0; i < n; i++) {

        sorted[temp[arr[i]] - 1] = arr[i]; // sorted at the position of the occurrences of current (minus 1) is = to current 
        temp[arr[i]]--;  // decrease occurence of the current element
    }

    free(temp);
    return sorted;
}

//Version for posive and negative numbers. Logic is similar but we have to use a trick for no having negative indexes
void sign_counting_sort(int* arr, int n) {
  
    int max = find_max(arr, n);
    int min = find_min(arr, n);

    int temp_s = max - min + 1;
    int* temp = calloc(temp_s, sizeof(int)); // Allocate an array of the range 0 to max + 1 

    int i;

    for (i = 0; i < n; i++) { //Count occurrences in the orignial array and update the corresponding index in temp
        temp[arr[i] - min]++;
    }

    int arr_index = 0;

    for (int i = 0; i < temp_s; i++) {
        while (temp[i] > 0) {
            arr[arr_index] = i + min;
            temp[i]--;
            arr_index++;
        }
    }

    free(temp);
}
// Helper for radix
void counting_sort_for_radix(int* arr, int n, int unit) {
  

    int *temp = calloc(10, sizeof(int)); // Allocate an array of the range 0 to max + 1 

    int i;

    for (i = 0; i < n; i++) { //Count occurrences in the orignial array and update the corresponding index in temp
         
        temp[(arr[i] / unit) % 10]++;
    }

    for (i = 1; i < 10; i++) {      // accumulative sum of each elment with its predecesors
        temp[i] = temp[i] + temp[i - 1];
    }

    int* sorted = (int*)malloc(n * sizeof(int)); //create new array to return 
    
    for (i = 0; i < n; i++) {

        sorted[temp[(arr[i] / unit) % 10] - 1] = arr[i]; // sorted at the position of the occurrences of current (minus 1) is = to current 
        temp[(arr[i] / unit) % 10]--;  // decrease occurence of the current element
    }

    int* temp_arr = arr;
    
    arr = sorted;
    
    free(temp_arr);
    free(temp);
}

// Bubble Sort
void bubble_sort(int* arr, int n) {

  bool swapped;

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {

      if (arr[j + 1] < arr[j]) {
        swap(&arr[j + 1], &arr[j]);
        swapped = true;
      }
    }
    if (swapped == false) {
      break;
    }
  }
}

// Quick Sort
void median_of_three(int* arr, int start, int mid, int end) {
   
    if (arr[start] > arr[mid]) { swap(&arr[start], &arr[mid]); }
    if (arr[start] > arr[end]) { swap( &arr[start], &arr[end]); }
    if (arr[mid] > arr[end]) { swap(&arr[mid], &arr[end]); }
    
    swap(&arr[mid], &arr[end - 1]);
}

// Optimized partition for quick_sort with median of three
int partition(int* arr, int start, int end) {
    
    int mid = start + (end - start) / 2;
    
    median_of_three(arr, start, mid, end);
    
    int pivot_index = end - 1;
    int pivot = arr[pivot_index];
    
    int i = start + 1;
    int j = pivot_index - 1;

    while (i <= j) {
        
        while (arr[i] < pivot) { i++; }
        while (arr[j] > pivot) { j--; }

        if (i <= j) {  //swapping

            swap(&arr[i], &arr[j]);
            j--;
            i++;
        }
    }

  swap(&arr[i], &arr[pivot_index]); // Swap the pivot -> Place found
  
  return i; // Return position of pivot
}

// Traditional partition function
int partition_normal(int* arr, int start, int end) {

    int pivot = arr[end];
    int j = start - 1;

    for (int i = 0; i < end; i++) {

        if (arr[i] < pivot) {
            j++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[j + 1], &arr[end]);
    
    return j + 1;
}

void quick_sort(int* arr, int start, int end) {

  if (start < end) {

    int pi = partition(arr, start, end);  //divide in two

    quick_sort(arr, start, pi - 1);  //work on the left part
    quick_sort(arr, pi + 1, end); // work on the right part
  }
}

// Merge Sort
void merge_arr(int* arr, int left, int m, int right) {

    int left_len = m - left + 1;
    int right_len = right - m;

    int temp_right[right_len];
    int temp_left[left_len];

    int i, j, k;

    for (i = 0; i < right_len; i++) {
        temp_right[i] = arr[m + 1 + i];
    }

    for (i = 0; i < left_len; i++) {
        temp_left[i] = arr[left + i];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < left_len && j < right_len) {
        if (temp_left[i] <= temp_right[j]) {
            arr[k] = temp_left[i];
            i++;
        } else {
            arr[k] = temp_right[j];
            j++;
        }
        k++;
    }

    while (i < left_len) {
        arr[k] = temp_left[i];
        i++;
        k++;
    }

    while (j < right_len) {
        arr[k] = temp_right[j];
        j++;
        k++;
    } 
}


void merge_recursion(int* arr, int left, int right) {
  
    if (left < right) {

        int m = left + (right - left) / 2; //divide the array in two

        merge_recursion(arr, left, m);  // continue dividing
        merge_recursion(arr, m + 1, right);

        merge_arr(arr, left, m, right); // sort and combine
    }
}

//Only a wrapper for merge_sort
void merge_sort(int* arr, int n) { merge_recursion(arr, 0, n - 1); }

// Insertion Sort
void insertion_sort(int* arr, int n) {

    for (int i = 0; i < n; i++) {
        
        int temp = arr[i];
        int j = i - 1;
        
        // Swapping positons starting the previous index
        // only if the number at current index is less than the one at the previous
        while (j >= 0 && temp < arr[j]) {

            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = temp;
    }
}

// Selection sort
// Swapping based on the index
void selection_sort(int* arr, int n) {

    for (int i = 0; i < n - 1; i++) {
        
        int current_min_index = i;

        for (int j = i; j < n; j++) {
            
            if (arr[j] < arr[current_min_index]) {               
                current_min_index = j;
            }
        }
        
        swap(&arr[i], &arr[current_min_index]);        
    } 
}

// Radix sort
void radix_sort(int* arr, int n) {
    
    int max = find_max(arr, n);
    int exp = 1;

    while (max / exp >= 1) {

        counting_sort_for_radix(arr, n,exp);
        exp *= 10;
    } 
}



// It is counting sort but with the digits of the elements in the array 

// Print arr
void print_arr(int* arr, int n) {

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}

int main() {

    int arr[] = {14, 18, 12, 15, 5, 19, 6, 4, 2, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, 0, n - 1);
    
    print_arr(arr, n);
  
    return 0;
}
