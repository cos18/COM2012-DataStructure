#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char data;
    Node *next;
    Node *prev;
};

typedef struct LinkedListADT{ // Double Linked List
    Node *head;
    Node *tail;
    Node *currPosition;
};

Node* createNode(char data);
LinkedListADT* createLinkedList();
int cnt(LinkedListADT* adt);
void addNode(LinkedListADT** adt, char data);
void printList(LinkedListADT *adt, int isPrintPos);
void get_data(LinkedListADT *adt);
void traverse(LinkedListADT **adt, int type);
void deleteNode(LinkedListADT **adt);
void replace(LinkedListADT *adt, char data);
int gotoPosition(LinkedListADT **adt, int position);
void is_member(LinkedListADT **adt, char data);
void is_empty(LinkedListADT *adt);
void passNullNode(LinkedListADT **adt);
void clear(LinkedListADT **adt);
void help();
void freeList(LinkedListADT *adt);

int main(){
    LinkedListADT* saveADT;
    char command[10];
    saveADT = createLinkedList();
    printf("[NOTICE] 연결 리스트를 생성했습니다\n");
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'H'를 입력하세요)\n");
    while(1){
        scanf("%s", &command);
        if(command[0]=='Q') break;
        switch (command[0]) {
            case '+':
                addNode(&saveADT, command[1]);
                break;
            case 'L':
                if(command[1]=='P') printList(saveADT, 1);
                else printList(saveADT, 0);
                break;
            case 'G':
                get_data(saveADT);
                break;
            case '<':
                traverse(&saveADT, 0);
                break;
            case 'N':
                traverse(&saveADT, 1);
                break;
            case '-':
                deleteNode(&saveADT);
                break;
            case '>':
                traverse(&saveADT, 2);
                break;
            case 'P':
                traverse(&saveADT, 3);
                break;
            case '=':
                replace(saveADT, command[1]);
                break;
            case '#':
                printf("%d\n", cnt(saveADT));
                break;
            case '?':
                is_member(&saveADT, command[1]);
                break;
            case 'C':
                clear(&saveADT);
                break;
            case 'E':
                is_empty(saveADT);
                break;
            case 'H':
                help();
                break;
            default:
                if(command[0]>=49 && command[0]<=57){
                    char num[10], pos=0;
                    while(command[pos]>=48 && command[pos]<=57){
                        num[pos]=command[pos];
                        pos++;
                    }
                    num[pos]='\0';
                    if(gotoPosition(&saveADT, atoi(num))){
                        switch (command[pos]){
                            case 'G':
                                get_data(saveADT);
                                break;
                            case '=':
                                replace(saveADT, command[pos+1]);
                                break;
                        }
                        break;
                    }
                }
                printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    freeList(saveADT);
    return 0;
}

Node* createNode(char data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

LinkedListADT* createLinkedList(){
    LinkedListADT *newList = (LinkedListADT*)malloc(sizeof(LinkedListADT));
    Node *nullNode = createNode('\0');
    newList->head = nullNode;
    newList->tail = nullNode;
    newList->currPosition = nullNode;
    return newList;
}

int cnt(LinkedListADT* adt){
    int cnt = 0;
    Node *countPtr = adt->head->next;
    while(countPtr){
        cnt++;
        countPtr = countPtr->next;
    }
    return cnt;
}

void addNode(LinkedListADT** adt, char data){
    Node *newNode = createNode(data);
    if((*adt)->currPosition->next==NULL){
        newNode->prev = (*adt)->currPosition;
        newNode->prev->next = newNode;
        (*adt)->tail = newNode;
        (*adt)->currPosition = newNode;
        return;
    }
    newNode->next = (*adt)->currPosition->next;
    newNode->prev = (*adt)->currPosition;
    (*adt)->currPosition->next->prev = newNode;
    (*adt)->currPosition->next = newNode;
    (*adt)->currPosition = newNode;
}

void printList(LinkedListADT *adt, int isPrintPos){
    if(!cnt(adt)){
        printf("[NOTICE] 빈 연결리스트입니다.\n");
        return;
    }
    Node *printNode = adt->head->next;
    while(printNode){
        if(isPrintPos && (printNode==adt->currPosition)) printf(">%c< ", printNode->data);
        else printf("%c ", printNode->data);
        printNode = printNode->next;
    }
    printf("\n");
}

void get_data(LinkedListADT *adt){
    if(!(cnt(adt))){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return;
    }
    printf("%c\n", adt->currPosition->data);
}

void traverse(LinkedListADT **adt, int type){
    if(!(cnt(*adt))){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return;
    }
    switch (type){ // 0: front, 1: next, 2:rear
        case 0:
            (*adt)->currPosition = (*adt)->head;
            break;
        case 1:
            passNullNode(adt);
            if((*adt)->currPosition == (*adt)->tail){
                printf("[ERROR] 현제 위치가 맨 끝에 있습니다.\n");
                return;
            }
            (*adt)->currPosition = (*adt)->currPosition->next;
            break;
        case 2:
            (*adt)->currPosition = (*adt)->tail;
            break;
        case 3:
            if((*adt)->currPosition == (*adt)->head->next){
                printf("[ERROR] 현제 위치가 맨 앞에 있습니다.\n");
                return;
            }
            (*adt)->currPosition = (*adt)->currPosition->prev;
            break;
    }
}

void deleteNode(LinkedListADT **adt){
    if(!cnt(*adt)){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return;
    }
    passNullNode(adt);
    if((*adt)->currPosition==(*adt)->tail){
        (*adt)->currPosition->prev->next = NULL;
        (*adt)->tail = (*adt)->currPosition->prev;
        free((*adt)->currPosition);
        (*adt)->currPosition = (*adt)->head;
        if(cnt(*adt)) passNullNode(adt);
        return;
    }
    (*adt)->currPosition->prev->next = (*adt)->currPosition->next;
    (*adt)->currPosition->next->prev = (*adt)->currPosition->prev;
    Node *deleteNode = (*adt)->currPosition;
    (*adt)->currPosition = (*adt)->currPosition->next;
    free(deleteNode);
}

void replace(LinkedListADT *adt, char data){
    if(!cnt(adt)){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return;
    }
    passNullNode(&adt);
    adt->currPosition->data = data;
}

int gotoPosition(LinkedListADT **adt, int position){
    if(!cnt(*adt)){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return 0;
    }
    if(position > cnt(*adt)){
        printf("[ERROR] 리스트 크기를 초과하는 값을 받았습니다.\n");
        return 0;
    }
    (*adt)->currPosition = (*adt)->head;
    while(position){
        (*adt)->currPosition = (*adt)->currPosition->next;
        position--;
    }
    return 1;
}

void is_member(LinkedListADT **adt, char data){
    if(!cnt(*adt)){
        printf("[ERROR] 비어있는 연결리스트입니다.\n");
        return;
    }
    Node *checkNode = (*adt)->head->next;
    int curPosition = 1;
    int size = cnt(*adt);
    while(curPosition<=size){
        if(checkNode->data == data){
            (*adt)->currPosition = checkNode;
            printf("%d: ", curPosition);
            printList(*adt, 1);
            return;
        }
        checkNode = checkNode->next;
        curPosition++;
    }
    printf("[ERROR] 리스트 안에 값을 찾을 수 없습니다.\n");
}

void is_empty(LinkedListADT *adt){
    if(cnt(adt)) printf("FALSE\n");
    else printf("TRUE\n");
}

void passNullNode(LinkedListADT **adt){
    if((*adt)->currPosition==(*adt)->head) (*adt)->currPosition = (*adt)->currPosition->next;
}

void clear(LinkedListADT **adt){
    if(!cnt(*adt)){
        printf("[ERROR] 이미 비어있는 연결리스트입니다.\n");
        return;
    }
    Node *clearNode = (*adt)->head->next, *trash;
    while(clearNode){
        trash = clearNode;
        clearNode = clearNode->next;
        free(trash);
    }
    (*adt)->currPosition = (*adt)->head;
    (*adt)->currPosition->next = NULL;
    (*adt)->tail = (*adt)->head;
}

void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나, 추가적인 기능이 존재합니다.\n");
    printf("H : 도움말 출력\n");
    printf("P : 현제 명령어가 실행되는 포지션의 위치를 한칸 전으로 옮김\n");
    printf("LP : 현제 명령어가 실행되는 포지션의 위치를 표시해 배열 전체 출력\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}

void freeList(LinkedListADT *adt){
    if(cnt(adt)) clear(&adt);
    free(adt->head);
    free(adt);
}