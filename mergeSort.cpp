#include"mergeSort.h"
#include<vector>
#include<iostream>

using namespace std;

void printArray(const vector<int> &arr){
    int n = arr.size();
    cout<< "Array size: " << n << endl;
    cout<<"[";
    for(int i=0; i <n-1; i++){
        cout<< arr[i] << " ";
    }
    cout<< arr[n-1] << "]"<< endl;
}

//Wrapper for merge sort implementation with 1 thread
void singleSort(vector<int> &arr){
    mergeSort(arr, 0, arr.size() - 1);
}

//Merge Sort implementation with 1 thread
void mergeSort(vector<int> &arr, int left, int right){
    if(left>=right) return;

    int mid= (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);

}

void merge(vector<int> &arr, int left, int mid, int right){
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int l=0, r=0, i=left;
    int leftSize= leftArr.size();
    int rightSize= rightArr.size();

    while(l<leftSize && r<rightSize){
        if(leftArr[l]<= rightArr[r]){
            arr[i]= leftArr[l];
            l++;
        }else{
            arr[i]= rightArr[r];
            r++;
        }
        i++;
    }
    while(l<leftSize){
        arr[i]= leftArr[l];
        l++;
        i++;
    }
    while(r<rightSize){
        arr[i]= rightArr[r];
        r++;
        i++;
    }
    
}

int sum(int a, int b) {
    return a + b;
}

//Test main function
// int main(){
    
//     vector<int> arr = {38, 27, 43, 10,11, 3, 5, 92, 75, 61,24,5,88,15,49,67,34,22,19,8};
//     printArray(arr);
//     singleSort(arr);
//     printArray(arr);
//     return 0;
// }