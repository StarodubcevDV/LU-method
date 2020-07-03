#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>

int mp(double** a, double* b, double* c, int n, int m) { // Умножение матрицы на столбец/строку
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            c[i] = 0.0;
            for (k = 0; k < n; k++) {
                c[i] += a[i][k] * b[j];
            }
        }
    }
}
void invmatr(int n, double** a, double** b) {
    int i, j, k;
    double **tmp, *u, *v, nn, *B, *Y;

    tmp = (double**)malloc(n * sizeof(double*)); //Выделяем память.
    for (i = 0; i < n; i++)
        tmp[i] = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++) // Заполняем обратную матрицу нулями для корректного счёта
        for (j = 0; j < n; j++)
            b[i][j] = 0.0;

    for (k = 0; k < n; k++) {
        if (k == 0) {
            b[0][0] = 1.0 / a[0][0]; // Левый верхний элемент матрицы просто переварачиваем
        }
        else {
            u = (double*)malloc(k * sizeof(double));
            v = (double*)malloc(k * sizeof(double));
            for (i = 0; i <= k; i++)  // Выбираем столбец и строку
                for (j = 0; j <= k; j++) {
                    if ((i == k) && (j == k))
                        continue;
                    else if (j == k)
                        u[i] = a[i][j];
                    else if (i == k)
                        v[j] = a[i][j];
                }
            B = (double*)malloc(k * sizeof(double));
            Y = (double*)malloc(k * sizeof(double));
            mp(b, u, B, k, k); // Вычисляем столбец
            mp(b, v, Y, k, k); // Вычисляем строку
            nn = a[n - 1][n - 1]; // Вычисляем угловой элемент
            for (i = 0; i <= k; i++) {
                nn -= a[k][i] * B[i];
            }
            for (i = 0; i <= k; i++) { // Заполняем обратную матрицу
                for (j = 0; j <= k; j++) {
                    if ((i == k) && (j == k))
                        b[i][j] = 1 / nn;
                    else {
                        if ((i < k) && (j < k))
                            b[i][j] += (B[j] * Y[j]) / nn;
                        if (j == k)
                            b[i][j] = (-B[j] / nn);
                        if (i == k)
                            b[i][j] = (-Y[j] / nn);
                    }
                }
            }
            free(B);
            free(Y);
            free(u);
            free(v);
        }
    }
    for (i = 0; i < n; i++) //Очищаем память.
        free(tmp[i]);
    free(tmp);
}
  

int main() {
    double** a, **b;
    int i, j, nA;
    FILE* input, * output; //Инициализируем файлы.

    input = fopen("input.txt", "r"); //Открываем файлы.
    output = fopen("output.txt", "w");

    printf("Enter range of matrix A:"); //Определяем размерность матриц.
    scanf("%d", &nA);

    a = (double**)malloc(nA * sizeof(double*)); //Выделяем память.
    for (i = 0; i < nA; i++)
        a[i] = (double*)malloc(nA * sizeof(double));
    b = (double**)malloc(nA * sizeof(double*)); //Выделяем память.
    for (i = 0; i < nA; i++)
        b[i] = (double*)malloc(nA * sizeof(double));

    for (i = 0; i < nA; i++) //Считываем матрицу.
        for (j = 0; j < nA; j++)
            fscanf(input, "%lf", &a[i][j]);

    invmatr(nA, a, b);

    for (i = 0; i < nA; i++) {
        printf("\n");
        for (j = 0; j < nA; j++)
            printf("%lf ", b[i][j]);
    }

    /*if (Твоя функция) {                          //Вызываем функцию.
            Выводишь результат
    }
    else {
        Выводишь сообщение об ошибке
    }*/

    fclose(input); //Закрываем файлы.
    fclose(output);

    for (i = 0; i < nA; i++) //Очищаем память.
        free(a[i]);
    free(a);
    return 0;
}