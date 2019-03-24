//
// Created by Richie on 2/28/2019.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
TreeNode *create_node(double lw, double rw, TreeNode *left, TreeNode *right) {
    TreeNode *new = malloc(sizeof(TreeNode));
    new -> c = 0;
    new -> t = 0;
    new -> ctot = 0;
    new -> rpath = 0;
    new -> label = -1;
    new ->lw = lw;
    new ->rw = rw;
    new -> left = left;
    new -> right = right;
    return new;
}

TreeNode *create_leaf(int label, double capacitance) {
    TreeNode *new = malloc(sizeof(TreeNode));
    new -> label = label;
    new -> ctot = 0;
    new -> rpath = 0;
    new -> lw = 0;
    new -> rw = 0;
    new -> t = 0;
    new -> c = capacitance;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

TreeNode *push(TreeNode *head, TreeNode *newNode) {
    if (head != NULL) {
        newNode->next = head;
        head = newNode;
    }
    else {
        head = newNode;
        head->next = NULL;
        }
    return head;
}

TreeNode *pop(TreeNode **head) {
    if (*head != NULL) {
    TreeNode *popped = *head;
        *head = (*head)->next;
    return popped;
    }
    return NULL;
}

void prePrint(TreeNode *tn, FILE *fp) {
    if (tn == NULL) {
        return;
    }
    if (tn->label != -1) {
    fprintf(fp, "%d(%le)\n", tn->label,tn->c);
    }
    else {
        fprintf(fp, "(%le %le)\n", tn->lw, tn->rw);
    }
    prePrint(tn->left, fp);
    prePrint(tn->right, fp);

}

void delayPrint(TreeNode *tn, FILE *fp) {
    if (tn == NULL) {
        return;
    }
    if(tn->label != -1) {
    fprintf(fp,"%d(%le)\n",tn->label, tn->t);
    }
    delayPrint(tn->left, fp);
    delayPrint(tn->right, fp);

}

void delayPrintB(TreeNode *tn, FILE *fp) {
    if (tn == NULL) {
        return;
    }
    if(tn->label != -1) {
        fwrite(&tn->label, sizeof(int), 1, fp);
        fwrite(&tn->t, sizeof(double), 1, fp);
    }
    delayPrintB(tn->left, fp);
    delayPrintB(tn->right, fp);

}

void caprCalc(TreeNode *tn, double cap, double c, double rpath, double r) {
    if (tn == NULL) {
        return;
    }
    tn->rpath = tn->rpath + rpath;
    double leftCap = (c * tn->lw)/2;
    double rightCap = (c * tn->rw)/2;
    double leftr = (r * tn->lw) + tn->rpath;
    double rightr = (r * tn->rw) + tn->rpath;
    tn -> c = (tn -> c) + cap + leftCap + rightCap;
  //  printf("label = %d\n",tn->label);
    caprCalc(tn->left, leftCap, c,leftr, r);
    caprCalc(tn->right, rightCap, c, rightr, r);
    if (tn ->left != NULL && tn->right != NULL) {
        tn->ctot = (tn->left->ctot + tn->left->c) + (tn->right->ctot + tn->right->c);
    }
//    else {
//        tn -> ctot = tn -> c;
//    }

}

void timeCalc(TreeNode *tn, double prevr, double prevrc) {
    if(tn == NULL) {
        return;
    }
    double currR = tn->rpath;
    double currC = tn -> ctot + tn->c;
    double currrc = prevrc - currC*pow(prevr,2);
    currrc = currrc + currC*pow(currR, 2);
    tn->t = (currrc)/currR;
    timeCalc(tn->left, currR, currrc);
    timeCalc(tn->right, currR, currrc);


}
TreeNode *postTree(FILE *fp) {
    int label;
    double nodeC;
    double lw;
    double rw;
    TreeNode *head = NULL;
    TreeNode *right = NULL;
    TreeNode *left = NULL;
    char str[200];
    int match;
    while(1) {
        fgets(str, 200, fp);
        if( feof(fp)) {
            break;
        }
        match = sscanf(str, "%d(%le)\n", &label, &nodeC);
        if (match == 2) {
            TreeNode *leaf = create_leaf(label, nodeC);
            head = push(head, leaf);
        } else {
            match = sscanf(str, "(%le %le)\n", &lw, &rw);
            right = pop(&head);
            left = pop(&head);
            head = push(head, create_node(lw, rw, left, right));

        }
    }
  //  prePrint(head);
    return head;
}

void free_Tree(TreeNode *tn) {
    if (tn == NULL) {
        return;
    }
    free_Tree(tn -> left);
    free_Tree(tn -> right);
    free(tn);
}
