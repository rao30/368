#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	printf("size of array = %d", *size);
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
	int writeSize = 0;
	if(fp == NULL) {
		return EXIT_FAILURE;
	}

	rewind(fp);
	for(int i = 0; i < size; i++) {
		writeSize = fwrite(&array[i], sizeof(long), 1, fp);
		if(writeSize != 1) {
			break;
		}
	}
	fclose(fp);
	return writeSize;
}

static void printArray(long *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("The array[%d] = %ld\n", i, array[i]);
	}
}

int main(int argc, char* argv[]) {
	int size = 0;
	if (argc < 4) {
		return EXIT_FAILURE;
	}
	if(strcmp(argv[1],"-q") == 0) {
		long *inputArray;
		inputArray = Array_Load_From_File(argv[2], &size);
		if (inputArray == NULL) {
			printf("failed to load file");
			return EXIT_FAILURE;
		}
		clock_t t;
		t = clock();
		Quick_Sort(inputArray, size);
		t = clock() - t;
		double time_taken = 1000*((double)t)/CLOCKS_PER_SEC; // in seconds
		printf("quicksort took %f ms to execute \n", time_taken);
		Array_Save_To_File(argv[3], inputArray, size);
		free(inputArray);
		return EXIT_SUCCESS;
	}
	else if(strcmp(argv[1],"-m") == 0) {
		long *inputArray;
		inputArray = Array_Load_From_File(argv[2], &size);
		if (inputArray == NULL) {
			printf("failed to load file");
			return EXIT_FAILURE;
		}
		clock_t t;
		t = clock();
		Merge_Sort(inputArray, size);
		t = clock() - t;
		double time_taken = 1000*((double)t)/CLOCKS_PER_SEC;
		printf("mergesort took %f ms to execute \n", time_taken);
		Array_Save_To_File(argv[3], inputArray, size);
		free(inputArray);
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}


