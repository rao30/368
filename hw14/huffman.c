#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <string.h>
TreeNode *create_node(int c, long count) {
	TreeNode *new = malloc(sizeof(TreeNode));
	new -> ch = c;
	new -> count = count;
	new -> left = NULL;
	new -> right = NULL;
	new -> front = NULL;
	new -> rear = NULL;
	return new;
}


TreeNode *merge(TreeNode *old1, TreeNode *old2) {
	TreeNode *new = malloc(sizeof(TreeNode));
	new -> left = old1;
	new -> right = old2;
	new -> ch = 256;
	new ->count = (old1->count) +(old2->count);
	new -> front = NULL;
	new -> rear = NULL;
	return new;
}

int compare(TreeNode *t1, TreeNode *t2) {
	if(t1 -> count < t2 -> count) {
		return 1;
	}
	else if(t1 -> count == t2 -> count) {
		if(t1 -> ch < t2 -> ch) {
			return 1;
		}
		else {
			return 2;

		}
	}
	else {
		return 0;
	}
}

TreeNode * make_list(TreeNode **head, int c, long count) {
	TreeNode *t = create_node(c, count);
	TreeNode *n = (*head);
	while(1) {
		if(n -> front == NULL) {
			t -> front = NULL;
			t -> rear = n;
			n -> front = t;
			break;
		}
		n = n -> front;
	}
	return(*head);
}

TreeNode * sort_list(TreeNode **head) {
	int swap = 0;
	TreeNode *temp = (*head);
	long count;
	int ch;
	do {
		if(temp -> front -> count < temp -> count) {
			ch = temp -> ch;
			count = temp -> count;
			temp -> count = temp -> front -> count;
			temp -> ch = temp -> front -> ch;
			temp -> front -> count = count;
			temp -> front -> ch = ch;
			swap = swap + 1;
		}
		temp = temp -> front;
		if(temp -> front == NULL) {
			if(swap == 0) {
				temp = (*head);
				break;
			}
			else {
				swap = 0;
				temp = (*head);
			}
		}
	} while(1);
	return(*head);
}

TreeNode *make_tree(TreeNode **head) {
	TreeNode *temp = (*head);
	while(temp->front != NULL) {
		TreeNode *merged = merge(temp, temp->front);
		dequeue(&temp);
		dequeue(&temp);
		if(temp == NULL) {
			return merged;
		}
		insert(&temp,&merged);
	}
	return NULL;
}

void insert(TreeNode **head, TreeNode **node) {
	TreeNode *temp = (*head);
	TreeNode *insert = (*node);
	while(1) {
		if(temp==NULL) {
			end_queue((*head), (*node));
			break;
		}
		else if(insert->count > temp -> count) {
			temp = temp -> front;
		}
		else if(((insert->count) == (temp -> count)) && ((insert -> ch) >= (temp -> ch))) {
			temp = temp ->front;
		}
		else {
			insert->front = temp;
			insert->rear = temp->rear;
			temp->rear->front = insert;
			temp->rear = insert;
			break;

		}
	}
}





int treeSum(TreeNode *node) {
	if(node == NULL){
		return -1;
	}
	else if(node ->front == NULL) {
		return node -> count;
	}
	else {
		return ((node -> count) + (node->front->count));
	}
}

TreeNode *front(TreeNode *head) {
	if(head == NULL) {
		return NULL;
	}
	else {
		head = head -> front;
		return head;
	}
}

void nlr(TreeNode *head) {
	head -> left = NULL;
	head -> right = NULL;
}

void print_tree(TreeNode *tn, FILE *fp) {
	if((tn) == NULL) {
		return;
	}
	print_tree((tn)->left, fp);
	print_tree((tn)->right, fp);
	if((tn -> ch) < 256) {
		fprintf(fp,"ch = %c, count = %ld\n", (tn) -> ch, (tn) -> count);
		return;
	}

}

void traverse(TreeNode *tn, FILE*fp, char *code) {
	char *arrl;
	char *arrr;
	char left[] = "0";
	char right[] = "1";
	arrl = malloc(sizeof(char)* strlen(code));
	arrr = malloc(sizeof(char)* strlen(code));
	strcpy(arrl,code);
	strcpy(arrr,code);
	if((tn) == NULL) {
		return;
	}
	traverse((tn)->left, fp, strcat(arrl,left));
	traverse((tn)->right,fp, strcat(arrr,right));
	if((tn)->ch < 256) {
		fprintf(fp,"%c:%s\n",(tn)->ch,code);
	}
}
void end_queue(TreeNode *head, TreeNode *end) {
	TreeNode *temp = (head);
	if(temp == NULL) {
		temp = end;
		temp -> front = NULL;
		temp -> rear = NULL;
	}
	else {
		while(temp != NULL) {
			if(temp -> front == NULL) {
				end -> rear = temp;
				end -> front = NULL;
				temp -> front = end;
				break;
			}
			temp = temp -> front;
		}
	}
}

void  dequeue(TreeNode **head) {
	(*head) = (*head) -> front;
	if((*head) != NULL) {
		(*head)->rear = NULL;
	}
}


void print_queue(TreeNode **head, FILE *fp) {
	TreeNode *temp = malloc(sizeof(TreeNode));
	temp = (*head);
	while(temp != NULL) {
		fprintf(fp,"%c:%ld->",temp->ch,temp->count);
		temp = temp -> front;
	}
	fprintf(fp,"NULL\n");
}

void print_list(TreeNode **head, FILE *fp) {
	TreeNode *temp = malloc(sizeof(TreeNode));
	temp = (*head);
	while(temp != NULL) {
		fprintf(fp,"%c\n",temp->ch);
		temp = temp -> front;
	}
	fprintf(fp,"NULL");
}

void print(TreeNode **head) {
	TreeNode *temp = malloc(sizeof(TreeNode));
	temp = (*head);
	while(temp != NULL) {
		printf("%c:%ld->",temp->ch,temp->count);
		temp = temp -> front;
	}
	printf("NULL");
	free(temp);
}

void traverse2(TreeNode *tn, FILE *fp) {
	if((tn) == NULL) {
		return;
	}
	traverse2((tn)->left,fp);
	traverse2((tn)->right,fp);
	if((tn -> ch) < 256) {
		fprintf(fp,"%c%c",'1',(tn)->ch);
		return;
	}
	else {
		fprintf(fp, "0");
	}
}

void traverse3(TreeNode *tn, FILE *fp , int *shift, int *ch) {
	if((tn) == NULL) {
		return;
	}
	traverse3((tn)->left,fp,shift, ch);
	traverse3((tn)->right,fp,shift,ch);
	if((tn)->ch < 256) {
		if(*shift == 8) {
			fprintf(fp,"%c",*ch);
			(*shift) = 0;
			*ch = 0x00;
		}
		int mask = 0xFF;
		(*shift)++;
		int dir_mask = (mask >> 7)  << (8-(*shift));
		int curr_mask = (mask >> *shift) << (*shift);
		int remaining = mask >> (8-(*shift));
		int curr = (curr_mask & (tn)->ch);
		curr = curr >> (*shift); 
		int final = (*ch | dir_mask | curr);
		*ch = (remaining & (tn)->ch);
		*ch = *ch << (8-(*shift));

		fprintf(fp,"%c",final);
	}
	else {
		if(*shift == 8) {
			fprintf(fp,"%c",*ch);
			*shift = 0;
			*ch = 0x00;
		}
		(*shift)++;	
	}
	return;
}


void free_Tree(TreeNode *t) {
	if (t == NULL) {
		return;
	}
	free_Tree(t -> front);
	free_Tree(t -> rear);
	free_Tree(t -> left);
	free_Tree(t -> right);
	free(t);
}



