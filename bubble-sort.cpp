#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void sort(int arr[], int len){
    for(int i=0; i<len; i++){
        int first = i%2;
        #pragma omp parallel 
        for(int j=first; j<len-1; j +=2){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


int main(){
    int len;
    cout<<"Enter No. of element : " << endl;
    cin>>len;
    
    int *arr = new int[len];
    
    for(int i=0; i<len ;i++){
        cin>>arr[i];
    }
    
    sort(arr, len);
    
    cout << "Sorted array: ";
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
