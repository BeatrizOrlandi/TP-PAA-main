#ifndef PROG_DINAMICA_H
#define PROG_DINAMICA_H

struct Item {
    int value;
    int weight;
};

int max(int a, int b);
void knapsackDP(int W, struct Item items[], int n);
void prog_dinamica(char* filename, int n);

#endif