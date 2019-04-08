#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void swap(long* a, long* b)
{
	long temp = *a;
	*a = *b;
	*b = temp;
}


static long partition (long arr[], int low, int high)
{
	long pivot = arr[high];
	//	long pivot = threeMedian(&arr[low], &arr[(low+high)/2], &arr[high]);
	int i = (low - 1);
	int j = low;
	while(j <= high- 1)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


static long threeMedian_partition(long arr[], long low, long high) {
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

static void quickSort(long arr[], long low, long high)
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

static long min(long x, long y) { 
	if( x < y) {
	return x;
	}
	else {
	return y;
	}
} 

static void merge(long arr[], long left, long mid, long right) 
{ 
	long i = 0;
	long j = 0;
	long k = 0; 
	long l = mid - left + 1; 
	long r =  right - mid; 
	long *LeftArr = malloc(l*sizeof(long));
	long *RightArr = malloc(r*sizeof(long));
	//Dividing array into two parts
	memcpy(LeftArr, &arr[left], l*sizeof(long));
	memcpy(RightArr, &arr[mid + 1], r*sizeof(long));
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
		k++;
		j++;
	} 
	free(LeftArr);
	free(RightArr);
} 


void Merge_Sort(long *Array, int Size){
	long n = Size;
	long cs = 1; 
	long ls;
	while(cs <= n-1) {
		ls = 0;
		while(ls < n-1) {
			long mid = min(ls + cs - 1, n - 1);
			long r = min((2 * cs) + ls - 1, n-1); 
			merge(Array, ls, mid, r); 
			ls = ls + 2*cs;
		}
		cs = 2*cs;
	}
}
