#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

void min(int arr[], int len){
    int min =INT_MAX;
    #pragma omp parallel for reduction(min:min_value)
    for (int i=0; i<len ; i++){
        if(min>arr[i]){
            min = arr[i];
        }
    }
    cout<< "min :" <<min<<endl;
}

void max(int arr[], int len){
    int max =INT_MIN;
    #pragma omp parallel for reduction(min:min_value)
    for (int i=0; i<len ; i++){
        if(max<arr[i]){
            max = arr[i];
        }
    }
    
    cout<<"max :"<< max<<endl;
}

void avg(int arr[], int len){
    int avg =0;
    #pragma omp parallel for reduction(min:min_value)
    for (int i=0; i<len ; i++){
        avg += arr[i];
    }
    
    cout<<"avg : "<<avg/len<<endl;
    
    cout<<"sum : "<<avg << endl;
}

int main(){
    int len;
    
    cout<<"enter no of element : ";
    cin>>len;
    
    int *arr = new int[len];
    
    for(int i=0; i<len ;i++){
        cin >> arr[i];
    }
    
    min(arr, len);
    max(arr, len);
    avg(arr, len);
    
    return 0;
}
