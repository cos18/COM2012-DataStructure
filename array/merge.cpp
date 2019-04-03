#include <stdio.h>
#include <stdlib.h>

int* mergeSort(int *arr1, int cnt1, int *arr2, int cnt2);
int compareUpper(const void *a, const void *b) {
    if (*(int*)a > *(int*)b) return 1;
    else if (*(int*)a < *(int*)b) return -1;
    else return 0;
}

int main(){
    int arr1Cnt, arr2Cnt;

    printf("첫 번째 배열에 저장할 데이터 수를 입력하세요 : ");
    scanf("%d", &arr1Cnt);
    printf("두 번째 배열에 저장할 데이터 수를 입력하세요 : ");
    scanf("%d", &arr2Cnt);

    int *arr1 = (int*)malloc(sizeof(int)*arr1Cnt);
    int *arr2 = (int*)malloc(sizeof(int)*arr2Cnt);

    printf(">첫번째 배열에 넣을 데이터를 입력해주세요<\n");
    for (int i=0;i<arr1Cnt;i++) scanf("%d", &arr1[i]);
    printf("\n");
    printf(">두번째 배열에 넣을 데이터를 입력해주세요<\n");
    for (int i=0;i<arr2Cnt;i++) scanf("%d", &arr2[i]);

    qsort(arr1, (size_t)arr1Cnt, sizeof(int), compareUpper);
    qsort(arr2, (size_t)arr2Cnt, sizeof(int), compareUpper);

    int* merged = mergeSort(arr1, arr1Cnt, arr2, arr2Cnt);
    printf("\n>최종 결과입니다<\n");
    for(int i=0;i<arr1Cnt+arr2Cnt;i++) printf("%d ", merged[i]);

    free(arr1);
    free(arr2);
    free(merged);

    getchar();
    getchar();
    return 0;
}

int* mergeSort(int *arr1, int cnt1, int *arr2, int cnt2){
    int a=0, b=0, i=0;
    int *result = (int *)malloc(sizeof(int)*(cnt1+cnt2));
    while ((a!=cnt1) && (b!=cnt2)){
        if (arr1[a] > arr2[b]) result[i++]=arr2[b++];
        else result[i++]=arr1[a++];
    }
    if(a==cnt1) for(int j=b;j<cnt2;j++) result[i++]=arr2[j];
    else for(int j=a;j<cnt1;j++) result[i++]=arr1[j];
    return result;
}

