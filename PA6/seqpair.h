#ifndef SEQPAIR_H
#define SEQPAIR_H

#define W 0
#define B 1

typedef struct _Node {
    int label;
    int color;
    double width;
    double height;
    int dx;
    int dy;
    int hc;
    int vc;
    struct _Node **h_adj;
    struct _Node **v_adj;

} Node;

typedef struct _Graph {
    Node **v;
    int v_len;
} Graph;


typedef struct _Queue {
    Node **arr;
    int len;
} Stack;

Graph *load(char *fName);
void find_coords(Graph *g);
int save(Graph *g, char *fName);
void freeAll(Graph *g);
#endif