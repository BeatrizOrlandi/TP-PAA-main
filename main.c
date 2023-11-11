#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "gerador.h"
#include "prog_dinamica.h"
#include "Branch-and-Bound.h"
#include "backtracking.h"

// Estruturas e algoritmos definidos aqui

double getElapsedTime(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

int main() {
    int n_values[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
    int num_instances = 20;
    int *n;
    int *w;
    int W;
    int QTD = 9; //n_values -> diminua para teste
    double execution_times[3][QTD][20]; // 3 algoritmos, QTD tamanhos de instâncias

  
    for (int j = 0; j < (int)(sizeof(n_values) / sizeof(n_values[0])); j++) {
        struct timeval start, end;
        struct timeval start2, end2;
        struct timeval start3, end3;

        for (int i = 0; i < 20; i++) {  
            n = (int*) malloc(sizeof(int)*n_values[j]);
            w = (int*) malloc(sizeof(int)*n_values[0]);
            char *result = generateRandomInstance(j, n_values[j], 100);
            if (result == NULL) {
                printf("Falha ao gerar instância aleatória.\n");
                continue;  // Pule para a próxima iteração
            }

            printf("Arquivo gerado: %s\n", result);

            if (!readValuesFromFile(result, n, w, &W)) {
                printf("Falha ao ler valores do arquivo.\n");
                free(result);
                continue;  // Pule para a próxima iteração
            }

            gettimeofday(&start, NULL);
            prog_dinamica(result, n_values[j]);
            gettimeofday(&end, NULL);
            double elapsed_time = getElapsedTime(start, end);
            execution_times[0][j][i] = elapsed_time; // Algoritmo 1

            gettimeofday(&start2, NULL);
            //branch_and_bound(result, n_values[j]);
            gettimeofday(&end2, NULL);
            elapsed_time = getElapsedTime(start2, end2);
            execution_times[1][j][i] = elapsed_time; // Algoritmo 2


            gettimeofday(&start3, NULL);
            backtracking(result, n_values[j]);
            gettimeofday(&end3, NULL);
            elapsed_time = getElapsedTime(start2, end2);
            execution_times[2][j][i] = elapsed_time; // Algoritmo 3

            free(result);
            free(n);
            free(w);
        }
            
    }

    // Calcule as médias de tempo dividindo pelo número de instâncias
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < QTD; j++) {
            for (int k = 0; k < 20; k++)
                execution_times[i][j][k] /= num_instances;
        }
    }

    // Gere um arquivo de dados para o Gnuplot
    FILE *gnuplot_data = fopen("gnuplot_data.txt", "w");
    for (int j = 0; j < QTD; j++) {
        for (int k = 0; k < 20; k++)
            fprintf(gnuplot_data, "%d %f\n", n_values[j], execution_times[0][j][k]);
    }
    fclose(gnuplot_data);

    // Use o Gnuplot para criar um gráfico de barras
    FILE *gnuplot_script = popen("gnuplot -persist", "w");
    fprintf(gnuplot_script, "set terminal png\n");
    fprintf(gnuplot_script, "set output 'execution_times.png'\n");
    fprintf(gnuplot_script, "set title 'Tempo Médio de Execução'\n");
    fprintf(gnuplot_script, "set xlabel 'Tamanho da Instância'\n");
    fprintf(gnuplot_script, "set ylabel 'Tempo (s)'\n");
    fprintf(gnuplot_script, "set style data histograms\n");
    fprintf(gnuplot_script, "plot 'gnuplot_data.txt' using 2:xtic(1) title 'Algoritmo 1'\n");
    fclose(gnuplot_script);

    return 0;
}
