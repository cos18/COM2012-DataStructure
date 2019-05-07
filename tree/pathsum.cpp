// 다음 트리의 각 path의 합을 구하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXDEGREE 10

typedef struct Node{
    int data;
    int degree;
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

Node* createNode(int data);
void addChildNode(Node* parent, int data);
void removeTreeNode(Node* n);
SearchNode* createSearchNode(Node *node);
SearchQueue* createSearchQueue();
void enqueue(SearchQueue* q, SearchNode* n);
Node* dequeue(SearchQueue* q);
int queueCnt(SearchQueue* q);
Node* breadthFirstSearch(Node* main, int data);
void removeQueue(SearchQueue* q);
void pathSum(Node* parent, int sum);

int main(){
    char nodes[100];
    Node* locateNode;
    Node* treeRootNode=NULL;
    printf("트리에 넣을 노드들을 입력해주세요.\n");
    printf("입력 순서는 부모노드 자식노드1 자식노드2 자식노드3 ... 순으로 입력해주세요.\n");
    printf("맨 처음 입력한 부모노드는 트리의 루트가 됩니다\n");
    printf("입력이 완료되면 *을 입력해주세요.\n");
    printf("ex)\n1 2 3 4\n2 5 6\n4 7 8 9\n*\n입력시\n");
    printf("     1\n 2   3    4\n5 6     7 8 9\n와 같은 트리가 만들어집니다.\n");
    while(1){
        gets(nodes);
        if(nodes[0]=='*') break;
        int locate = 0, isFirst = 1;
        while(locate<strlen(nodes)){
            char num[10], pos=0;
            int realnum;
            while(nodes[locate]>=48 && nodes[locate]<=57){
                num[pos]=nodes[locate];
                pos++;
                locate++;
            }
            num[pos]='\0';
            realnum = atoi(num);
            if(isFirst){
                if(treeRootNode==NULL){
                    treeRootNode = createNode(realnum);
                    locateNode = treeRootNode;
                } else locateNode = breadthFirstSearch(treeRootNode, realnum);
                isFirst = 0;
            } else addChildNode(locateNode, realnum);
            locate++;
        }
    }
    printf("트리를 설정 완료했습니다.\n");
    pathSum(treeRootNode, 0);
    removeTreeNode(treeRootNode);
    getchar();
    return 0;
}

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->degree=0;
    newNode->child=(Node**)malloc(sizeof(Node*)*MAXDEGREE);
    return newNode;
}
void addChildNode(Node* parent, int data){
    if(parent->degree==MAXDEGREE){
        printf("[ERROR] 현제 집어넣을려고 하는 노드의 부모노드가 꽉 찼습니다. 설정된 최대 차수는 %d입니다.\n", MAXDEGREE);
        return;
    }
    Node* newNode = createNode(data);
    parent->child[(parent->degree)++] = newNode;
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
Node* breadthFirstSearch(Node* main, int data){
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
    do{
        count = q->head;
        q->head = q->head->nextNode;
        free(count);
    } while(q->head);
    free(q);
}
void removeTreeNode(Node* n) {
    for (int i = 0; i < n->degree; i++) removeTreeNode(n->child[i]);
    free(n);
}
void pathSum(Node* parent, int sum){
    if(!(parent->degree)){
        printf("단말 노드 %d: %d\n", parent->data, sum+(parent->data));
        return;
    }
    for(int i=0;i<parent->degree;i++) pathSum(parent->child[i], sum+(parent->data));
}