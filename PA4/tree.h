#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int key;
	int balance;
	int depth;
	int height;
	char type;
	struct Node *left;
	struct Node *right;
	struct Node *next;
} Node;


Node* create_node(int k);

Node* insert(Node* node, int k);

void delete(Node** node, int k);

void inOrder(Node *root);

void depth_inOrder(Node *root);

void balance_inOrder(Node *root);

void depth(Node *root, int d);

int height(Node *root);

void update_balance(Node *root);

void balance(Node **node);

int getHeight(Node *Node);

int requires_Bal(Node *node);

int getBalance(Node *node);

void left_rotate(Node **root);

void right_rotate(Node **root);

void free_Tree(Node *root);

Node *maxNode(Node* node);

Node *minNode(Node* node);

//int preOrder(Node *root, FILE* fp);

int preOrder(Node *root, FILE *fp);

int preOrderPrint(Node *root);

char binaryPattern(Node *node);

void constructTree(FILE *fp, Node **root, char type, int *status);

void binaryTreeCheck(Node *root,int *prevVal, int *isBST, int *isBalanced);

Node *pop(Node **head);

Node *push(Node *head, Node *newNode);



#endif


	
