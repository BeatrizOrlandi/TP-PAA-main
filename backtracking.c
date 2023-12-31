#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prog_dinamica.h"
#include "backtracking.h"

void knapsackBacktracking(int W, struct Item items[], int n, int selected[], int currentWeight, int currentValue, int index) {
    if (index == n || currentWeight == W) {
        if (currentValue > selected[n]) {
            selected[n] = currentValue;
        }
        return;
    }
    
    if (currentWeight + items[index].weight <= W) {
        selected[index] = 1;
        knapsackBacktracking(W, items, n, selected, currentWeight + items[index].weight, currentValue + items[index].value, index + 1);
    }
    
    selected[index] = 0;
    knapsackBacktracking(W, items, n, selected, currentWeight, currentValue, index + 1);
}

int backtracking(char* filename, int n) {

    int W;
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    fscanf(file, "%d", &W);
    
    struct Item items[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d", &items[i].weight, &items[i].value);
    }
    
    fclose(file);
    
    int selected[n];
    for (int i = 0; i < n; i++) {
        selected[i] = 0;
    }
    
    knapsackBacktracking(W, items, n, selected, 0, 0, 0);
    
    printf("Lucro Maximo: %d\nItens selecionados: ", selected[n]);
    for (int i = 0; i < n; i++) {
        if (selected[i])
            printf("%d ", i);
    }
    
    return 0;
}
