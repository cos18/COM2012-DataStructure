#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Scedule{
    int time; // 24시간 표시법 사용
    char description[50];
    Scedule *next = NULL;
};

void makeScedule(Scedule** myScedule, int time, char* description);
void fixScedule(Scedule* myScedule, int time, char* change);
void deleteScedule(Scedule** myScedule, int time);
void printScedule(Scedule* myScedule);
void removeAllScedule(Scedule** myScedule);

int main(){
    int choice, isContinued = 1;
    int time;
    char description[50];
    Scedule* saveScedule = NULL;
    while(isContinued){
        printf("==스케쥴 관리 프로그램==\n");
        printf("1. 스케쥴 추가\n");
        printf("2. 스케쥴 수정\n");
        printf("3. 스케쥴 삭제\n");
        printf("4. 스케쥴 출력\n");
        printf("(이외 값 입력시 종료)\n");
        printf(" >> ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("스케쥴을 등록할 시간대를 입력하세요\n >> ");
                scanf("%d", &time);
                getchar();
                printf("스케쥴의 상세 내용을 입력해주세요.\n >> ");
                fgets(description, sizeof(description), stdin);
                description[strlen(description)-1]='\0';
                makeScedule(&saveScedule, time, description);
                break;
            case 2:
                printf("스케쥴을 수정할 시간대를 입력하세요\n >> ");
                scanf("%d", &time);
                getchar();
                printf("수정할 스케쥴의 상세 내용을 입력해주세요.\n >> ");
                fgets(description, sizeof(description), stdin);
                description[strlen(description)-1]='\0';
                fixScedule(saveScedule, time, description);
                break;
            case 3:
                printf("스케쥴을 삭제할 시간대를 입력하세요\n >> ");
                scanf("%d", &time);
                deleteScedule(&saveScedule, time);
                break;
            case 4:
                printf("===현재 저장되어있는 스케쥴===\n");
                printScedule(saveScedule);
                break;
            default:
                isContinued = 0;
        }
    }
    removeAllScedule(&saveScedule);
}

void makeScedule(Scedule** myScedule, int time, char* description){
    Scedule* newScedule = (Scedule*)malloc(sizeof(Scedule));
    newScedule->time = time;
    strcpy(newScedule->description, description);
    newScedule->next = NULL;
    if(*myScedule == NULL){
        *myScedule = newScedule;
    } else if ((*myScedule)->time > time){
        newScedule->next = (*myScedule)->next;
        *myScedule = newScedule;
    } else if ((*myScedule)->time == time){
        printf("[ERROR] 같은 시간대에 스케쥴을 두개 이상 만들 수 없습니다.\n");
        return free(newScedule);
    } else {
        while((*myScedule)->next){
            if ((*myScedule)->next->time == time){
                printf("[ERROR] 같은 시간대에 스케쥴을 두개 이상 만들 수 없습니다.\n");
                return free(newScedule);
            }
            if((*myScedule)->next->time > time){
                newScedule->next = (*myScedule)->next;
                (*myScedule)->next = newScedule;
                break;
            }
            myScedule = &((*myScedule)->next);
        }
        if((*myScedule)->next == NULL){
            (*myScedule)->next = newScedule;
        }
    }
}

void fixScedule(Scedule* myScedule, int time, char* change){
    if(myScedule==NULL || myScedule->time > time){
        printf("[ERROR] 수정하고 싶은 시간대에 스케쥴이 없습니다.\n");
        return;
    }
    if(myScedule->time == time){
        strcpy(myScedule->description, change);
        return;
    }
    return fixScedule(myScedule->next, time, change);
}

void deleteScedule(Scedule** myScedule, int time){
    Scedule* delScedule;
    if(*myScedule==NULL){
        printf("[ERROR] 현재 스케쥴이 비어있습니다.\n");
        return;
    }
    if((*myScedule)->time==time){
        delScedule = *myScedule;
        *myScedule = (*myScedule)->next;
        return free(delScedule);
    }
    while((*myScedule)->next){
        if((*myScedule)->next->time>time){
            printf("[ERROR] 삭제할 시간대에 스케쥴이 없습니다.\n");
            return;
        }
        if((*myScedule)->next->time==time){
            delScedule = (*myScedule)->next;
            (*myScedule)->next = delScedule->next;
            return free(delScedule);
        }
        myScedule = &((*myScedule)->next);
    }
    printf("[ERROR] 삭제할 시간대에 스케쥴이 없습니다.\n");
}

void printScedule(Scedule* myScedule){
    if(myScedule == NULL) return;
    printf("[%3d시 : %-50s]\n", myScedule->time, myScedule->description);
    return printScedule(myScedule->next);
}

void removeAllScedule(Scedule** myScedule){
    if(*myScedule){
        removeAllScedule(&((*myScedule)->next));
        free(*myScedule);
        *myScedule = NULL;
    }
}