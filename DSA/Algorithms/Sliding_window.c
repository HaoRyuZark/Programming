#include <stdio.h>
#include <stdlib.h>

// Sliding window technique applied to the max sub array problem

int k_sum(int* arr, int k) { // Sum of the first sub array
    
    int sum = 0;

    for (int i = 0; i < k; i++) {
        sum += arr[i];
    }

    return sum;
}

int sliding_window(int* arr, int n, int k) { // sliding the window ;)
    
    if (n < k) {
        return 0;
    }

    int sum = k_sum(arr, k);
    int max = sum;

    for (int i = 0; i <= n - k; i++) {
        
        sum -= arr[i];     // subtract first element of sub
        sum += arr[i + k]; // add next element

        if (sum > max) {
            max = sum;
        }
    }
    
    return max;
}


int main() {

    int n;
    
    printf("Enter size of arr: ");
    scanf("%d", &n);
    
    int*arr = (int *)malloc(n * sizeof(int));

    printf("Enter elements of arr: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int k;
    
    printf("Enter size of sub array: ");
    scanf("%d", &k);

    printf("Maximum sum of a subarray of size %d is %d\n", k,  sliding_window(arr, n, k));
    
    free(arr);
  
    return 0;
}
