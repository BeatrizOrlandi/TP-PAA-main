#ifndef GERADOR_H
#define GERADOR_H

char* generateRandomInstance(int i,int n, int W);
int criarArquivos(int n_values, int W_values);
void readValuesFromFile(const char* filename, int *n_values, int *w_values, int *W);

#endif