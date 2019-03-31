#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
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
	printf("\n");
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

static Node *currNode(Node *head, int num) {
	Node *n = head;
	for(int i = 0; i< num; i++) {
		n = n -> next;
	}
	return n;
}

static Node* swapNodes(Node* a, int p, Node* b, int q, Node* head) {
	Node* preva = NULL;
	Node* temp = NULL;
	Node* prevb = currNode(head,q-1);
	if(a == head) {
		prevb->next = a;
		temp = b->next;
		b->next = a->next;
		a->next = temp;
		head = b;
	}
	else {
		preva = currNode(head, p-1);
		prevb->next = a;
		preva->next = b;
		temp = b->next;
		b->next = a->next;    
		a->next = temp;
	}
	return head;
}

static Node* insertNode(Node* a, Node* head, int position) {
	if (position == 0) {
		a->next = head;
		return a;
	}
	else {
		Node *prevb = currNode(head, position -1);
		Node *b = prevb->next;
		prevb->next = a;
		a->next = b;
		return head;
	}	
}

static Node* removeNode(Node* a, Node*head, int position) {
	if(position == 0) {
		head = a->next;
		a->next = NULL;
		return head;
	}
	else {
		Node *preva = currNode(head, position-1);
		preva->next = a->next;
		a->next = NULL;
		return head;
	}
}

static List* makeList() {
	List* list = malloc(sizeof(List));
	list->next = NULL;
	list->node = NULL;
	return list;
}
static List* createList(Node* head, int sequence) {
	List *list;
	List *head_list;
	if(sequence > 0) {
		head_list = makeList();
		list = (head_list);
	}
	else {
		return NULL;
	}
	for(int i = 1; i < sequence; i++) {
		while(1) {
			if(list->next == NULL) {
				list->next = makeList();
				list = list->next;
				break;
			}
			else {
				list = list->next;
			}
		}
	}
	//Store the nodes in the list;
	Node* nodes = (head);
	while(nodes != NULL) {
		list = head_list;
		for(int i = 0; i < sequence; i ++) {
			
			Node *list_node = list->node;
			while(1) {
				if(list->node == NULL) {
					list->node = nodes;
					list_node = list->node;
					nodes = nodes->next;
					list_node->next = NULL;
					
					break;
				}
				else if(list_node->next == NULL) {
					list_node->next = nodes;
					nodes = nodes->next;
					list_node->next->next = NULL;
					break;
				}
				else if(nodes != NULL) {
					list_node = list_node->next;
				}

			}
			list = list->next;

		}
	}
	return head_list;

}
static Node* bubbleSortList(Node *list, int size,int sequence, double *comps) { 
	Node *head = list;
	int i = 0;
	int j = 0;
	int k = 0;
	int swap_flag = 0;
	Node* a = NULL;
	Node* b = NULL;
	Node*key = NULL;
	/*	for(i = 0; i < sequence; i++) {
		for(j = i; j < size; j = j+sequence) {
		swap_flag = 0;
		for(k = i; k < size-j-sequence; k = k+sequence) {
	 *comps = *comps + 1;
	 a = currNode(head,k);
	 b = currNode(head,k+sequence);
	 if(a->value > b->value) {
	 head = swapNodes(a,k,b,k+sequence,head);
	 swap_flag = 1;
	 }
	 }
	 if(swap_flag == 0) {
	 break;
	 }
	 } */
	for(i = 0; i < sequence; i++) {
		for(j = i+sequence; j < size; j = j+sequence) {
			key = currNode(head, j);

			k = j-sequence;
			while(k >= i && (currNode(head,k)->value > key->value)) {
				*comps = *comps + 1;
				k = k - sequence;
			}
			head = removeNode(key, head, j);
			head = insertNode(key, head, k+sequence);
		}
		//	printList(head);
	}
	return head;
}



Node *List_Load_From_File(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("reading file failed");
		return NULL;
	}

	//Processing file name to get size
	int readsize = 0;
	long val = 0;
	int size = 0;
	long dummy;
	rewind(fp);
	while(!feof(fp)) {
		size = size + fread(&dummy, sizeof(long), 1, fp);
	}
	rewind(fp);
	printf("filesize = %d",size);
	readsize = fread(&val, sizeof(long), 1, fp);
	if(readsize == 0) {
		return NULL;
	}
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
	int curr_seq = 0;
	int size = listSize(list);
	long *sequence = Generate_2p3q_Seq(size, &sequence_size);
	for(int i = sequence_size-1; i >=0;i--) {
		curr_seq = sequence[i];
		List *lists = createList(list, curr_seq);
		while(1) {
			if(lists == NULL) {
				break;
			}
			printList(lists->node);
			lists = lists->next;
		}
		list = bubbleSortList(list, size, curr_seq, n_comp);
	}
	free(sequence);
	return list;

}

