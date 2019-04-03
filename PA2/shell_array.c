#include "shell_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"


/*static void printArray(long *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("The array[%d] = %ld\n", i, array[i]);
	}
} */
static void bubbleSort(long arr[], int size,int sequence, double *comps) { 
	//	*comps =10;
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < sequence; i++) {
		for(j = i+sequence; j < size; j = j+sequence) {
			long key = arr[j];
			k = j-sequence;
			while(k >= i && arr[k] > key) {
				*comps = *comps + 1;
				arr[k+sequence] = arr[k];
				k = k - sequence;
			}
			arr[k+sequence] = key;
		}
	}
}


long *Array_Load_From_File(char *filename, int *size) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		*size = 0;
		return NULL;
	}
	long dummy;
	rewind(fp);
	while(!feof(fp)) {
		*size = *size + fread(&dummy, sizeof(long), 1, fp);
	}
	rewind(fp);
	long * longArray = malloc(sizeof(long)*(*size));
	if (longArray == NULL) {
		*size = 0;
		return NULL;
	}

	fread(longArray, sizeof(long), *size, fp);
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
	for(int i = sequence_size-1; i >=0;i--) {
		pos = 0;
		curr_seq = sequence[i];	
		bubbleSort(array, size, curr_seq, n_comp);
	}
	free(sequence);
}



