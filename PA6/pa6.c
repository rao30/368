#include <stdio.h>
#include <stdlib.h>>
#include "seqpair.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *fp1 = argv[1];
    char *fp2 = argv[2];

    Graph *rects = load(fp1);
    if (rects == NULL) {
        return EXIT_FAILURE;
    }
    find_coords(rects);
    int SaveCheck = save(rects, fp2);
    freeAll(rects);
    if(SaveCheck == EXIT_SUCCESS) {
        return EXIT_SUCCESS;
    }
    else return EXIT_FAILURE;
}