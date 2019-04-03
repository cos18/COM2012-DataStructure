#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 9

typedef struct v {
    char name[100];
    int isWaterClean;
    int isWireless;
    int price;
    int buyCount;
    int star;
} vacuum;

int printcnt=LENGTH;

vacuum vlist[LENGTH] = {
        { "Dyson100", 0, 1, 13000, 30, 3 },
        { "Dyson200", 1, 0, 15000, 27, 4 },
        { "Samsung100", 0, 0, 10000, 35, 2 },
        { "Samsung200", 1, 1, 70000, 40, 5 },
        { "Samsung300", 0, 1, 30000, 20, 3 },
        { "Lg100", 1, 0, 30000, 15, 4 },
        { "Lg200", 1, 1, 60000, 22, 5 },
        { "Mi150", 1, 1, 50000, 44, 5 },
        { "Mi200", 0, 1, 35000, 23, 4 }
};

// vacuum result[LENGTH]={};

void show(vacuum *slist, int isMalloc);   // 목록 출력
vacuum* search();           // 검색 : 문자열 비교를 통해 동일한 이름의 청소기 제시
vacuum* filtering();        // 기능 필터링(물청소 가능, 무선/유선) : 조건문을 통하여 선택된 기능들을 가진 청소기만 노출
// 가격대 조정 : 조건문을 통하여 선택된 가격대의 청소기만 노출

void sort();             // 정렬 : 구매순, 평점순, 가격오르내림순으로 정렬을 하여 제시
// 구매순의 경우 : 소비자가 구매를 할 때마다 품목별로 1씩 카운팅하여 이를 기준으로 정렬한다.
// https://norux.me/10
// https://wwwwwwwwwwwww.tistory.com/142
int priceUpCompare(const void *v1, const void *v2) {
    int p1, p2;
    p1 = ((vacuum *)v1)->price;
    p2 = ((vacuum *)v2)->price;
    if (p1 < p2) return -1;
    else if (p1 == p2) return 0;
    else return 1;
}
int priceDownCompare(const void *v1, const void *v2) {
    int p1, p2;
    p1 = ((vacuum *)v1)->price;
    p2 = ((vacuum *)v2)->price;
    if (p1 > p2) return -1;
    else if (p1 == p2) return 0;
    else return 1;
}
int countCompare(const void *v1, const void *v2) {
    int p1, p2;
    p1 = ((vacuum *)v1)->buyCount;
    p2 = ((vacuum *)v2)->buyCount;
    if (p1 > p2) return -1;
    else if (p1 == p2) return 0;
    else return 1;
}
int starCompare(const void *v1, const void *v2) {
    int p1, p2;
    p1 = ((vacuum *)v1)->star;
    p2 = ((vacuum *)v2)->star;
    if (p1 > p2) return -1;
    else if (p1 == p2) return 0;
    else return 1;
}

int main() {
    int menuSelect;
    while (1) {
        printf("======청소기 구매 사이트=====\n\n");
        printf("원하시는 메뉴의 번호를 입력하세요\n");
        printf("1. 전체목록 조회\n");
        printf("2. 청소기 검색\n");
        printf("3. 전체목록 필터링\n");
        printf("4. 전체목록 정렬\n");
        printf("0. 종료\n");
        printf(" >> ");
        scanf("%d", &menuSelect);
        if (!menuSelect) break;
        switch (menuSelect) {
            case 1:
                show(vlist, 0);
                break;
            case 2:
                show(search(), 0);
                break;
            case 3:
                show(filtering(), 1);
                break;
            case 4:
                sort();
                break;
            default:
                printf("\n잘못 입력하셨습니다. 다시 입력해주세요!\n");
                break;
        }
    }
    return 0;
}

void show(vacuum *slist, int isMalloc) {
    //int slistSize = sizeof(*slist) / sizeof(vacuum);
//    printf("%d %d %d", sizeof(*slist), sizeof(vacuum), slistSize);
//    for (int i = 0; i < LENGTH; i++) { // (!!HELP!!) LENGTH 번이 아니라, slist의 vacuum의 갯수만큼
//        if (!slist[i].star) { slistSize++;
//        printf("%d : %s\n", i, slist[i].name);}
//    }

    if (slist != NULL) {
        // int len = slistSize;
        printf("==================================================\n");
        // 이름   물청소가능여부(0불가능/1가능)   무선/유선(0/1)    가격    구매   평점(1~5)
        printf(" %10s | %5s | %4s | %7s | %4s | %2s\n", "이름", "물청소", "통신", "가격", "구매", "평점");
        printf("--------------------------------------------------\n");
        for (int i = 0; i<printcnt; i++) {
            printf(" %10s | %5s | %4s | %7d | %4d | %2d\n",
                   slist[i].name,
                   slist[i].isWaterClean ? "가 능" : "불가능",
                   slist[i].isWireless ? "무선" : "유선",
                   slist[i].price,
                   slist[i].buyCount,
                   slist[i].star);
        }
        printf("==================================================\n\n");
        printcnt = LENGTH;
    }
    if (isMalloc) {
        free(slist);
    }
}

vacuum* search() {           // 검색 : 문자열 비교를 통해 동일한 이름의 청소기 제시
    char temp[30];
    int searchNum = 0;
    int check[LENGTH] = { 0 };

    printf("검색하고 싶은 청소기 이름을 입력하세요: ");
    scanf("%s", temp);
    for (int i = 0; i < LENGTH; i++) {
        char *result = strstr(vlist[i].name, temp); //첫 글자는 검색왜안됨
        if (result != NULL) {     //왜 if절 조건(result결과값 없으면)에서 안걸림?
            searchNum++;
            check[i] = 1;
        }
        printf("check[%d]: %d\n", i, check[i]);
    }

    vacuum* searchResult = (vacuum*)malloc(sizeof(vacuum)*searchNum);
    //filtered 에 해당하는 vlist 정보 저장
    int x = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (check[i]) {
            searchResult[x] = vlist[i];
            x++;
        }
    }
    printcnt = searchNum;

    printf(" => 검색 결과입니다\n");
    return searchResult;
}

vacuum* filtering() {
    // 기능 필터링(물청소 가능, 무선/유선) : 조건문을 통하여 선택된 기능들을 가진 청소기만 노출
    // 가격대 조정 : 조건문을 통하여 선택된 가격대의 청소기만 노출

    int isWaterClean, isWireless, maxPrice, minPrice;

    // 조건 입력받기
    printf("======================\n");
    printf("괄호 안의 형식으로 조건을 입력해주세요\n");
//    printf("생략하고 싶은 조건은 엔터를 눌러주세요\n");
    printf("======================\n");

    printf("물청소 (가능1, 불가능0): ");
    scanf("%d", &isWaterClean);

    printf("무선: 1/ 유선: 0: ");
    scanf("%d", &isWireless);

    printf("원하는 가격대를 입력하세요(최저가격-최대가격)\n");
    scanf("%d-%d", &minPrice, &maxPrice);


    int filteredLength = 0;
    int check[LENGTH] = { 0 };

    for (int i = 0; i < LENGTH; i++) {
        if (vlist[i].isWaterClean == isWaterClean &&   // 사용자가 enter 누른 경우 vlist의 내용과 같을 수 없으므로 조건 filtering 가능
            vlist[i].isWireless == isWireless &&
            minPrice <= vlist[i].price &&
            vlist[i].price <= maxPrice) {
            filteredLength++;
            check[i]=1;
        }
    }

    if (filteredLength == 0) {
        printf(" => 해당하는 조건의 청소기가 없습니다.\n\n\n");
        return NULL;
    }
    else {
        printf("======================\n");
        printf("입력하신 조건에 맞는 청소기 목록입니다.\n");
    }

    vacuum* filtered = (vacuum*)malloc(sizeof(vacuum)*filteredLength);

    //filtered 에 해당하는 vlist 정보 저장
    int x = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (check[i]) {
            filtered[x] = vlist[i];
            x++;
        }
    }
    printcnt = filteredLength;
    return filtered;
}


void sort() {
    int sortSelect;
    while (1) {
        printf("\n========= 정렬 ========\n\n");
        printf("정렬하고 싶은 항목의 번호를 입력하세요\n");
        printf("1. 구매순\n");
        printf("2. 평점순\n");
        printf("3. 가격 오름차순\n");
        printf("4. 가격 내림차순\n");
        printf(" >> ");
        scanf("%d", &sortSelect);
        switch (sortSelect) {
            case 1:
                qsort(vlist, LENGTH, sizeof(vlist[0]), countCompare);
                break;
            case 2:
                qsort(vlist, LENGTH, sizeof(vlist[0]), starCompare);
                break;
            case 3:
                qsort(vlist, LENGTH, sizeof(vlist[0]), priceUpCompare);
                break;
            case 4:
                qsort(vlist, LENGTH, sizeof(vlist[0]), priceDownCompare);
                break;
            default:
                printf(" => 정렬 결과입니다\n");
        }
        if (sortSelect <= 4 && sortSelect >= 1) break;
        printf("\n잘못 입력하셨습니다. 다시 입력해주세요!\n");
    }
    show(vlist, 0);
}