#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#define ROWS 3

#define COLS 3

int matrix1[ROWS][COLS];

int matrix2[ROWS][COLS];

int sum[ROWS][COLS];

int sub[ROWS][COLS];

int mul[ROWS][COLS];

void *addition(void *arg)

{

    int i, j;

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    pthread_exit(NULL);
}

void *subtraction(void *arg)

{

    int i, j;

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            sub[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    pthread_exit(NULL);
}

void *multiplication(void *arg)

{

    int i, j, k;

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            mul[i][j] = 0;

            for (k = 0; k < COLS; k++)
            {

                mul[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

void *AB_BA(void *arg)

{
    printf("This is Equality check\n");

    int i, j, flag = 1;

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            if (matrix1[i][j] != matrix2[j][i])
            {

                flag = 0;

                break;
            }
        }
    }

    if (flag)
    {

        printf("AB = BA\n");
    }
    else
    {

        printf("AB != BA\n");
    }

    pthread_exit(NULL);
}
void *trace1(void *arg)

{

    int i, trace = 0;

    for (i = 0; i < ROWS; i++)
    {

        trace += matrix1[i][i];
    }

    printf("Trace of matrix 1 is: %d\n", trace);

    pthread_exit(NULL);
}
void *trace2(void *arg)

{

    int i, trace = 0;

    for (i = 0; i < ROWS; i++)
    {

        trace += matrix2[i][i];
    }

    printf("Trace of matrix 2 is: %d\n", trace);

    pthread_exit(NULL);
}
int main()

{

    int i, j;

    pthread_t threads[5];

    // Initialize matrices

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            matrix1[i][j] = i+j;

            matrix2[i][j] = i*j;
        }
    }

    // Create threads for matrix operations

    pthread_create(&threads[0], NULL, addition, NULL);

    pthread_create(&threads[1], NULL, subtraction, NULL);

    pthread_create(&threads[2], NULL, multiplication, NULL);

    pthread_create(&threads[3], NULL, trace1, NULL);

    pthread_create(&threads[4], NULL, trace2, NULL);

    pthread_create(&threads[5], NULL, AB_BA, NULL);

    // WAITING STAGE for threads to finish

    for (i = 0; i < 5; i++)
    {

        pthread_join(threads[i], NULL);
    }

    // Print results of matrix operations

    printf("Addition:\n");

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            printf("%d", sum[i][j]);
        }

        printf("\n");
    }

    printf("Subtraction:\n");

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            printf("%d", sub[i][j]);
        }

        printf("\n");
    }

    printf("Multiplication:\n");

    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {

            printf("%d", mul[i][j]);
        }

        printf("\n");
    }

    trace1(&matrix1);
    trace2(&matrix2);

    AB_BA(&matrix1);

    return 0;
}