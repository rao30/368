#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>
void swap(long* a, long* b)
{
	long t = *a;
	*a = *b;
	*b = t;
}


int partition (long arr[], int low, int high)
{
	long pivot = arr[high];
	//	long pivot = threeMedian(&arr[low], &arr[(low+high)/2], &arr[high]);
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
int threeMedian_partition(long arr[], long low, long high) {
	long mid = (low+high)/2;
	long l = arr[low];
	long m = arr[mid];
	long u = arr[high];
	if ((l > m) != (l > u)) {
		swap(&arr[low], &arr[high]);
	}
	else if ((m > l) != (m > u)) {
		swap(&arr[mid], &arr[high]);
	}
	return partition(arr, low, high);
}


void quickSort(long arr[], long low, long high)
{
	if (low < high)
	{
		long pi = threeMedian_partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void Quick_Sort(long *Array, int Size) {
	quickSort(Array, 0 , Size -1);

}

long min(long x, long y) { return (x<y)? x :y; } 
void merge(long arr[], long left, long mid, long right) 
{ 
	long i;
	long j;
	long k; 
	long l = mid - left + 1; 
	long r =  right - mid; 
	long *LeftArr = malloc(l*sizeof(long));
	long *RightArr = malloc(r*sizeof(long));
	for (i = 0; i < l; i++) {
		LeftArr[i] = arr[left + i]; 
		}
	for (j = 0; j < r; j++) { 
		RightArr[j] = arr[mid + 1+ j];
		}
	i = 0; 
	j = 0; 
	k = left; 
	while (i < l && j < r) 
	{ 
		if (LeftArr[i] <= RightArr[j]) 
		{ 
			arr[k] = LeftArr[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = RightArr[j]; 
			j++; 
		} 
		k++; 
	} 
	while (i < l) 
	{ 
		arr[k] = LeftArr[i]; 
		i++; 
		k++; 
	} 
	while (j < r) 
	{ 
		arr[k] = RightArr[j]; 
		j++; 
		k++; 
	} 
	free(LeftArr);
	free(RightArr);
} 


void Merge_Sort(long *Array, int Size){
	long n = Size;
	long curr_size; 
	long left_start;
	for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
	{ 
		for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
		{ 
			long mid = min(left_start + curr_size - 1, n - 1);
			long right_end = min(left_start + 2*curr_size - 1, n-1); 
			merge(Array, left_start, mid, right_end); 
		} 
	} 
}
