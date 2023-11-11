#ifndef BACKTRACKING_H
#define BACKTRACKING_H

void knapsackBacktracking(int W, struct Item items[], int n, int selected[], int currentWeight, int currentValue, int index);
int backtracking(char* filename, int n);

#endif