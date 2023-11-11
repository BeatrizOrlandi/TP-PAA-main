#include "Branch-and-Bound.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compareItems(const void *a, const void *b) {
    double ratioA = (double)(((struct ItemB *)b)->value) / (((struct ItemB *)b)->weight);
    double ratioB = (double)(((struct ItemB *)a)->value) / (((struct ItemB *)a)->weight);
    if (ratioA > ratioB)
        return 1;
    if (ratioA < ratioB)
        return -1;
    return 0;
}

double bound(struct Node u, int n, int W, struct ItemB arr[]) {
    if (u.weight >= W)
        return 0;

    double profitBound = u.value;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while ((j < n) && (totalWeight + arr[j].weight <= W)) {
        totalWeight += arr[j].weight;
        profitBound += arr[j].value;
        j++;
    }

    if (j < n)
        profitBound += (W - totalWeight) * (double)arr[j].value / arr[j].weight;

    return profitBound;
}

void knapsackBranchAndBound(int W, struct ItemB arr[], int n) {
    qsort(arr, n, sizeof(struct ItemB), compareItems);

    struct Node u, v;
    u.level = -1;
    u.value = u.weight = 0;
    u.bound = bound(u, n, W, arr);

    struct Node *priorityQueue = (struct Node *)malloc(sizeof(struct Node) * (n + 1));
    int front = -1, rear = -1;
    int maxProfit = 0;

    while (1) {
        if (u.level == n - 1)
            break;

        if (u.level == -1)
            v.level = 0;

        v.level = u.level + 1;
        v.weight = u.weight + arr[v.level].weight;
        v.value = u.value + arr[v.level].value;

        if (v.weight <= W && v.value > maxProfit)
            maxProfit = v.value;

        v.bound = bound(v, n, W, arr);

        if (v.bound > maxProfit) {
            rear++;
            priorityQueue[rear] = v;
        }

        v.weight = u.weight;
        v.value = u.value;
        v.bound = bound(v, n, W, arr);

        if (v.bound > maxProfit) {
            rear++;
            priorityQueue[rear] = v;
        }

        front++;
        u = priorityQueue[front];
    }

    printf("Lucro Maximo: %d\nItens selecionados: ", maxProfit);
    for (int i = 0; i < n; i++) {
        if (arr[i].index)
            printf("%d ", i);
    }

    free(priorityQueue);
}

int branch_and_bound(char* filename, int n) {
    int W;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (fscanf(file, "%d", &W) != 1) {
        printf("Erro ao ler o valor de W do arquivo.\n");
        fclose(file);
        return 1;
    }

    struct ItemB *items = malloc(sizeof(struct ItemB) * n);
    if (items == NULL) {
        printf("Erro ao alocar memória para os itens.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d %d", &items[i].weight, &items[i].value) != 2) {
            printf("Erro ao ler os itens do arquivo.\n");
            free(items);
            fclose(file);
            return 1;
        }
        items[i].index = 0;
    }

    fclose(file);

    knapsackBranchAndBound(W, items, n);

    free(items);

    return 0;
}
