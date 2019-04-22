#include <stdio.h>
#include <stdlib.h>
#include "seqpair.h"

int *indexing(int *x, int rNumber) {
    int *list = malloc(sizeof(int) * (rNumber+1));
    for (int i = 0; i < rNumber; i++) {
        list[x[i]] = i;
    }
    return list;
}

void join(Graph *g, int *sequence1, int *sequence2) {
    Node **head = g->v;
    int rNumber = g->v_len;

    int *table1 = indexing(sequence1, rNumber-1);
    int *table2 = indexing(sequence2, rNumber-1);
    for (int i = 1; i < rNumber; i++) {
        int idx1 = table1[head[i]->label];
        int idx2 = table2[head[i]->label];

        for (int j = idx2+1, k = 0; j < rNumber - 1; j++, k++) {
            if (table1[sequence2[j]] > idx1) {
                int cnt = ++(head[i]->hc);
                head[i]->h_adj = realloc(head[i]->h_adj, cnt*sizeof(Node));
                head[i]->h_adj[cnt-1] = head[sequence2[j]];
            }
            if (table1[sequence2[j]] < idx1) {
                //above
                int cnt = ++(head[i]->vc);
                head[i]->v_adj = realloc(head[i]->v_adj, cnt*sizeof(Node));
                head[i]->v_adj[cnt-1] = head[sequence2[j]];
            }
        }
    }
    free(table1);
    free(table2);
}

void push(Stack *s, Node *head) {
    int newLength = s->len + 1;
    s->len = newLength;
    s->arr = realloc(s->arr, sizeof(Node) * newLength);
    for (int i = newLength-1; i > 0; i--) {
        s->arr[i] = s->arr[i-1];
    }
    s->arr[0] = head;
}

Node *pop(Stack *s) {
    int newLength = s->len -1;
    if (newLength < 0) {
        return NULL;
    }
    Node *head = s->arr[0];
    s->len = newLength;
    for (int i = 0; i < newLength; i++) {
        s->arr[i] = s->arr[i+1];
    }
    s->arr = realloc(s->arr, sizeof(Node) * newLength);
    return head;
}

Graph *load(char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        return NULL;
    }

    int cnt;
    fscanf(fp, "%d", &cnt);
    int rNumber = cnt + 1;
    Node **head = calloc(1, sizeof(Node) * rNumber);
    int sequence1[rNumber];
    int sequence2[rNumber];
    head[0] = calloc(1, sizeof(Node));
    head[0]->dx = head[0]->dy = 0;
    head[0]->hc = head[0]->vc = cnt;
    head[0]->h_adj = calloc(1, sizeof(Node) * cnt);
    head[0]->v_adj = calloc(1, sizeof(Node) * cnt);

    for (int i = 1; i < cnt+1; i++) {
        double width, height;
        int label;
        fscanf(fp, "%d(%le,%le)", &label, &width, &height);
        head[i] = calloc(1, sizeof(Node));
        head[i]->width = width;
        head[i]->height = height;
        head[i]->label = label;
        head[i]->dx = head[i]->dy = 0;
        head[0]->h_adj[i-1] = head[i];
        head[0]->v_adj[i-1] = head[i];
    }
    for (int i = 0; i < cnt; i++) {
        fscanf(fp, "%d", &sequence1[i]);
    }
    for (int i = 0; i < cnt; i++) {
        fscanf(fp, "%d", &sequence2[i]);
    }
    Graph *g = calloc(1, sizeof(Graph));
    g->v = head;
    g->v_len = rNumber;
    join(g, sequence1, sequence2);

    fclose(fp);
    return g;
}


//
//void toposort(Node *head, Stack *s, int axis) {
//    head->color = B;
//    int i = 0;
//    if(axis) {
//        while(1) {
//            if(i >= head->hc) {
//                break;
//            }
//            Node *haj = head->h_adj[i];
//            if (haj->color == W) {
//            toposort(haj, s, axis);
//        }
//            i++;
//
//        }
//    }
//    else {
//        while(1) {
//            if(i >= head->vc) {
//                break;
//            }
//            Node *vaj = head->v_adj[i];
//            if (vaj->color == W) {
//                toposort(vaj, s, axis);
//            }
//            i++;
//
//        }
//    }
////    for (int i = 0; i < ((h) ? head->hc : head->vc); i++) {
////        Node *u = (h) ? head->h_adj[i] : head->v_adj[i];
////        if (popped->color == W) {
////            toposort(u, s, h);
////        }
////    }
//
//    push(s, head);
//}

void tsortx(Node *head, Stack *s) {
    head->color = B;
    int i = 0;
    while(1) {
        if(i >= head->hc) {
            break;
        }
        Node *haj = head->h_adj[i];
        if (haj->color == W) {
            tsortx(haj, s);
        }
        i++;

    }
    push(s, head);
}


void tsorty(Node *head, Stack *s) {
    head->color = B;
    int i = 0;
    while(1) {
        if(i >= head->vc) {
            break;
        }
        Node *vaj = head->v_adj[i];
        if (vaj->color == W) {
            tsorty(vaj, s);
        }
        i++;

    }
    push(s, head);
}


void find_coords(Graph *g) {
    Node **head = g->v;
    Stack *v = calloc(1,sizeof(Stack));
    Stack *h = calloc(1,sizeof(Stack));

    for (int i = 0; i < g->v_len; i++) {
        if (head[i]->color == W) {
            tsortx(head[i], h);
        }
        if (i != 0) {
            head[i]->dx = head[i]->dy = -1;
        }
    }
    for (int i = 0; i < g->v_len; i++) {
        head[i]->color = W;
    }
    for (int i = 0; i < g->v_len; i++) {
        if (head[i]->color == W) {
            tsorty(head[i], v);
        }
    }
    while (v->len != 0) {
        Node *popped = pop(v);
        for (int i = 0; i < popped->vc; i++) {
            double cheight = popped->dy + popped->height;
            Node *y = popped->v_adj[i];
            if (y->dy <= cheight) {
                y->dy = cheight;
            }
        }
    }
    while (h->len != 0) {
        Node *popped = pop(h);
        for (int i = 0; i < popped->hc; i++) {
            double cwidth =popped->dx + popped->width;
            Node *x = popped->h_adj[i];
            if (x->dx <= cwidth) {
                x->dx = cwidth;
            }
        }
    }
    free(v);
    free(h);
}

int save(Graph *graph, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        EXIT_FAILURE;
    }

    Node **rectList = graph->v;
    int rNumber = graph->v_len;
    for (int i = 1; i < rNumber; i++) {
        fprintf(fp, "%d(%.6le,%.6le)\n", rectList[i]->label, (double)rectList[i]->dx, (double)rectList[i]->dy);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

void freeAll(Graph *g) {
    for (int i = 0; i < g->v_len; i++) {
        free(g->v[i]->v_adj);
        free(g->v[i]->h_adj);
        free(g->v[i]);
    }
    free(g->v);
    free(g);
}