#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

typedef struct _List {
	Node *node;
	Node *tail;
	struct _List *next;
} List;
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

/*static void printList(Node *head) {
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
  } */
static Node *make_list(Node *head, long val, Node *tail) {
	Node *t = create_node(val);
	Node *n = (head);
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

static List* makeList(Node *node) {
	List* list = malloc(sizeof(List));
	list->next = NULL;
	list->tail = NULL;
	list->node = node;
	return list;
}
void freeLists(List *list) {
	List *temp;
	while(list != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
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

static Node* SortList(Node *list, double *comps)
{

	if(list == NULL || list->next == NULL)
		return list;

	Node *head = NULL;
	while(list != NULL) {
		Node * current = list;
		list = list->next;
		if(head == NULL || current->value < head->value) {

			*comps = *comps + 1;
			current->next = head;
			head = current;
		} else {

			Node *temp = head;
			while(temp != NULL) {
				if(temp->next == NULL || current->value < temp->next->value)
				{
					*comps = *comps + 1;
					current->next = temp->next;
					temp->next = current;
					break;
				}
				temp = temp->next;
			} 
		}
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

