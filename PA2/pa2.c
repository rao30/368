
#include "shell_array.h"
#include "shell_list.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void printArray(long *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("The array[%d] = %ld\n", i, array[i]);
	}
}
static void printList(Node *head) {
	Node *n = head;
	while(1) {
		printf("Node Val = %ld\n", n->value);
		if(n->next == NULL) {
			break;
		}
		n = n->next;
	}
}
void freeList(Node *head) {
	Node *temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
int main(int argc, char* argv[]) {
	int size = 0;
	if(strcmp(argv[1],"-a") == 0) {
	long *inputArray;
	inputArray = Array_Load_From_File(argv[2], &size);
	if(inputArray == NULL) {
		printf("failed to load file");
		return EXIT_FAILURE;
	}
	double comps = 0;
	Array_Shellsort(inputArray, size, &comps);
	Array_Save_To_File(argv[3], inputArray, size);
	free(inputArray);
	printf("%le\n",comps);
	}
	else if (strcmp(argv[1],"-l") == 0) {
	Node *head = List_Load_From_File(argv[2]);
	double compsA = 0;
	Node *sortedList = List_Shellsort(head, &compsA);
//	printList(sortedList);
	printf("%le\n",compsA);
	List_Save_To_File(argv[3], sortedList);
	freeList(sortedList);
	return 0;
	}
}
