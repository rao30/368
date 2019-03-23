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
	binarytoText(argv[1]);
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
