#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char data;
    Node* next;
};

typedef struct QueueADT{
    Node* head;
    Node* tail;
};

Node* createNode(char data);
QueueADT* createQueue();
void enqueue(QueueADT* q, char data);
void print(QueueADT* q);
void peek(QueueADT* q);
void dequeue(QueueADT* q);
int queueCnt(QueueADT* q);
int isEmpty(QueueADT* q);
int isFull();
int isMember(QueueADT* q, char data);
void replace(QueueADT* q, char data);
void clear(QueueADT* q);
void help();
char* changeBool(int boolean);

int main(){
    QueueADT *adt;
    char command[5], tmp;
    adt = createQueue();
    printf("[NOTICE] 큐를 생성했습니다\n");
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'H'를 입력하세요)\n");
    while(1) {
        scanf("%s", &command);
        if (command[0] == 'Q') break;
        switch(command[0]){
            case '+':
                enqueue(adt, command[1]);
                break;
            case 'L':
                print(adt);
                break;
            case 'P':
                peek(adt);
                break;
            case '-':
                dequeue(adt);
                break;
            case 'E':
                printf("%s\n", changeBool(isEmpty(adt)));
                break;
            case 'F':
                printf("%s\n", changeBool(isFull()));
                break;
            case '?':
                printf("%d\n", isMember(adt, command[1]));
                break;
            case '#':
                printf("%d\n", queueCnt(adt));
                break;
            case '=':
                replace(adt, command[1]);
                break;
            case 'C':
                clear(adt);
                adt = createQueue();
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
                    for(int i=0;i<realnum;i++) dequeue(adt);
                    break;
                }
                printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    clear(adt);
    getchar();
    getchar();
    return 0;
}

Node* createNode(char data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

QueueADT* createQueue(){
    QueueADT* newQueue = (QueueADT*)malloc(sizeof(QueueADT));
    newQueue->head = newQueue->tail = NULL;
    return newQueue;
}

void enqueue(QueueADT* q, char data){
    if(isFull()){
        printf("[ERROR] 메모리에 빈 공간이 없어 새로운 데이터를 enqueue할 수 없습니다.\n");
        return;
    }
    Node* enNode = createNode(data);
    if(queueCnt(q)==0){
        q->head = q->tail = enNode;
        return;
    }
    q->tail->next = enNode;
    q->tail = enNode;
}
void print(QueueADT* q){
    if(queueCnt(q)==0){
        printf("[NOTICE] 빈 큐입니다.\n");
        return;
    }
    Node* print = q->head;
    while(print){
        printf("%c ", print->data);
        print = print->next;
    }
    printf("\n");
}
void peek(QueueADT* q){
    if(queueCnt(q)==0){
        printf("[NOTICE] 빈 큐입니다.\n");
        return;
    }
    printf("%c\n", q->head->data);
}
void dequeue(QueueADT* q){
    if(queueCnt(q)==0){
        printf("[ERROR] 빈 큐에 dequeue를 할 수 없습니다.\n");
        return;
    }
    Node* outN = q->head;
    q->head = q->head->next;
    printf("%c\n", outN->data);
    free(outN);
}
int queueCnt(QueueADT* q){
    int cnt = 0;
    Node* count = q->head;
    while(count){
        cnt++;
        count = count->next;
    }
    if(!cnt) q->tail = NULL;
    return cnt;
}
int isEmpty(QueueADT* q){
    if(queueCnt(q)) return 0;
    return 1;
}
int isFull(){
    Node* testNode;
    if(!(testNode = (Node*)malloc(sizeof(testNode)))){
        free(testNode);
        return 1;
    }
    free(testNode);
    return 0;
}
int isMember(QueueADT* q, char data){
    int loc = -1, locat = 1;
    Node* find = q->head;
    while(find){
        if(data==find->data){
            loc = locat;
            break;
        }
        locat++;
        find = find->next;
    }
    return loc;
}
void replace(QueueADT* q, char data){
    if(queueCnt(q)==0){
        printf("[ERROR] 비어있는 큐임으로 대치(replace)할 수 없습니다.\n");
        return;
    }
    q->tail->data = data;
}
void clear(QueueADT* q){
    Node* del;
    do{
        del = q->head;
        q->head = q->head->next;
        free(del);
    } while(q->head);
    free(q);
}
void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나, 연결리스트로 구현했기 때문에 몇몇 기능을 구현하지 않았습니다.\n");
    printf("미구현 기능 내용 : H(head), T(tail)\n");
    printf("이하 명령어는 실습활동지에 없는 명령어를 구현한 목록입니다.\n");
    printf("H : 도움말 출력\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}
char* changeBool(int boolean){
    if(boolean) return "True";
    return "False";
}