#ifndef TREE_H
#define TREE_H
typedef struct Node {
	int key;
	int balance;
	int depth;
	int height;
	struct Node *left;
	struct Node *right;
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

#endif


	
