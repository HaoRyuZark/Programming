#include <stdio.h>

//Binary Search
int binary_search(int arr[], int l, int r, int x){
    
    if (r >= l){
    int mid = l + (r - l)/2;

    if (arr[mid] == x) return mid;
    
    if (arr[mid] > x) return binary_search(arr, l, mid-1, x);

        return binary_search(arr, mid+1, r, x);
    }

    return -1;
}


int interpolation_search(int arr[], int size, int target) {
    
    int high = size - 1;
    int low = 0;

    while (target >= arr[low] && target <= arr[high] && low <= high) {

        if (arr[low] == arr[high]) { // Avoid division by zero
            if (arr[low] == target) return low;
            else return -1;
        }

        int probe = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);

        if (probe < low || probe > high) // Check for out-of-bounds index
            return -1;

        printf("Probe index: %d\n", probe);

        if (arr[probe] == target)
            return probe;
        else if (arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return -1;
}

int main(void){

    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr)/ sizeof(arr[0]);
    int x = 10;
    int result = binary_search(arr, 0, n-1, x);
    
    (result == -1)? printf("Element is not present in array"): printf("Element is present at index %d", result);
    
    printf("\n");

    result = interpolation_search(arr, n, 40);

    (result == -1)? printf("Element is not present in array"): printf("Element is present at index %d", result);
    
    return 0;
}
