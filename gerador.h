#ifndef GERADOR_H
#define GERADOR_H

char* generateRandomInstance(int i,int n, int W);
int criarArquivos(int n_values, int W_values);
int readValuesFromFile(char* filename, int *n_values, int *w_values, int *W);

#endif