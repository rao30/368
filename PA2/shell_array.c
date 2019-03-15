#include "shell_array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
static int getSize(char *filename) {
	int size = 0;
	int len = strlen(filename);
	char *s = (char*)malloc(len - 1);
	strncpy(s, filename, len - 2);
	s[len - 2] = '\0';
	size = atoi(s);
	free(s);
//	size = 15;
	return size;
}

static void printArray(long *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("The array[%d] = %ld\n", i, array[i]);
	}
}
static void bubbleSort(long arr[], int size,int sequence, double *comps) { 
	//	*comps =10;
	int i = 0;
	int j = 0;
	int swap_flag = 0;
	long temp = 0;
/*	for(i = 0; i < size; i++) {
		swap_flag = 0;
		for(j = i+sequence; j < size; j = j+sequence) {
			*comps = *comps+1;
			if (arr[j] < arr[i])                //Comparing other array elements
			{
				temp = arr[i];         //Using temporary variable for storing last value
				arr[i] = arr[j];            //replacing value
				arr[j] = temp;             //storing last value
		//		j = i+sequence;
				swap_flag = 1;
			}
		}
	//	if(swap_flag ==) {
	//	break;
	//	}
	} */
	for(i = 0; i < size; i++) {
		swap_flag = 0;
		for(j = i; j < size-sequence-i; j = j+sequence) {
			*comps = *comps+1;
				if (arr[j] > arr[j+sequence]) {
				temp = arr[j+sequence];
				arr[j+sequence] = arr[j];    
				arr[j] = temp;            
				swap_flag = 1;
			}
		}
		if(swap_flag == 0 && ((sequence == 1) )) {
		break;
		}
	}

} 



long *Array_Load_From_File(char *filename, int *size) {
	//Processing file name to get size
	*size = getSize(filename);
	//	*size = 30;
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("reading file failed");
		*size = 0;
		return NULL;
	}
	rewind(fp);
	long * longArray = malloc(sizeof(long)*(*size));
	if (longArray == NULL) {
		*size = 0;
		return NULL;
	}

	int readsize = fread(longArray, sizeof(long), *size, fp);
	if (readsize == 0) {
		free(longArray);
		*size = 0;
		return NULL;
	}
	fclose(fp);
	return longArray;
}

int Array_Save_To_File(char *filename, long *array, int size) {
	FILE *fp = fopen(filename, "wb");
	if(fp == NULL) {
	return EXIT_FAILURE;
	}
	rewind(fp);
	int writeSize = fwrite(array, sizeof(long), size, fp);
	fclose(fp);
	return writeSize;
}

void Array_Shellsort(long *array, int size, double *n_comp) {
	int sequence_size;
	int pos = 0;
	int curr_seq = 0;
	long *sequence = Generate_2p3q_Seq(size, &sequence_size);
//	printArray(array, size);
//	printf("\n\n");
	for(int i = sequence_size-1; i >=0;i--) {
		pos = 0;
		curr_seq = sequence[i];	
		bubbleSort(array, size, curr_seq, n_comp);
	}
	free(sequence);
//	printArray(array, size);
//	printf("\n Number of comparisions = %f",*n_comp);
}



