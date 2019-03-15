#include "shell_list.h"
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
	return size;
}

static int listSize(Node *head) {
	Node *n = head;
	int counter = 0;
	while(1) {
		counter = counter+1;
		if(n->next == NULL) {
			break;
		}
		n = n->next;
	}
	return counter;
}

static Node *create_node(long val) {
	Node *new = malloc(sizeof(Node));
	new -> value = val;
	new -> next = NULL;
	return new;
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
static void make_list(Node *head, long val) {
	Node *t = create_node(val);
	Node *n = (head);
	while(1) {
		if(n -> next == NULL) {
			t->next = NULL;
			n -> next = t;
			t->value = val;
			break;
		}
		n = n -> next;
	}
}

Node *currNode(Node *head, int num) {
	Node *n = head;
	for(int i = 0; i< num; i++) {
		n = n -> next;
	}
	return n;
}
static Node* bubbleSortList(Node *list, int size,int sequence, double *comps) { 
	Node *head = list;
	int i = 0;
	int j = 0;
	int swap_flag = 0;
	Node *temp;
	Node* a;
	Node* b;
	Node* preva;
	Node* prevb;
	//	printf("size = %d\n",size);
	//	long temp = 0;
	for(i = 0; i < size; i++) {
		swap_flag = 0;
		for(j = i; j < size-sequence-i; j = j+sequence) {
			//	printf("before op\n");
			//	printList(head);
			//	printf("i = %d, j = %d\n",i,j);
			a = currNode(head,j);
			b = currNode(head,j+sequence);
			*comps = *comps+1;
			if (a->value > b->value) {
				if(j == 0) {
					prevb = currNode(head,j+sequence-1);
					prevb->next = a;
					temp = b->next;
					b->next = a->next;
					a->next = temp;
					head = b;
				}
				else {
					preva = currNode(head, j-1);
					prevb = currNode(head, j+sequence-1);
					prevb->next = a;
					preva->next = b;
					temp = b->next;
					b->next = a->next;    
					a->next = temp;   
				}
				//	printf("prevb: %ld, a: %ld, b: %ld\n", prevb->value,a->value,b->value);
				//	printf("after op\n");
				//	printList(head);
				swap_flag = 1;
			}
		}
		if(swap_flag == 0 && ((sequence == 1) )) {
			break;
		}
	}
	return head;

}
Node *List_Load_From_File(char *filename) {
	//Processing file name to get size
	int readsize = 0;
	int size = getSize(filename);
	long val = 0;
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("reading file failed");
		return NULL;
	}
	rewind(fp);
	readsize = fread(&val, sizeof(long), 1, fp);
	Node *head = create_node(val);
	for(int i = 1; i < size; i++) {
		readsize = fread(&val, sizeof(long), 1, fp);
		make_list(head, val);
	}
	fclose(fp);
	return(head);
}

int List_Save_To_File(char *filename, Node *list) {
	FILE *fp = fopen(filename, "wb");
	int writeSize = 0;
	long val;
	if(fp == NULL) {
		return EXIT_FAILURE;
	}
	rewind(fp);
//	Node *n = list;
	while(1) {
		val = list->value;
		writeSize = writeSize +  fwrite(&val, sizeof(long), 1, fp);
		if(list->next == NULL) {
			break;
		}
		list = list->next;
	}
	fclose(fp);
	return writeSize;
}


Node *List_Shellsort(Node *list, double *n_comp) {
	int sequence_size;
	int pos = 0;
	int curr_seq = 0;
	int size = listSize(list);
	long *sequence = Generate_2p3q_Seq(size, &sequence_size);
	for(int i = sequence_size-1; i >=0;i--) {
		pos = 0;
		curr_seq = sequence[i];	
		list = bubbleSortList(list, size, curr_seq, n_comp);
	}
	free(sequence);
	return list;

}

