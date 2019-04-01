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
	//	printf("counter = %d\n\n\n\n\n\n",counter);
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

static void printLists(List *list) {
	List *l = list;
	while(1) {
		printList(l->node);
		printf("\n");
		if(l->next == NULL) {
			break;
		}
		l = l->next;
	}
}
static Node *make_list(Node *head, long val, Node *tail) {
	Node *t = create_node(val);
	Node *n = (head);
	/*	while(1) {
		if(n -> next == NULL) {
		t->next = NULL;
		n -> next = t;
		t->value = val;
		break;
		}
		n = n -> next;
		} */
	if(tail == NULL) {
		t->next = NULL;
		n->next = t;
		return t;
	}
	else {
		t->next = NULL;
		t->value = val;
		tail->next = t;
		return t;
	}

}

static Node *append_list(Node *head, Node *node, Node *tail) {
	Node *t = node;
	Node *n = (head);
/*	while(1) {
		if(n -> next == NULL) {
			t->next = NULL;
			n -> next = t;
			break;
		}
		n = n -> next;
	} */
	if(tail == NULL) {
	t->next = NULL;
	n->next = t;
	return t;
	}
	else {
	t->next = NULL;
	tail->next = t;
	return t;
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

static List* makeList(Node *node) {
	List* list = malloc(sizeof(List));
	list->next = NULL;
	list->tail = NULL;
	list->node = node;
	return list;
}


static List* generateListSequence(int sequence) {
	List *list = makeList(NULL);
	List *tempList = list;
	for(int i = 1; i < sequence; i++) {
		tempList->next = makeList(NULL);
		tempList = tempList->next;
	}
	return list;
}

/*static List* createList(Node* nodeHead, int sequence) {
	Node *tempNode = nodeHead;
	List* newList = generateListSequence(sequence);
	List* head = newList;
	while(1) {
		if(tempNode == NULL) {
			break;
		}
		if(newList == NULL) {
			newList = head;
		}
		if(newList->node == NULL) {
			newList->node = tempNode;
			tempNode = tempNode->next;
			newList->tail = newList->node;
			newList->node->next = NULL;
			newList = newList->next;

		}
		else {
			Node *temper = tempNode;
			tempNode = tempNode->next;
			newList->tail = append_list(newList->node, temper, newList->tail);
			newList = newList->next;
		}
	}
	return head;
} */

static List* createList(List *oldList, int size, int sequence) {
	List *oldListHead = oldList;
	List *newList = generateListSequence(sequence);
	List *head = newList;
	int i = 0;
	while(1) {
		if(i == size) {
		break;
		}
		if(oldList == NULL) {
		oldList = oldListHead;
		}
		if(newList == NULL) {
		newList = head;
		}
		if(newList->tail == NULL) {
		newList->node = oldList->node;
		oldList->node = oldList->node->next;
		newList->tail = newList->node;
		newList->node->next = NULL;
		oldList = oldList->next;
		newList = newList->next;
		} 
		else {
		newList->tail->next = oldList->node;
		oldList->node = oldList->node->next;
		newList->tail = newList->tail->next;
		newList->tail->next = NULL;
		oldList = oldList->next;
		newList = newList->next;
		}
		i++;
	}
	oldList = oldListHead;
	freeLists(oldList);
	return head;
}

static Node* combineList(List* Lists, int size) {
	List *tempLists = Lists;
	Node *head = NULL;
	Node *temp = head;
	int i = 0;
	while(1) {
		if(tempLists == NULL) {
			tempLists = Lists;
		}
		if(i == size) {
			break;
		}
		if(tempLists->node != NULL && head == NULL) {
			head = tempLists->node;
			tempLists->node = tempLists->node->next;
			tempLists = tempLists->next;
			head->next = NULL;
			temp = head;
			i++;
		}
		else {
			temp->next = tempLists->node;
			tempLists->node = tempLists->node->next;
			tempLists = tempLists->next;
			temp = temp->next;
			temp->next = NULL;
			i++;
		}
	}
	return head;
}

static Node* SortList(Node *List, double *comps)
{
	// zero or one element in list
	if(List == NULL || List->next == NULL)
		return List;
	// head is the first element of resulting sorted list
	Node *head = NULL;
	while(List != NULL) {
		Node * current = List;
		List = List->next;
		if(head == NULL || current->value < head->value) {
			// insert into the head of the sorted list
			// or as the first element into an empty sorted list
			*comps = *comps + 1;
			current->next = head;
			head = current;
		} else {
			// insert current element into proper position in non-empty sorted list
			Node *p = head;
			while(p != NULL) {
				if(p->next == NULL || // last element of the sorted list
						current->value < p->next->value) // middle of the list
				{
					// insert into middle of the sorted list or as the last element
					*comps = *comps + 1;
					current->next = p->next;
					p->next = current;
					break; // done
				}
				p = p->next;
			}
		}
	}
	return head;
}


void sortedInsert(Node** head_ref, Node* new_node, double *comps) 
{ 
	Node* current; 
	/* Special case for the head end */
	if (*head_ref == NULL || (*head_ref)->value >= new_node->value) {
		*comps = *comps + 1;
		new_node->next = *head_ref; 
		*head_ref = new_node; 
	}
	else
	{ 
		/* Locate the node before the point of insertion */
		current = *head_ref; 
		while (current->next!=NULL && current->next->value < new_node->value) 
		{ 
			*comps = *comps+1;
			current = current->next; 
		} 
		new_node->next = current->next; 
		current->next = new_node; 
	} 
}
void insertionSort(Node **head_ref, double *comps) 
{ 
	// Initialize sorted linked list 
	Node *sorted = NULL; 

	// Traverse the given linked list and insert every 
	// node to sorted 
	Node *current = *head_ref;                        
	while (current != NULL) 
	{ 
		// Store next for next iteration 
		Node *next = current->next; 

		// insert current in sorted linked list 
		sortedInsert(&sorted, current, comps); 

		// Update current 
		current = next; 
	} 

	// Update head_ref to point to sorted linked list 
	*head_ref = sorted; 
} 

/* function to insert a new_node in a list. Note that this 
   function expects a pointer to head_ref as this can modify the 
   head of the input linked list (similar to push())*/

void freeLists(List *list) {
	List *temp;
	while(list != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
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
	//	printf("filesize = %d",size);
	readsize = fread(&val, sizeof(long), 1, fp);
	if(readsize == 0) {
		return NULL;
	}
	Node *head = create_node(val);
	Node *tail = NULL;
	for(int i = 1; i < size; i++) {
		readsize = fread(&val, sizeof(long), 1, fp);
		tail = make_list(head, val, tail);
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
	List *oldList = generateListSequence(1);
	oldList->node = list;
	List *newList = NULL;
	List *tempList = oldList;
	for(int i = sequence_size-1; i >= 0 ; i--) { 
		newList = createList(tempList, size, sequence[i]);
		tempList = newList;
		for(int j = 0; j < sequence[i]; j++) {
			tempList->node = SortList(tempList->node, n_comp);
		//	insertionSort(&tempList->node, n_comp);
			tempList = tempList->next;
		}
		tempList = newList;
//	printLists(tempList);
	}
	list = combineList(newList, size);
	freeLists(newList);
	free(sequence);
	return  list;
}

