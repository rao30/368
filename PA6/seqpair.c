#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "seqpair.h"

int *indexing(int *a, int rNumber) {
    int *table = malloc(sizeof(*table) * (rNumber+1));
    for (int i = 0; i < rNumber; i++) {
        table[a[i]] = i;
    }
    return table;
}

void connect(Graph *g, int *sequence1, int *sequence2) {
    Node **v = g->v;
    int rNumber = g->v_len;

    int *table1 = indexing(sequence1, rNumber-1);
    int *table2 = indexing(sequence2, rNumber-1);
    for (int i = 1; i < rNumber; i++) {
        int idx1 = table1[v[i]->label];
        int idx2 = table2[v[i]->label];

        for (int j = idx2+1, k = 0; j < rNumber - 1; j++, k++) {
            if (table1[sequence2[j]] > idx1) {
                int cnt = ++(v[i]->hadj_cnt);
                v[i]->h_adj = realloc(v[i]->h_adj, cnt*sizeof(*(v[i]->h_adj)));
                v[i]->h_adj[cnt-1] = v[sequence2[j]];
            }
            if (table1[sequence2[j]] < idx1) {
                //above
                int cnt = ++(v[i]->vadj_cnt);
                v[i]->v_adj = realloc(v[i]->v_adj, cnt*sizeof(*(v[i]->v_adj)));
                v[i]->v_adj[cnt-1] = v[sequence2[j]];
            }
        }
    }
    free(table1);
    free(table2);
}

Graph *load(char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        return NULL;
    }

    int cnt;
    fscanf(fp, "%d", &cnt);
    int rNumber = cnt + 1;
    Node **v = calloc(1, sizeof(*v) * rNumber);
    int sequence1[rNumber];
    int sequence2[rNumber];
    v[0] = calloc(1, sizeof(*(v[0])));
    v[0]->dx = v[0]->dy = 0;
    v[0]->hadj_cnt = v[0]->vadj_cnt = cnt;
    v[0]->h_adj = calloc(1, sizeof(*(v[0]->h_adj)) * cnt);
    v[0]->v_adj = calloc(1, sizeof(*(v[0]->v_adj)) * cnt);

    for (int i = 1; i < cnt+1; i++) {
        double width, height;
        int label;
        fscanf(fp, "%d(%le,%le)", &label, &width, &height);
        v[i] = calloc(1, sizeof(*(v[0])));
        v[i]->width = width;
        v[i]->height = height;
        v[i]->label = label;
        v[i]->dx = v[i]->dy = 0;
        v[0]->h_adj[i-1] = v[i];
        v[0]->v_adj[i-1] = v[i];
    }
    for (int i = 0; i < cnt; i++) {
        fscanf(fp, "%d", &sequence1[i]);
    }
    for (int i = 0; i < cnt; i++) {
        fscanf(fp, "%d", &sequence2[i]);
    }
    Graph *g = calloc(1, sizeof(*g));
    g->v = v;
    g->v_len = rNumber;
    connect(g, sequence1, sequence2);

    fclose(fp);
    return g;
}

Stack *init_stack() {
    Stack *s = calloc(1,sizeof(*s));
    return s;
}

void push(Stack *s, Node *v) {
    s->len++;
    s->arr = realloc(s->arr, sizeof(*(s->arr)) * s->len);
    for (int i = s->len - 1; i > 0; i--) {
        s->arr[i] = s->arr[i-1];
    }
    s->arr[0] = v;
}

Node *_pop(Stack *s) {
    if (s->len < 1) {
        return NULL;
    }
    Node *v = s->arr[0];
    s->len--;
    for (int i = 0; i < s->len; i++) {
        s->arr[i] = s->arr[i+1];
    }
    s->arr = realloc(s->arr, sizeof(*(s->arr)) * s->len);
    return v;
}

int empty(Stack *s) {
    return (s->len == 0);
}

void toposort(Node *v, Stack *s, int h) {
    v->color = BLACK;

    for (int i = 0; i < ((h) ? v->hadj_cnt : v->vadj_cnt); i++) {
        Node *u = (h) ? v->h_adj[i] : v->v_adj[i];
        if (u->color == WHITE) {
            toposort(u, s, h);
        }
    }
    push(s, v);
}

void find_coords(Graph *g) {
    Stack *sh = init_stack();
    Stack *sv = init_stack();
    Node **v = g->v;
    for (int i = 0; i < g->v_len; i++) {
        if (v[i]->color == WHITE) {
            toposort(v[i], sh, 1);
        }
        if (i != 0) {
            v[i]->dx = v[i]->dy = -INT_MAX;
        }
    }
    for (int i = 0; i < g->v_len; i++) {
        v[i]->color = WHITE;
    }
    for (int i = 0; i < g->v_len; i++) {
        if (v[i]->color == WHITE) {
            toposort(v[i], sv, 0);
        }
    }

    while (!empty(sh)) {
        Node *u = _pop(sh);
        for (int i = 0; i < u->hadj_cnt; i++) {
            Node *x = u->h_adj[i];
            if (x->dx <= u->dx + u->width) {
                x->dx = u->dx + u->width;
            }
        }
    }
    while (!empty(sv)) {
        Node *u = _pop(sv);
        for (int i = 0; i < u->vadj_cnt; i++) {
            Node *x = u->v_adj[i];
            if (x->dy <= u->dy + u->height) {
                x->dy = u->dy + u->height;
            }
        }
    }
    free(sv);
    free(sh);
}

void save(Graph *g, char *fname) {
    FILE *f = fopen(fname, "w");
    if (!f) {
        return;
    }

    Node **v = g->v;
    int rNumber = g->v_len;
    for (int i = 1; i < rNumber; i++) {
        fprintf(f, "%d(%.6le,%.6le)\n", v[i]->label, (double)v[i]->dx, (double)v[i]->dy);
    }
    fclose(f);
}

void free_graph(Graph *g) {
    for (int i = 0; i < g->v_len; i++) {
        free(g->v[i]->v_adj);
        free(g->v[i]->h_adj);
        free(g->v[i]);
    }
    free(g->v);
    free(g);
}