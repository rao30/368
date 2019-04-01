#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
static long *createLongArray(int size) {
	long *array = malloc(sizeof(long)*size);
	return array;
}

static long powa(long a, long b) {
	long power = 1;
	for(long i = 0; i < b; i++) {
		power = power * a;
	}
	return power;
}

static void printArray(long *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("The array[%d] = %ld\n", i, array[i]);
	}
}
long *Generate_2p3q_Seq(int length, int *seq_size) {
	//Variables
	long seq_num = 0;
	long p = 0;
	long q = 0;
	long size = 0;
	while (powa(2,p) < length) {
		for (q = 0; q <= p; q++) {
			seq_num = powa(2, p-q) * powa(3, q);	//Generating sequence number
		//	printf("calculating sequence = %d", seq_num);
			if(seq_num < length) {
				size = size + 1;
			}
		}
		p++;
	}
	//Create array
	*seq_size = size;
//	printf("sequence size = %d", *seq_size); 
	long * sequence = createLongArray(*seq_size);
	if (sequence == NULL) {
		*seq_size = 0;
		return NULL;
	}
	size = 0;
	p = 0;
	q = 0;
	//Store Values in array
	while (powa(2, p) < length) {
		for (q = 0; q <= p; q++) {
			seq_num = powa(2, p - q) * powa(3, q);	//Generating sequence number
			if (seq_num < length) {
				sequence[size] = seq_num;
				size = size + 1;
			}
		}
		p++;
	}
	//Sorting the Array
	int swap_flag = 0;
	for (int i = 0; i < *seq_size; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < *seq_size; j++)             //Loop for comparing other values
		{
			if (sequence[j] > sequence[i])                //Comparing other array elements
			{
				int tmp = sequence[i];         //Using temporary variable for storing last value
				sequence[i] = sequence[j];            //replacing value
				sequence[j] = tmp;             //storing last value
				swap_flag = 1;
			}
		}
		if (swap_flag == 0) {
			break;
		}
	}
//	printArray(sequence, *seq_size);
	return sequence;
}

