#include <stdlib.h>
#include <stdio.h>

typedef struct stackADT{
    char* data;
    int locateAt;
    int maxSize;
};

stackADT* createStack(int size);
void push(stackADT* adt, char data);
void print(stackADT* adt);
char peek(stackADT* adt);
char pop(stackADT* adt);
int cnt(stackADT* adt);
void top(stackADT* adt);
void replace(stackADT* adt, char newData);
void clear(stackADT* adt);
void destroyStack(stackADT *adt);

// 1:True, 0:False
int isFull(stackADT* adt);
int isEmpty(stackADT* adt);
int isMember(stackADT* adt, char data);
void printBoolean(int boolean);

void help();


int main(){
    stackADT *adt;
    int size;
    char command[5], tmp;
    while(1){
        printf("[NOTICE] 스택 ADT를 시작하기 전, 스택의 최대크기를 입력해주세요.\n");
        scanf("%d", &size);
        if (size>0) break;
        printf("[ERROR] 배열의 크기는 1 이상이여야 합니다.\n");
    }
    adt = createStack(size);
    printf("[NOTICE] 스택을 생성했습니다\n");
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'H'를 입력하세요)\n");
    while(1) {
        scanf("%s", &command);
        if (command[0] == 'Q') break;
        switch(command[0]){
            case '+':
                push(adt, command[1]);
                break;
            case 'L':
                print(adt);
                break;
            case 'P':
                tmp = peek(adt);
                if(tmp!='\0') printf("%c\n", tmp);
                break;
            case '-':
                tmp = pop(adt);
                if(tmp!='\0') printf("%c\n", tmp);
                break;
            case 'F':
                printBoolean(isFull(adt));
                break;
            case 'E':
                printBoolean(isEmpty(adt));
                break;
            case '?':
                printBoolean(isMember(adt, command[1]));
                break;
            case '#':
                printf("%d\n", cnt(adt));
                break;
            case 'T':
                top(adt);
                break;
            case '=':
                replace(adt, command[1]);
                break;
            case 'C':
                clear(adt);
                break;
            case 'H':
                help();
                break;
            default:
                if(command[0]>=49 && command[0]<=57){
                    char num[10], pos=0;
                    int realnum;
                    while(command[pos]>=48 && command[pos]<=57){
                        num[pos]=command[pos];
                        pos++;
                    }
                    num[pos]='\0';
                    realnum = atoi(num);
                    for(int i=0;i<realnum;i++){
                        tmp = pop(adt);
                        if(tmp!='\0') printf("%c\n", tmp);
                    }
                    break;
                }
                printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    destroyStack(adt);
    getchar();
    getchar();
    return 0;
}

stackADT* createStack(int size){
    stackADT* newStack = (stackADT*)malloc(sizeof(stackADT));
    newStack->data = (char*)malloc(sizeof(char)*size);
    newStack->locateAt = -1;
    newStack->maxSize = size;
    return newStack;
}

void push(stackADT* adt, char data){
    if(isFull(adt)){
        printf("[ERROR] 스택이 꽉 차서 데이터를 더 집어넣을 수 없습니다.\n");
        return;
    }
    adt->data[++(adt->locateAt)] = data;
}
void print(stackADT* adt){
    if(isEmpty(adt)){
        printf("[NOTICE] 빈 스택입니다.\n");
        return;
    }
    for(int i=0;i<cnt(adt);i++) printf("%c ", adt->data[i]);
    printf("\n");
}
char peek(stackADT* adt){
    if(isEmpty(adt)){
        printf("[NOTICE] 빈 스택입니다.\n");
        return '\0';
    }
    return adt->data[adt->locateAt];
}
char pop(stackADT* adt){
    if(isEmpty(adt)){
        printf("[ERROR] 스택이 비어있어 데이터를 뺄 수 없습니다.\n");
        return '\0';
    }
    return adt->data[(adt->locateAt)--];
}
int cnt(stackADT* adt){
    return (adt->locateAt)+1;
}
void top(stackADT* adt){
    char get = peek(adt);
    if(get!='\0') printf("( %d, %c )\n", cnt(adt), get);
}
void replace(stackADT* adt, char newData){
    if(isEmpty(adt)){
        printf("[ERROR] 스택이 비어있어 데이터를 뺄 수 없습니다.\n");
        return;
    }
    adt->data[adt->locateAt] = newData;
}
void clear(stackADT* adt){
    if(isEmpty(adt)){
        printf("[NOTICE] 이미 비어있는 스택입니다.\n");
        return;
    }
    free(adt->data);
    adt->data = (char*)malloc(sizeof(char)*(adt->maxSize));
    adt->locateAt=-1;
}
void destroyStack(stackADT *adt){
    free(adt->data);
    free(adt);
}

// 1:True, 0:False
int isFull(stackADT* adt){
    return cnt(adt)==(adt->maxSize);
}
int isEmpty(stackADT* adt){
    return cnt(adt)==0;
}
int isMember(stackADT* adt, char data){
    for(int i=0;i<(adt->locateAt)+1;i++){
        if(data==(adt->data[i])) return 1;
    }
    return 0;
}
void printBoolean(int boolean){
    printf("%s\n", (boolean)?"True":"False");
}

void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나, 추가적인 기능이 존재합니다.\n");
    printf("H : 도움말 출력\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}