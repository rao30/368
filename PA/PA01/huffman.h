#ifndef HUFFMAN_H
#define HUFFMAN_H 


typedef struct _TreeNode {
	int ch;
	long count;
	struct _TreeNode *left;
	struct _TreeNode *right;
	struct _TreeNode *front;
	struct _TreeNode *rear;
} TreeNode;


TreeNode *create_node(int c, long count);

TreeNode *merge(TreeNode *old1, TreeNode *old2);

void free_Tree(TreeNode *t);

TreeNode * make_list(TreeNode **head, int c, long count);

TreeNode * sort_list(TreeNode **head);

TreeNode * make_tree(TreeNode **head);

TreeNode * insert_tree(TreeNode **head, TreeNode *merged);

void  dequeue(TreeNode **head);

void end_queue(TreeNode *head, TreeNode * end);

void print_queue(TreeNode **head, FILE *fp);

void print_list(TreeNode **head, FILE *fp);

void print_tree(TreeNode *tn, FILE *fp);

void print(TreeNode **head);

void nlr(TreeNode *head);

int treeSum(TreeNode *node);

TreeNode *front(TreeNode *head);

void insert(TreeNode **head, TreeNode **merged);

void traverse(TreeNode *tn, FILE*fp, char *code, char chars[], char *list[], long *counter);

void traverse2(TreeNode *tn, FILE *fp);

void traverse3(TreeNode *tn, FILE *fp, int *shift, int*ch);

//FUNCTIONS TO CREATE COMPRESSED FILE

void printdoubles(FILE *fp, long c1, long c2, long c3);

void printTree(FILE *fp1, FILE *fp2, long *c2);

void printCompress(FILE *input, FILE *output,char*list[], char chars[], long *c1, long counter);

void listArray(FILE*list, char*table[],int chars[]);
#endif
