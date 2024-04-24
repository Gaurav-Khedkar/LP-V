#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to merge two sorted subarrays [left...mid] and [mid+1...right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left...right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Parallel merge sort function
void mergeSort_parallel(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Use OpenMP tasks for parallelization
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                // Recursively sort the first half
                mergeSort_parallel(arr, left, mid);
            }

            #pragma omp section
            {
                // Recursively sort the second half
                mergeSort_parallel(arr, mid + 1, right);
            }
        }

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    cout << "Original array:" << endl;
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // Parallel merge sort
    mergeSort_parallel(arr, 0, n - 1);

    cout << "Sorted array:" << endl;
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
