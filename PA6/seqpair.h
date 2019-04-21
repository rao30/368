#ifndef SEQPAIR_H
#define SEQPAIR_H

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct _Node {
    int label;
    int color;
    double width;
    double height;
    int dx;
    int dy;
    struct _Node **h_adj;
    struct _Node **v_adj;
    int hadj_cnt, vadj_cnt;
} Node;

typedef struct _Graph {
    Node **v;
    int v_len;
} Graph;


typedef struct _Queue {
    Node **arr;
    int len;
} Stack;

Graph *load(char *fname);
void find_coords(Graph *g);
void save(Graph *g, char *fname);
void free_graph(Graph *g);

#endif