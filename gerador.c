
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gerador.h"

char* generateRandomInstance(int i,int n, int W) {
    char arq[12] = "input";
    char c = i +'0';
    strcat(arq, c);
    strcat(arq, ".txt");
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de entrada.\n");
        return;
    }

    srand(time(NULL));

    fprintf(file, "%d\n", W);
    for (int i = 0; i < n; i++) {
        int weight, value;

            weight = 1 + (rand() % 30);
            value = 1 + (rand() % 100);

        fprintf(file, "%d %d\n", weight, value);
    }
        
    fclose(file);
    return arq;
}
void readValuesFromFile(const char* filename, int *n_values, int *w_values, int *W) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return NULL;
    }

    fscanf(file, "%d", *W); // Lê o valor de W
    int size = 0;

    while (fscanf(file, "%d %d", n_values[size], w_values[size]) == 2) {
        size++;
    }

    fclose(file);  
}

