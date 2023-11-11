#include "gerador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char* generateRandomInstance(int i, int n, int W) {
    char arq[12] = "input";
    char c[2];
    c[0] = (i + '0');
    c[1] = '\0';
    strcat(arq, c);
    strcat(arq, ".txt");

    printf("arquivo %d quantidade %d\n", i,n);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de entrada.\n");
        return NULL;
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

    char *result = malloc(strlen(arq) + 1);
    if (result == NULL) {
        printf("Erro ao alocar memória para o resultado.\n");
        return NULL;
    }

    strcpy(result, arq);
    return result;
}

int readValuesFromFile(char* filename, int *n_values, int *w_values, int *W) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return 0;
    }

    if (fscanf(file, "%d", W) != 1) {
        printf("Falha ao ler W do arquivo.\n");
        fclose(file);
        return 0;
    }

    int size = 0;
    while (size < n_values[0] && fscanf(file, "%d %d", &n_values[size], &w_values[size]) == 2) {
        size++;
    }

    fclose(file);
    return 1;
}