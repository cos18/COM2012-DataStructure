#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXDEGREE 10

typedef struct Node{
    char data;
    int degree;
    Node *parent;
    Node **child;
};
typedef struct SearchNode{
    Node *node; // data
    SearchNode *nextNode;
};

typedef struct SearchQueue{
    SearchNode *head;
    SearchNode *tail;
};

Node* createNode(char data);
void addChildNode(Node* parent, char data);
void removeTreeNode(Node* n);
Node** getSibling(Node* target);
Node* getParent(Node* target);
Node** getChild(Node* target);
void printTree(Node* rootNode);
int getLevel(Node* target, int level); // 초기 level = 0
int getTreeLevel(Node* rootNode, int level); // 초기 level = 0
void deleteNode(Node* target);
void getAncestors(Node* target);
void getDescendants(Node* target);
int getDegree(Node* target);
int getTreeDegree(Node* rootNode);
int cntTreeNode(Node* rootNode);
void insertSibling(Node* target, char data);
void clearTree(Node* rootNode);
void help();

void printNodeArray(Node** array);
void printNode(Node* node);

// BFS 관련 함수들
SearchNode* createSearchNode(Node *node);
SearchQueue* createSearchQueue();
void enqueue(SearchQueue* q, SearchNode* n);
Node* dequeue(SearchQueue* q);
int queueCnt(SearchQueue* q);
Node* breadthFirstSearch(Node* main, char data);
void removeQueue(SearchQueue* q);

int main(){
    Node *rootTreeNode=NULL;
    char command[20], tmp;
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'H'를 입력하세요)\n");
    while(1) {
        scanf("%s", &command);
        if (command[0] == 'Q') break;
        switch(command[0]){
            case '+': {
                if (command[1] == '^') rootTreeNode = createNode(command[2]);
                else {
                    if (rootTreeNode == NULL) {
                        printf("[ERROR] 아직 루트 노드를 만들지 않았습니다. 루트 노드를 먼저 만들어주세요.\n");
                        break;
                    }
                    Node *parentNode = breadthFirstSearch(rootTreeNode, command[1]);
                    if (parentNode == NULL) {
                        printf("[ERROR] 부모 노드 %c를 찾을 수 없습니다.\n", command[1]);
                        break;
                    }
                    int locate = 3;
                    while (locate < strlen(command)) {
                        addChildNode(parentNode, command[locate]);
                        locate += 2;
                    }
                }
                break;
            }
            case 'S': {
                Node* target = breadthFirstSearch(rootTreeNode, command[2]);
                if(target==NULL){
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                    break;
                }
                Node** sib = getSibling(target);
                if(sib!=NULL) printNodeArray(sib);
                free(sib);
                break;
            }
            case 'P': {
                Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                if (target == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                    break;
                }
                Node* parent = getParent(target);
                if(parent==NULL){
                    printf("[NOTICE] 부모가 없습니다\n");
                    break;
                }
                printNode(parent);
                break;
            }
            case 'C':{
                Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                if (target == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                    break;
                }
                printNodeArray(getChild(target));
                break;
            }
            case 'T':
                printTree(rootTreeNode);
                break;
            case 'L':
                if(strlen(command)>1){
                    Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                    if (target == NULL) {
                        printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                        break;
                    }
                    printf("%d\n", getLevel(target, 0));
                    break;
                }
                printf("%d\n", getTreeLevel(rootTreeNode, 0));
                break;
            case '-':{
                Node *target = breadthFirstSearch(rootTreeNode, command[1]);
                if (target == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[1]);
                    break;
                }
                deleteNode(target);
                break;
            }
            case 'A':{
                Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                if (target == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                    break;
                }
                getAncestors(target);
                break;
            }
            case 'D':{
                Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                if (target == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                    break;
                }
                getDescendants(target);
                break;
            }
            case 'G':
                if(strlen(command)>1){
                    Node *target = breadthFirstSearch(rootTreeNode, command[2]);
                    if (target == NULL) {
                        printf("[ERROR] 노드 %c를 찾을 수 없습니다.\n", command[2]);
                        break;
                    }
                    printf("%d\n", getDegree(target));
                    break;
                }
                printf("%d\n", getTreeDegree(rootTreeNode));
                break;
            case '#':
                printf("%d\n", cntTreeNode(rootTreeNode));
                break;
            case '=': {
                Node *sibNode = breadthFirstSearch(rootTreeNode, command[2]);
                if (sibNode == NULL) {
                    printf("[ERROR] 노드 %c를 찾을 수 없습니다.", command[2]);
                    break;
                }
                int locate = 4;
                while (locate < strlen(command)) {
                    insertSibling(sibNode, command[locate]);
                    locate += 2;
                }
                break;
            }
            case 'K':
                clearTree(rootTreeNode);
                rootTreeNode=NULL;
                break;
            case 'H':
                help();
                break;
            default:
                printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    if(rootTreeNode!=NULL) clearTree(rootTreeNode);
    getchar();
    getchar();
    return 0;
}

Node* createNode(char data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->degree=0;
    newNode->child=(Node**)malloc(sizeof(Node*)*MAXDEGREE);
    newNode->parent=NULL;
    return newNode;
}
void addChildNode(Node* parent, char data){
    if(parent->degree==MAXDEGREE){
        printf("[ERROR] 현제 집어넣을려고 하는 노드의 부모노드가 꽉 찼습니다. 설정된 최대 차수는 %d입니다.\n", MAXDEGREE);
        return;
    }
    Node* newNode = createNode(data);
    newNode->parent = parent;
    parent->child[(parent->degree)++] = newNode;
}
Node** getSibling(Node* target){
    Node* parent = target->parent;
    if(parent==NULL){
        printf("[ERROR] 이 노드는 루트 노드입니다.");
        return NULL;
    }
    if(parent->degree==1){
        printf("[NOTICE] 이 노드는 형제 노드가 없습니다.");
        return NULL;
    }
    Node** nodeArray = (Node**)malloc(sizeof(Node*)*(parent->degree));
    int locate = 0;
    for(int i=0;i<parent->degree;i++){
        if(target!=parent->child[i]){
            nodeArray[locate++] = parent->child[i];
        }
    }
    nodeArray[locate]=NULL;
    return nodeArray;
}
Node* getParent(Node* target){
    return target->parent;
}
Node** getChild(Node* target){
    Node** returnArray = (Node**)malloc(sizeof(Node*)*((target->degree)+1));
    for(int i=0;i<target->degree;i++) returnArray[i] = target->child[i];
    returnArray[target->degree] = NULL;
    return returnArray;
}
void printTree(Node* rootNode){
    if(rootNode==NULL){
        printf("[NOTICE] 빈 트리입니다.\n");
        return;
    }
    if (!(rootNode->degree)){
        if (rootNode->parent==NULL) printf("(%c)\n", rootNode->data);
        return;
    }
    if (rootNode->parent==NULL) printf("(%c", rootNode->data);
    printf("(");
    for(int i=0;i<rootNode->degree;i++){
        printf("%c", rootNode->child[i]->data);
        printTree(rootNode->child[i]);
        if(i!=(rootNode->degree)-1) printf(",");
    }
    printf(")");
    if (rootNode->parent==NULL) printf(")\n");
}
int getLevel(Node* target, int level){
    if(target->parent==NULL) return level;
    return getLevel(target->parent, level+1);
}
int getTreeLevel(Node* rootNode, int level){
    int returnLevel = level;
    for(int i=0;i<rootNode->degree;i++){
        int check = getTreeLevel(rootNode->child[i], level+1);
        if(returnLevel<check) returnLevel = check;
    }
    return returnLevel;
}
void deleteNode(Node* target){
    if(target->degree){
        printf("[ERROR] 이 노드는 자식이 있음으로 지울 수 없습니다.\n");
        return;
    }
    Node* parent = target->parent;
    int checkChild = 0;
    for(int i=0;i<parent->degree;i++){
        if(checkChild) parent->child[i-1] = parent->child[i];
        if(target==parent->child[i]) checkChild = 1;
        if(i==parent->degree-1) parent->child[i]=NULL;
    }
    (parent->degree)--;
    free(target->child);
    free(target);
}
void getAncestors(Node* target){
    if(target->parent==NULL){
        printf("\n");
        return;
    }
    printf("%c ", target->parent->data);
    getAncestors(target->parent);
}
void getDescendants(Node* target){
    printf("[NOTICE] 이 노드의 서브트리를 출력합니다.\n");
    printTree(target);
}
int getDegree(Node* target){
    return target->degree;
}
int getTreeDegree(Node* rootNode){
    int returnDegree = rootNode->degree;
    for(int i=0;i<rootNode->degree;i++){
        int check = getTreeDegree(rootNode->child[i]);
        if(returnDegree<check) returnDegree = check;
    }
    return returnDegree;
}
int cntTreeNode(Node* rootNode){
    if(!(rootNode->degree)) return 1;
    int sum = 0;
    for(int i=0;i<rootNode->degree;i++){
        sum += cntTreeNode(rootNode->child[i]);
    }
    return sum+1;
}
void insertSibling(Node* target, char data){
    if(target->parent==NULL){
        printf("[ERROR] 루트 노드에 형제 노드를 추가할 수는 없습니다.\n");
        return;
    }
    addChildNode(target->parent, data);
}
void clearTree(Node* rootNode){
    for(int i=0;i<rootNode->degree;i++) clearTree(rootNode->child[i]);
    free(rootNode->child);
    free(rootNode);
}
void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나 미구현된 기능이 존재합니다.\n");
    printf("미구현 기능 내용 : J(Join Trees)\n");
    printf("이하 명령어는 실습활동지에 없는 명령어를 구현한 목록입니다.\n");
    printf("H : 도움말 출력\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}

void printNodeArray(Node** array){
    printf("{");
    int locate = 0;
    while(array[locate]){
        if(locate) printf(", ");
        printf("%c", array[locate]->data);
        locate++;
    }
    printf("}\n");
}
void printNode(Node* node){
    printf("%c\n", node->data);
}

SearchNode* createSearchNode(Node *node){
    SearchNode* newSearchNode = (SearchNode*)malloc(sizeof(SearchNode));
    newSearchNode->nextNode = NULL;
    newSearchNode->node = node;
    return newSearchNode;
}
SearchQueue* createSearchQueue(){
    SearchQueue* newSearchQueue = (SearchQueue*)malloc(sizeof(SearchQueue));
    newSearchQueue->head=NULL;
    newSearchQueue->tail=NULL;
    return newSearchQueue;
}
void enqueue(SearchQueue* q, SearchNode* n){
    if(queueCnt(q)==0){
        q->head = q->tail = n;
        return;
    }
    q->tail->nextNode = n;
    q->tail = n;
}
Node* dequeue(SearchQueue* q){
    if(queueCnt(q)==0){
        printf("[ERROR] 큐에서 나올 노드가 없습니다.\n");
        return NULL;
    }
    SearchNode* outSearchNode = q->head;
    q->head = q->head->nextNode;
    Node* exitNode = outSearchNode->node;
    free(outSearchNode);
    return exitNode;
}
int queueCnt(SearchQueue* q){
    int cnt = 0;
    SearchNode* count = q->head;
    while(count){
        cnt++;
        count = count->nextNode;
    }
    return cnt;
}
Node* breadthFirstSearch(Node* main, char data){
    SearchQueue* queue = createSearchQueue();
    SearchNode* insertSearchNode = createSearchNode(main);
    enqueue(queue, insertSearchNode);
    while(queueCnt(queue)){
        Node* outNode = dequeue(queue);
        if (outNode->data==data){
            removeQueue(queue);
            return outNode;
        }
        for(int i=0;i<outNode->degree;i++) enqueue(queue, createSearchNode(outNode->child[i]));
    }
    removeQueue(queue);
    return NULL;
}
void removeQueue(SearchQueue* q){
    SearchNode* count;
    while(q->head){
        count = q->head;
        q->head = q->head->nextNode;
        free(count);
    }
    free(q);
}