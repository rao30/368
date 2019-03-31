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
	printf("counter = %d\n\n\n\n\n\n",counter);
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

static void append_list(Node *head, Node *node) {
    Node *t = node;
    Node *n = (head);
    while(1) {
        if(n -> next == NULL) {
            t->next = NULL;
            n -> next = t;
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

static List* makeList(Node *node) {
	List* list = malloc(sizeof(List));
	list->next = NULL;
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

static List* createList(List* list, int sequence) {
    List* temp = list;
    List* newList = generateListSequence(sequence);
    List* head = newList;

    int flag = 1;
    while(1) {
        if(temp == NULL) {
            temp = list;
            if(temp->node == NULL) {
                break;
            }
        }
        if(flag == 0) {
            if(temp->node == NULL) {
                break;
            }
        }
        if(newList == NULL) {
            newList = head;
        }
        if(newList->node == NULL) {
            newList->node = temp->node;
            newList = newList->next;
            temp->node = temp->node->next;
            temp = temp->next;
        }
        else {
            append_list(newList->node, temp->node);
            newList = newList->next;
            temp->node = temp->node->next;
            temp = temp->next;

        }

    }
    return head;
}


static Node* SortList(Node *List)
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
	List *lists = makeList(list);
	List *newLists = createList(lists, sequence[sequence_size-1]);
	printf("sequence size = %d", sequence[sequence_size-1]);

	/*for(int i = sequence_size-1; i >=0;i--) {
		curr_seq = sequence[i];
		List *lists = createList(list, curr_seq);
		while(1) {
			if(lists == NULL) {
				break;
			}
			printList(lists->node);
			lists = lists->next;
		} */
		//list = bubbleSortList(list, size, curr_seq, n_comp);
		list = SortList(newLists->node);
		printList(newLists->node);
	//}
	free(sequence);
	return list;

}

