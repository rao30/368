#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if (argc != 5) {
		return EXIT_FAILURE;
	}
	FILE *fp = fopen(argv[1],"r"); 
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	FILE *fpo1 = fopen(argv[2],"w");
	FILE *fpo2 = fopen(argv[3], "w");
	FILE *fpo3 = fopen(argv[4], "w");
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
	}
	fclose(fp);
//	for(int i = 0; i < 256; i++) {
//		fprintf(fpo3,"%ld\n", array[i][1]);   ///PRINTING FILE 1
//	}
//	fclose(fpo3);
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

	if(head_pos + 1 < 256) {
		for(int j = head_pos+1; j < 256; j++) {
			if(array[j][1] != 0) {
				head = make_list(&head, array[j][0],array[j][1]);
			}
		}
	}
	//	print(&head);
	//	printf("\n\n\n");
	sort_list(&head);//pRINTIG file 2
	TreeNode *tree = make_tree(&head);
	
	//	print(&head);
	traverse(tree, fpo1,"");
	traverse2(tree,fpo2);
	fprintf(fpo2,"0");
	int shift;
	int chf= 0x00;
	traverse3(tree,fpo3,&shift,&chf);
	if(shift != 0) {
		fprintf(fpo3,"%c",chf);
	}
	fclose(fpo1);
	fclose(fpo2);
	fclose(fpo3);
	//	print_queue(&head);
	//	head = dequeue_two(&head);
	//	printf("\n");
	//	TreeNode *tree = make_tree(&head);
		print(tree);
	//	free(tree);
	//	free(tree);


	return EXIT_SUCCESS;
}