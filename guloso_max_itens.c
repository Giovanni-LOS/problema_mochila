#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct iten {
    int p;
    int v;
    int pos;
} iten;

void merge(iten *itens, int l, int m, int r);
void merge_sort(iten *itens, int l, int r);

int main(int argc, char *argv[])
{
    int n, w;
    scanf("%d %d", &n, &w);
    iten itens[n], sorted_itens[n];
    int ans[n], judge[n], weightSum = 0, judgeWeightSum = 0, valueSum = 0, judgeValueSum = 0;
    clock_t start, end;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &itens[i].v, &itens[i].p);
        itens[i].pos = i;
        sorted_itens[i] = itens[i];
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &judge[i]);
        ans[i] = 0;
    }

    start = clock();
    
    merge_sort(sorted_itens, 0, n - 1);

    for(int i = 0; i<n; i++) {
        if(weightSum + sorted_itens[i].p <= w) {
            valueSum += sorted_itens[i].v;
            weightSum += sorted_itens[i].p;
            ans[sorted_itens[i].pos] = 1;
        }
        if(judge[i]) {
            judgeValueSum += itens[i].v;
            judgeWeightSum += itens[i].p;
        }
    }
    
    double result = (double)valueSum / judgeValueSum;

    end = clock();
    
    double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%f %f\n", result, cpuTimeUsed);

    return EXIT_SUCCESS;
}

void merge(iten *itens, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    iten L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = itens[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = itens[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].p < R[j].p) {
            itens[k] = L[i];
            i++;
        } else {
            itens[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        itens[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        itens[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(iten *itens, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(itens, l, m);
        merge_sort(itens, m + 1, r);
        merge(itens, l, m, r);
    }
}
