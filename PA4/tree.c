
#include "tree.h"


Node *create_node(int k) {
    Node *new = malloc(sizeof(Node));
    new -> key = k;
    new -> balance = 0;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d \n", root->key);
        inOrder(root->right);
    }
}

int preOrder(Node *root, FILE *fp) {
    int status;
    int k;
    char ch;
    if (root != NULL) {
        status = preOrder(root->left, fp);
        if (status == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        else {
            k = root->key;
            int len = fwrite(&k, sizeof(int), 1, fp);
            if (len != 1) {
                printf("%d\n", 0);
                return EXIT_FAILURE;
            }
            ch = binaryPattern(root);
            len = fwrite(&ch, sizeof(char), 1, fp);
            if (len != 1) {
                printf("%d\n", 0);
                return EXIT_FAILURE;
            }
            status = preOrder(root->right, fp);
            if (status == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

char binaryPattern(Node *node) {
    if((node->left) == NULL && (node->right) == NULL) {
        return 0x00;
    }
    else if((node->left) == NULL){
        return 0x01;
    }
    else if((node->right) == NULL){
        return 0x02;
    }
    else {
        return 0x03;
    }
}

void balance_inOrder(Node *root)
{
    if (root != NULL)
    {
        balance_inOrder(root->left);
        printf("%d \n", root->balance);
        balance_inOrder(root->right);
    }
}

Node* insert(Node* node, int k)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return create_node(k);

    /* Otherwise, recur down the tree */
    if (k <= node->key)
        node->left  = insert(node->left, k);
    else if (k > node->key)
        node->right = insert(node->right, k);

    /* return the (unchanged) node pointer */
    return node;
}

void delete(Node** node, int k)
{
    Node *root = *node;
    /* If the tree is empty, return a new node */
    if ((*node) == NULL) return;

    /* Otherwise, recur down the tree */
    else if (k < (*node)->key)
        delete(&((*node)->left), k);
    else if (k > (*node)->key)
        delete(&((*node)->right), k);
    else if (k == (*node)->key){
        if((*node)->left == NULL && (*node)->right == NULL) {
            free(*node);
            *node = NULL;
            return;
        }
        else if((*node)->left == NULL) {
            Node *temp = *node;
            *node = ((*node)->right);
            free(temp);
            return;
        }
        else if((*node)->right == NULL) {
            Node *temp = *node;
            *node = ((*node)->left);
            free(temp);
            return;
        }
        else {
            Node *max = maxNode((*node)->left);
            int tempK = max->key;
            delete(&root, max->key);
            (*node)->key = tempK;
            return;
        }
    }

    /* return the (unchanged) node pointer */
}


void update_balance(Node *root) {
    height(root);
    if(root == NULL) {
        return;
    }
    int lh = 0;
    int rh = 0;
    if(root->left != NULL) {
        Node *left = root->left;
        lh = left->height;
    }
    if(root->right != NULL) {
        Node *right = root->right;
        rh = right->height;
    }
    update_balance(root->left);
    update_balance(root->right);
    root->balance = lh-rh;

}


int height(Node *root) {
    if(root == NULL) {
        return 0;
    }
    int lh = height(root->left) + 1;
    int rh = height(root->right) + 1;

    if(lh > rh) {
        root->height = lh;
        return lh;
    }
    else {
        root->height = rh;
        return rh;
    }
}

//Node *balance(Node* root,  Node **node) {
//    if ((node) == NULL) {
//        return NULL;
//    }
//    int k = (*node)->key;
//
//    if ((*node)->left != NULL) {
//        update_balance(root);
//        balance(root, (*node)->left);
//
//    }
//    if (node->right != NULL) {
//        update_balance(root);
//        balance(root, node->right);
//    }
//    int bal = node->balance;
//    if(requires_Bal(node)) {
//        if (getBalance(node) == 2) {
//            if (getBalance(node->left) == 1) {
//                if (node == root) {
//                    root = right_rotate(node);
//                    return root;
//                }
//                else {
//                    node = right_rotate(node);
//                    return node;
//                }
//            }
//            else if (getBalance(node->left) == -1) {
//                node->left = left_rotate(node->left);
//                if (node == root) {
//                    root = right_rotate(node);
//                    return root;
//                }
//                else {
//                    node = right_rotate(node);
//                    return node;
//                }
//            }
//        }
//    }
//    return node;
//}
void balance(Node **node) {
 //   Node **ptr = node;
    if((*node) == NULL) {
        return;
    }
    update_balance((*node));
    balance(&(*node)->left);
    update_balance((*node));
    balance(&(*node)->right);
    update_balance((*node));
    if (requires_Bal(*node)) {
        if (getBalance(*node) == 2) {
            if (getBalance((*node)->left) == 1 || getBalance((*node)->left) == 0) {
                right_rotate(node);
            } else if (getBalance((*node)->left) == -1) {
                left_rotate(&((*node)->left));
                right_rotate(node);
            }
        }
        else if (getBalance(*node) == -2) {
            if (getBalance((*node)->right) == -1 || getBalance((*node)->right) == 0) {
                left_rotate(node);
            } else if (getBalance((*node)->right) == 1) {
                right_rotate(&((*node)->right));
                left_rotate(node);
            }
        }
    }
}

int requires_Bal(Node *node) {
    if(getBalance(node) < 2 && getBalance(node) > -2) {
        return 0;
    }
    else {
        return 1;
    }
}

int getBalance(Node *node) {
    if(node == NULL) {
        return 0;
    }
    else {
        return node->balance;
    }
}
void left_rotate(Node **root) {
    Node *newroot = (*root)->right;
    Node *temp = newroot->left;
    newroot->left = (*root);
    (*root)->right = temp;
    (*root) = newroot;
}

void right_rotate(Node **root) {
    Node *newroot = (*root)->left;
    Node *temp = newroot->right;
    newroot->right = (*root);
    (*root)->left = temp;
    (*root) = newroot;
     int a = 1;
}

Node *maxNode(Node* node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

void free_Tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_Tree(root -> left);
    free_Tree(root -> right);
    free(root);
}