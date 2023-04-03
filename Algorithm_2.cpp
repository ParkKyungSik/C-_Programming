#include <stdio.h>
#include <malloc.h>

int minmult(int n, int d[], int *P[]);  // 최소 곱셈 알고리즘
void order(int i, int j, int *P[]);     // 최적 순서 출력
int* input_array_number(int n);     // dx를 입력 받음
int** make_array(int n);    // P 행렬 동적 할당

int main()
{
    int *d, **P;
    int number, result;

    printf("Minimum Multiplication\nhow many numbers of array? ");
    scanf("%d", &number);  // 형렬의 갯수 입력 받음

    d = input_array_number(number); // 알고리즘의 입력이 되는 d 행렬
    P = make_array(number);     // 최적 순서 출력을 위한 P 행렬 만듬

    result = minmult(number, d, P); // 알고리즘의 결과값을 result에 저장
    printf("\nArray Multiplication Order is ");
    order(1, number, P);   // 행렬 곱셈 최적 순서 출력
    printf("\nMinimum Multiplication is %d\n", result);

    return 0;
}

int** make_array(int n) // P 행렬을 동적 메모리 할당으로 만듬
{
    int i;
    int **P = (int**)malloc(0);
    for (i = 0; i < n; i++)
        P[i] = (int*)malloc(sizeof(int)*n);
    return P;
}

int* input_array_number(int n)  // 입력 받은 number 만큼 dx를 입력 받음
{
    int i, *d;
    printf("Plz Input d0 ~ d%d\n", n);
    d = (int*)malloc(sizeof(int)*n);
    for(i = 0; i <= n; i++) {
        printf("d%d=? ", i);
        scanf("%d", &d[i]);
    }
    return d;
}

void order(int i, int j, int *P[])  // 최적의 순서 출력
{
    int k;
    if(i == j)
        printf("A%d", i);
    else {
        k = P[i][j];
        printf("(");
        order(i,k,P);
        order(k+1, j,P);
        printf(")");
    }
}

int minmult(int n, int d[], int *P[])   // 최소 곱셉 알고리즘
{
    int i, j, k, diagnonal, min_k = 0;
    int **M, temp = 0;
    M = make_array(n+1);
    for(i = 1; i <= n; i++)
        M[i][i] = 0;
    for(diagnonal = 1; diagnonal <= n-1; diagnonal++)  // diagonal값이 1이면
        for(i = 1; i <= n - diagnonal;i++) {          // 주대각선의 바로 위에
            j = i + diagnonal;                          // 있는 대각선을 의미한다.
            /* for(k~~~)는 아래에 해당한다.
             * M[i][j] = minimum(M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j]);
             *           i<= k <= j-1                   */
            for(k = i; k <= j-1; k++) {
                M[i][j] = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
                if(i == k) {
                    temp = M[i][j];
                    min_k = k;
                } else if(M[i][j] > temp) {
                    M[i][j] = temp;
                } else
                    min_k = k;
            }
            P[i][j] = min_k;    // 최소값을 주는 k의 값
        }
    return M[1][n];    // 최소 곱셈 값 리턴
}