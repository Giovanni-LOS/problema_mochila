#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct iten {
    int p;
    int v;
    int pos;
} iten;

int bpSolution(int n, int w, iten itens[], int **matrix);

int main(int argc, char *argv[])
{
    int n, w;
    scanf("%d %d", &n, &w);
    int** matrix = malloc(sizeof(int*)*(n+1));
    for(int i = 0; i<=n; i++) {
        matrix[i] = malloc(sizeof(int)*(w+1));
    }
    iten itens[n];
    int ans[n], judge[n], weightSum = 0, judgeWeightSum = 0, valueSum = 0, judgeValueSum = 0;
    clock_t start, end;
    double cpu_time_used;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &itens[i].v, &itens[i].p);
        itens[i].pos = i;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &judge[i]);
        ans[i] = 0;
    }
    
    for (int i = 0; i<=n; i++) {
        for (int j = 0; j<=w; j++) {
            matrix[i][j] = -1;
        }
    }

    for(int i = 0; i<n; i++) {
        if(judge[i]) {
            judgeValueSum += itens[i].v;
            judgeWeightSum += itens[i].p;
        }
    }

    start = clock();

    valueSum = bpSolution(n, w, itens, matrix);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    double result = (double) valueSum/judgeValueSum;

    int remWeight = w;  // Peso restante
    for (int i = n; i > 0; i--) {
        if (matrix[i][remWeight] != matrix[i-1][remWeight]) {
            ans[itens[i-1].pos] = 1;  // Marca o item como incluído
            remWeight -= itens[i-1].p;  // Subtrai o peso do item incluído
        }
    }

    printf("%f %f\n", result, cpu_time_used);

    for(int i = 0; i<=n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return EXIT_SUCCESS;
} 

int bpSolution(int n, int w, iten itens[], int **matrix) {
    if(n == 0 || w == 0) {
        matrix[n][w] = 0;
        return 0;
    }

    if(matrix[n][w] != -1) return matrix[n][w];

    if(itens[n-1].p > w) {
        matrix[n][w] = bpSolution(n-1, w, itens, matrix);
    } else {

        int no = bpSolution(n-1, w, itens, matrix);

        int yes = itens[n-1].v + bpSolution(n-1, w-itens[n-1].p, itens, matrix);

        matrix[n][w] = (no > yes) ? no : yes;
    }

    return matrix[n][w];
}
