#include "sorting.h"

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int threeMedian(int a, int b, int c) {
    if ((a > b) != (a > c))
        return a;
    else if ((b > a) != (b > c))
        return b;
    else
        return c;
}

int partition (int arr[], int low, int high)
{
    //int pivot = arr[high];
    int pivot = threeMedian(arr[low], arr[(low+high)/2], arr[high]);
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void Quick_Sort(long *Array, int Size) {
    quickSort(Array, 0 , Size -1);

}

void Merge_Sort(long *Array, int Size) {

}