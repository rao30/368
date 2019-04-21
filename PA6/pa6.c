#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seqpair.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *fp1 = argv[1];
    char *fp2 = argv[2];

    Graph *g = load(fp1);
    if (!g) {
        return EXIT_FAILURE;
    }
    find_coords(g);
    save(g, fp2);
    free_graph(g);

    return EXIT_SUCCESS;
}