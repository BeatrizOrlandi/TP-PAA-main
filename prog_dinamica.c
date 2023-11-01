#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prog_dinamica.h"

struct Item {
    int value;
    int weight;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsackDP(int W, struct Item items[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    int selected[n];
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    int result = dp[n][W];
    int w = W;
    
    for (int i = n; i > 0 && result > 0; i--) {
        if (result != dp[i - 1][w]) {
            selected[i - 1] = 1;
            result -= items[i - 1].value;
            w -= items[i - 1].weight;
        } else {
            selected[i - 1] = 0;
        }
    }
    
    printf("Lucro Máximo: %d\nItens selecionados: ", dp[n][W]);
    for (int i = 0; i < n; i++) {
        if (selected[i])
            printf("%d ", i);
    }
    // Libere a memória alocada para dp
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

void prog_dinamica() {
    clock_t start = clock();
    int W, n;
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    fscanf(file, "%d", &W);
    fscanf(file, "%d", &n);
    
    struct Item items[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d", &items[i].weight, &items[i].value);
    }
    
    fclose(file);
    
    knapsackDP(W, items, n);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo de Execução: %f segundos\n", time_spent);
}
