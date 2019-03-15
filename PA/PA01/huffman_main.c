#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if (argc != 6) {
		return EXIT_FAILURE;
	}
	FILE *fp = fopen(argv[1],"rb"); 
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	FILE *fpo1 = fopen(argv[2],"wb+");
	if (fpo1 == NULL) {
		return EXIT_FAILURE;
	}
	FILE *fpo2 = fopen(argv[3], "wb+");
	if (fpo2 == NULL) {
		return EXIT_FAILURE;
	}
	FILE *fpo3 = fopen(argv[4], "wb+");
	if (fpo3 == NULL) {
		return EXIT_FAILURE;
	}
	FILE *fpo4 = fopen(argv[5], "wb+");
	if (fpo4 == NULL) {
		return EXIT_FAILURE;
	}
	char *table[256] = {'\0'};
	char chars[256];
	long ctr = 0;
	long ctr1 = 0;
	long ctr2 = 0;
	long ctr3 = 0;
	rewind(fp);
	int ch;
	long array[256][2] = {{0}};
	for(int i = 0; i < 256; i++) {
		array[i][0] = i;
	}
	while(1) {
		ch = fgetc(fp);
		array[ch][1] = array[ch][1] + 1;
		if(feof(fp)) {
			break;
		}
		else {
		ctr3 = ctr3+1;
		}
	}
	rewind(fpo1);
	//Printing the .count files
	for(int i = 0; i < 256; i++) {
		fwrite(&array[i][1], sizeof(long), 1, fpo1);
	}
	fclose(fpo1);
	int head_pos = 256;
	int i = 0;
	while(i < 256) {
		if(array[i][1] != 0) {
			head_pos = i;
			break;
		}
		i++;
	}
	TreeNode *head = create_node(array[head_pos][0], array[head_pos][1]);
	//	print_queue(&head);

	if(head_pos < 255) {
		for(int j = head_pos+1; j <= 255; j++) {
			if(array[j][1] != 0) {
				head = make_list(&head, array[j][0],array[j][1]);
			}
		}
	}
	sort_list(&head);//pRINTIG file 2
	TreeNode *tree = make_tree(&head);

	traverse(tree, fpo3,"",chars,table, &ctr);
	traverse2(tree,fpo2);
	rewind(fpo4);
	printdoubles(fpo4, ctr1, ctr2, ctr3);
	printTree(fpo2,fpo4,&ctr2);
	printCompress(fp,fpo4,table,chars,&ctr1,ctr3);
	rewind(fpo4);
	printdoubles(fpo4, ctr1,ctr2,ctr3);
	fclose(fpo2);
	fclose(fpo3);
	fclose(fpo4);
	free_Tree(head);


	return EXIT_SUCCESS;
}
