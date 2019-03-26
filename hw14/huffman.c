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
	TreeNode *ins = (*node);
	while(1) {
		if(temp==NULL) {
			end_queue((*head), (*node));
			break;
		}
		else if(ins->count > temp -> count) {
			temp = temp -> front;
		}
		else if(((ins->count) == (temp -> count)) && ((ins -> ch) >= (temp -> ch))) {
			temp = temp ->front;
		}
		else {
			ins->front = temp;
			ins->rear = temp->rear;
			temp->rear->front = ins;
			temp->rear = ins;
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


void traverse(TreeNode *tn, FILE*fp, char *code, char list[], char vals[][256], long *counter) {
	char arrl[256] = {'\0'};
	char arrr[256] = {'\0'};
	char *left = "0";
	char *right = "1";
	if((tn) == NULL) {
		return;
	}
//	arrl = malloc(sizeof(char) * (strlen(code)+1));
//	arrr = malloc(sizeof(char) * (strlen(code)+1));
	strcpy(arrl,code);
	strcpy(arrr,code);
	strcat(arrl,left);
	strcat(arrr,right);

	traverse((tn)->left, fp, arrl, list,vals,counter);
	//free(arrl);
	traverse((tn)->right,fp, arrr,list,vals,counter);
	//free(arrr);
	if((tn)->ch < 256) {
		//	fprintf(fp,"%c:%s\n",(tn)->ch,code);
		//	list[*counter] = malloc(sizeof(char));
		//	char* c = (char)(tn)->ch;
		list[*counter] = (char)(tn)->ch;
	//	vals[*counter] = malloc(sizeof(char)*strlen(code));
		strcpy(vals[*counter], code);
		fprintf(fp,"%c:%s\n",list[*counter],vals[*counter]);

//		fprintf(fp,"%c:%s\n",list[*counter],code);
		*counter = *counter+1;
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

	//	traverse2((tn)->left,fp);
	//	traverse2((tn)->right,fp);
	if((tn -> ch) < 256) {
		fprintf(fp,"%c%c",'1',(tn)->ch);
		return;
	}
	else {
		fprintf(fp, "0");
	}
	traverse2((tn)->left,fp);
	traverse2((tn)->right,fp);
}
//FUNCTIONS TO PRINT COMPRESSED FILE
void printdoubles(FILE *fp, long c1, long c2, long c3) {
	if(fp == NULL) {
		return;
	}
	c1 = c1+c2+24;
	fwrite(&c1,sizeof(long),1, fp);
	fwrite(&c2,sizeof(long),1, fp);
	fwrite(&c3,sizeof(long),1, fp);

}

void printTree(FILE *treeTop, FILE *fp2, long *c2) {
	rewind(treeTop);
	unsigned char valWrite = 0x00;
	unsigned char mask = 0xFF;
	int shift = 0;
	unsigned char ch;
	int flag = 0;
	while(1) {
		ch = fgetc(treeTop);

		if(feof(treeTop)) {
			if(shift > 0) {
				fprintf(fp2, "%c", valWrite);
				*c2 = *c2+1;
				shift = 0;
				valWrite = 0x00;
			}
			break;

		}
		mask = 0xFF;
		if((ch == '0') && (flag == 0)) {
			shift = shift+1;
		}
		else if((ch == '1') && (flag == 0)) {
			flag = 1;
			unsigned char tempMask = 0x01;
			tempMask = tempMask << shift;
			valWrite = valWrite | tempMask;
			shift = shift+1;
		}
		else if((ch < 256) && (ch > -1)) {
			flag = 0;
			int numbits = 8-shift;
			unsigned char tempMask = (mask >> (8- numbits));
			tempMask = (ch & tempMask) << shift;
			valWrite = valWrite | tempMask;
			fprintf(fp2, "%c", valWrite);
			*c2 = *c2+1;
			tempMask = (mask >> numbits) << numbits;
			tempMask = (ch & tempMask) >> numbits;
			valWrite = 0x00 | tempMask;
			shift = 8-numbits;
		}
		if (shift == 8) {
			fprintf(fp2, "%c", valWrite);
			*c2 = *c2+1;
			valWrite = 0x00;
			shift = 0;

		}

	}
}
void printCompress(FILE *input, FILE *output, char list[][256], char chars[], long *c1, long counter) {
	rewind(input);
	char ch;
	int index=0;
	int index2=0;
	char bits;
	int shift = 0;
	unsigned char valWrite = 0x00;
	unsigned char mask = 0xFF;
	long ct = 0;
	//	while(1){
	for(long i = 0; i < counter; i++) {
		ch = fgetc(input);
		ct = ct+1;
		if(feof(input)) {
			if(shift > 0) {
				shift = 0;
				fprintf(output, "%c",valWrite);
				*c1 = *c1+1;
			}
			break;

		}
		index = 0;
		while(1) {
			if(ch == chars[index]) {
				//	printf("%c == %c\n", ch, chars[index]);
				index2 = 0;
				while(1) {
					bits = list[index][index2];
					//		printf("%c == %c\n", ch, bits);
					if(shift == 8) {
						fprintf(output, "%c", valWrite);
						*c1 = *c1+1;
						valWrite = 0x00;
						shift = 0;
					}
					if(bits == '\0') {
						break;
					}
					mask = 0xFF;
					if(bits == '0') {
						shift = shift+1;
					}

					else if(bits == '1') {
						unsigned char tempMask = 0x01;
						tempMask = tempMask << shift;
						valWrite = valWrite | tempMask;
						shift = shift+1;
					}
					//		printf("value of shift: %d\n",shift);
					index2 = index2+1;

				}
				break;
			}
			//	if(ch <0) {
			//		break;
			//	}
			index = index+1 ;
		}

	}
	if(shift > 0) {
		shift = 0;
		fprintf(output, "%c",valWrite);
		*c1 = *c1+1;
	}

}

void listArray(FILE *list, char *table[], int chars[]) {
	rewind(list);
	int flag = 0;
	int count = 0;
	int arrcounter = 0;
	char *arr;
	char *ch = NULL;
	while(1) {
		*ch = fgetc(list);
		if(flag == 1) {
			if (*ch != ':' && *ch != '\n') {
				arrcounter++;
				arr = malloc(sizeof(char)*(strlen(table[count])+1));
				arr = strcat(table[count],ch);
				strcpy(arr,table[count]);
			}
			if(*ch == '\n') {
				arrcounter = 0;
				count++;
				flag = 0;
			}
		}
		if(flag == 0) {
			flag = 1;
			chars[count] = *ch;
		}

		if(feof(list)) {
			break;
		}
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
	free_Tree(t -> left);
	free_Tree(t -> right);
	free(t);
}



