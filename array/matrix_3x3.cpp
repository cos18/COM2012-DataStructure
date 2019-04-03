//# 2. 두개의 3X3 2차원 배열을 입력 받아서,
//#     1) 두 행렬의 합
//#     2) 두 행렬의 차
//#     3) 두 행렬의 곱
//# 연산을 선택하여 출력하는 프로그램을  구현해보세요.
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 9

void print_metrix(int *m){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) printf("%d ", m[3*i+j]);
        printf("\n");
    }
}

void metrix_sum(int *r, int *m1, int *m2){
    for(int i=0;i<LENGTH;i++) *(r+i) = *(m1+i) + *(m2+i);
}
void metrix_minus(int *r, int *m1, int *m2){
    for(int i=0;i<LENGTH;i++) *(r+i) = *(m1+i) - *(m2+i);
}
void metrix_mul(int *r, int *m1, int *m2){
    int tmp;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tmp=0;
            for(int k=0;k<3;k++) tmp += *(m1+3*i+k) * *(m2+3*k+j);
            *(r+i*3+j) = tmp;
        }
    }
}

int main(){
    int *a = (int *)malloc(sizeof(int)*LENGTH);
    int *b = (int *)malloc(sizeof(int)*LENGTH);
    printf("첫번째 3x3 행렬을 입력해주세요.\n");
    for(int i=0;i<LENGTH;i++) scanf("%d", a+i);
    printf("두번째 3x3 행렬을 입력해주세요.\n");
    for(int i=0;i<LENGTH;i++) scanf("%d", b+i);

    printf("<첫번째 배열입니다>\n");
    print_metrix(a);
    printf("\n<두번째 배열입니다>\n");
    print_metrix(b);

    int choice;
    int *result = (int *)malloc(sizeof(int)*9);
    while(1){
        printf("실행할 계산을 선택해주세요\n");
        printf("1. 행렬의 덧셈\n");
        printf("2. 행렬의 뺄셈\n");
        printf("3. 행렬의 곱셈\n");
        printf("(나머지 값 입력시 종료)\n");
        printf(" >> ");
        scanf("%d", &choice);
        if(choice==1){
            metrix_sum(result, a, b);
        } else if (choice == 2){
            metrix_minus(result, a, b);
        } else if (choice == 3){
            metrix_mul(result, a, b);
        } else break;
        printf("\n계산 결과입니다.\n");
        print_metrix(result);
    }
    free(a);
    free(b);
    free(result);
    getchar();
    getchar();
    return 0;
}