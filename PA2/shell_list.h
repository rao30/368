#ifndef __SHELL_LIST_H__
#define __SHELL_LIST_H__

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;


typedef struct _List {
	Node *node;
	Node *tail;
	struct _List *next;
} List;


Node *List_Load_From_File(char *filename);

int List_Save_To_File(char *filename, Node *list);

Node *List_Shellsort(Node *list, double *n_comp);

#endif

