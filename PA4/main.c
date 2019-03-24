#include <stdlib.h>
#include "tree.h"
#include <stdio.h>
#include <string.h>
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

int main(int argc, char *argv[]) {
	//binarytoText(argv[1]);
	Node *root = NULL;
	root = insert(root, 100);
    insert(root, 20);
	insert(root, 120);
	insert(root, 15);
	insert(root, 10);
//	//insert(root, 30);
//	insert(root, 5);
//	insert(root, 500);
//    insert(root, 10);
//    insert(root, 30);
//    insert(root, 40);
//	insert(root, 50);
    update_balance(root);
	inOrder(root);
	balance_inOrder(root);
    balance(&root);
  //  height(root);
  //  update_balance(root);


	insert(root, 130);
	inOrder(root);
	printf("\n\n");
	insert(root, 140);
	update_balance(root);
	delete(&root, 140);
	delete(&root, 120);
	balance(&root);
    inOrder(root);
    printf("\n\n");
	balance_inOrder(root);
//	depth_inOrder(root);
	//balance_inOrder(root);
	free_Tree(root);

    return EXIT_SUCCESS;
}

/*int List_Save_To_File(char *filename, Node *list) {
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
} */
