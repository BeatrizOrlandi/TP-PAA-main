#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

struct ItemB {
    int value;
    int weight;
    int index;
};

struct Node {
    int level;
    int value;
    int weight;
    double bound;
};

int compareItems(const void* a, const void* b);
double bound(struct Node u, int n, int W, struct ItemB arr[]);
void knapsackBranchAndBound(int W, struct ItemB arr[], int n);
int branch_and_bound(char* filename, int n);

#endif