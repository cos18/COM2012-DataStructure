#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayADT{
    char *array; // 데이터를 저장할 배열
    int locateAt; // 현제 명령어를 실행할 위치
    int maxSize; // 이 배열의 최대 사이즈
    int nowSize; // 현제 데이터를 가지고 있는 크기
};

void create(ArrayADT *adt, int size);
void insert(ArrayADT *adt, char data);
void traverse_front(ArrayADT *adt, int count);
void traverse_rear(ArrayADT *adt, int count);
void movePosition(ArrayADT *adt, int position);
void delete_data(ArrayADT *adt);
void get_data(ArrayADT *adt);
void replace(ArrayADT *adt, char data);
void empty(ArrayADT *adt);
void move(ArrayADT *adt, int position);
void pushData_right(ArrayADT *adt, int from, int to); // 일정 범위의 데이터를 한칸 오른쪽으로 이동시킨다.
void pushData_left(ArrayADT *adt, int from, int to); // 일정 범위의 데이터를 한칸 왼쪽으로 이동시킨다.
int data_count(ArrayADT *adt);
void print(ArrayADT *adt);
void print_withLocation(ArrayADT *adt);
void help();
void debug(ArrayADT *adt);
void destroy(ArrayADT *adt);

int main(){
    ArrayADT *adt;
    int size, isFront=0, isRear=0;
    char command[5];
    while(1){
        printf("[NOTICE] 배열 ADT를 시작하기 전, 배열의 최대크기를 입력해주세요.\n");
        scanf("%d", &size);
        if (size>0) break;
        printf("[ERROR] 배열의 크기는 1 이상이여야 합니다.\n");
    }
    create(adt, size);
    printf("[NOTICE] 배열을 생성했습니다\n");
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'H'를 입력하세요)\n");
    while(1){
        scanf("%s", &command);
        if(command[0]=='Q') break;
        switch (command[0]){
            case '<':
                isFront++;
                break;
            case 'N':
                if(!isFront){
                    printf("[ERROR] N 명령어는 < 명령어 이후에 사용할 수 있습니다.\n");
                    break;
                }
                isFront++;
                break;
            default:
                if(isFront){
                    traverse_front(adt, isFront-1);
                    isFront = 0;
                }
        }
        switch (command[0]){
            case '>':
                isRear++;
                break;
            case 'P':
                if(!isRear){
                    printf("[ERROR] P 명령어는 > 명령어 이후에 사용할 수 있습니다.\n");
                    break;
                }
                isRear++;
                break;
            default:
                if(isRear){
                    traverse_rear(adt, isRear-1);
                    isRear = 0;
                }
        }
        if(!(isFront || isRear)){
            switch (command[0]){
                case '+':
                    insert(adt, command[1]);
                    break;
                case '-':
                    delete_data(adt);
                    break;
                case '@':
                    get_data(adt);
                    break;
                case '=':
                    replace(adt, command[1]);
                    break;
                case 'E':
                    empty(adt);
                    break;
                case 'M':
                    switch (command[1]){
                        case 'P':
                            move(adt, adt->locateAt - 1);
                            break;
                        case 'N':
                            move(adt, adt->locateAt + 1);
                            break;
                        case 'n':
                            move(adt, data_count(adt)-1);
                            break;
                        default:
                            if(command[1]>47 && command[1]<58) move(adt, atoi(command + 1));
                            else printf("[ERROR] M 명령어 뒤에 올바르지 않은 값을 입력하셨습니다. M 명령어 뒤에는 P, N, n, 또는 숫자만 올 수 있습니다.\n");
                    }
                    break;
                case 'L':
                    if(command[1]=='P') print_withLocation(adt);
                    else print(adt);
                    break;
                case 'H':
                    help();
                    break;
                case 'D':
                    debug(adt);
                    break;
                default:
                    printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
            }
        }
        // debug(adt);
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    destroy(adt);
}

void create(ArrayADT *adt, int size){
    // adt = (ArrayADT*)malloc(sizeof(ArrayADT));
    adt->array = (char*)malloc(sizeof(char)*size);
    adt->locateAt = -1;
    adt->maxSize = size;
    adt->nowSize = 0;
}
void insert(ArrayADT *adt, char data){
    if(data_count(adt) == adt->maxSize){
        printf("[ERROR] 설정한 배열의 최대 크기보다 많은 데이터를 저장할 수 없습니다.\n");
        return;
    }
    adt->locateAt++;
    if(adt->locateAt != data_count(adt)) pushData_right(adt, adt->locateAt, data_count(adt)-1);
    adt->array[adt->locateAt] = data;
    adt->nowSize++;
}
void traverse_front(ArrayADT *adt, int count){
    movePosition(adt, 0);
    for(int i=1;i<count+1;i++){
        movePosition(adt, i);
    }
}
void traverse_rear(ArrayADT *adt, int count){
    movePosition(adt, data_count(adt) - 1);
    for(int i=data_count(adt)-2;i>=data_count(adt)-(1+count);i--){
        movePosition(adt, i);
    }
}
void movePosition(ArrayADT *adt, int position){
    if(!data_count(adt)){
        printf("[ERROR] 빈 배열에서는 이동할 수 없습니다.\n");
    }
    if(position<0 || position>=adt->nowSize){
        printf("[ERROR] 현제 배열 범위를 초과하게 움직일 수 없습니다.\n");
        return;
    }
    adt->locateAt = position;
}
void delete_data(ArrayADT *adt){
    if(!(adt->nowSize)) {
        printf("[ERROR] 빈 배열에서 데이터를 지울 수 없습니다.\n");
        return;
    }
    adt->nowSize--;
    if(adt->locateAt != data_count(adt)) pushData_left(adt, adt->locateAt+1, data_count(adt));
    if(!(adt->nowSize)) adt->locateAt=-1;
    if(data_count(adt) == adt->locateAt) adt->locateAt = 0;
}
void get_data(ArrayADT *adt){
    printf("Return %c\n", adt->array[adt->locateAt]);
}
void replace(ArrayADT *adt, char data){
    if(!(adt->nowSize)) {
        printf("[ERROR] 빈 배열에서 데이터를 대치할 수 없습니다.\n");
        return;
    }
    adt->array[adt->locateAt] = data;
}
void empty(ArrayADT *adt){
    free(adt->array);
    adt->array = (char *)malloc(sizeof(char)*(adt->maxSize));
    adt->nowSize=0;
    adt->locateAt=-1;
}
void move(ArrayADT *adt, int position){
    if(!data_count(adt)){
        printf("[ERROR] 빈 배열에서는 이동할 수 없습니다.\n");
        return;
    }
    if(position<0 || position>=adt->nowSize){
        printf("[ERROR] 현제 배열 범위를 초과하게 움직일 수 없습니다.\n");
        return;
    }
    if(adt->locateAt == position){
        printf("[NOTICE] 현재 위치를 입력해 아무 변화가 없습니다.\n");
        return;
    }
    char keep;
    if(adt->locateAt < position){
        keep = adt->array[adt->locateAt];
        pushData_left(adt, adt->locateAt+1, position);
    } else {
        keep = adt->array[adt->locateAt];
        pushData_right(adt, position, adt->locateAt-1);
    }
    adt->array[position] = keep;
    adt->locateAt = position;
}
void pushData_right(ArrayADT *adt, int from, int to){
    for(int i=to;i>from-1;i--) adt->array[i+1] = adt->array[i];
}
void pushData_left(ArrayADT *adt, int from, int to){
    for(int i=from-1;i<to;i++) adt->array[i] = adt->array[i+1];
}
int data_count(ArrayADT *adt){
    return adt->nowSize;
}
void print(ArrayADT *adt){
    if(!(adt->nowSize)){
        printf("[NOTICE] 빈 배열입니다\n");
        return;
    }
    for(int i=0;i<adt->nowSize;i++){
        printf("%c ", adt->array[i]);
    }
    printf("\n");
}
void print_withLocation(ArrayADT *adt){
    if(!(adt->nowSize)){
        printf("[NOTICE] 빈 배열입니다\n");
        return;
    }
    for(int i=0;i<adt->nowSize;i++){
        if(i==adt->locateAt) printf("<%c> ", adt->array[i]);
        else printf("%c ", adt->array[i]);
    }
    printf("\n");
}
void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나, 추가적인 기능이 존재합니다.\n");
    printf("H : 도움말 출력\n");
    printf("LP : 현제 명령어가 실행되는 포지션의 위치를 표시해 배열 전체 출력\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}
void debug(ArrayADT *adt){
    printf("=====DEBUG=====\n");
    printf(" ---array---\n");
    print_withLocation(adt);
    printf(" -----------\n");
    printf("locateAt : %d\n", adt->locateAt);
    printf("nowSize : %d\n", data_count(adt));
    printf("maxSize : %d\n", adt->maxSize);
    printf("===============\n");
}
void destroy(ArrayADT *adt){
    free(adt->array);
}