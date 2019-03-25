#include <stdlib.h>
#include "tree.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
	if(argc < 3) {
		return EXIT_FAILURE;
	}
	if(strcmp(argv[1],"-b") == 0 && argc == 4) {
		FILE *fp = fopen(argv[2], "rb");
		if (fp == NULL) {
			printf("%d\n", -1);
			return EXIT_FAILURE;
		}
		int val;
		char ch;
		int flag = 1;
		int readCheck;
		rewind(fp);
		Node *root = NULL;
		while(!feof(fp)) {
			readCheck = fread(&val, sizeof(int), 1, fp);
			if(readCheck != 1) {
				break;
			}
			readCheck = fread(&ch, sizeof(char), 1, fp);
			if(readCheck != 1) {
				break;
			}
			if(ch == 'i') {
				if(flag == 1) {
					root = insert(root, val);
					balance(&root);
					flag = 0;
				}
				else {
					insert(root, val);
					balance(&root);
				}
			}
			else if(ch == 'd') {
				delete(&root, val);
			}
		}
		FILE *writeFile = fopen(argv[3], "wb");
		if(writeFile == NULL) {
			free(root);
			fclose(fp);
			return EXIT_FAILURE;
		}
		preOrder(root, writeFile);
		free_Tree(root);
		fclose(fp);
		fclose(writeFile);
	}

	if(strcmp(argv[1],"-e") == 0 && argc == 3) {
		Node *root = malloc(sizeof(Node));
		int readStatus = 1;
		int isBST = 1;
		int isBalanced = 1;
		int prevVal;
		FILE *fp = fopen(argv[2], "rb");
		if(fp == NULL) {
			readStatus = -1;
		}
		if(readStatus == 1){
			constructTree(fp, &root, 0x03, &readStatus);
		}
		Node *min = minNode(root);
		prevVal = min->key;
		update_balance(root);
		binaryTreeCheck(root, &prevVal, &isBST, &isBalanced);
		printf("%d,%d,%d",readStatus, isBST, isBalanced);
//		preOrderPrint(root);
		free(fp);
		free_Tree(root);
	}
}

void binarytoText(char *filename) {
	//Processing file name to get size
	FILE *fp = fopen(filename, "rb");
	char *txtname = strcat(filename, ".txt");
	FILE *writeFile = fopen("ops.txt","w");
	int val;
	char ch;
	if (fp == NULL) {
		printf("reading file failed");
		return;
	}
	rewind(fp);
	while(!feof(fp)) {
		fread(&val, sizeof(int), 1, fp);
		fread(&ch, sizeof(char), 1, fp);
		fprintf(writeFile, "%d %c\n",val,ch);
	}
	fclose(fp);
	fclose(writeFile);
}