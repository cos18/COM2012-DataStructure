#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXDEGREE 10

typedef struct Node{
    char data;
    int degree;
    Node **child;
};

typedef struct Tree{
    Node *root;
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
Tree* createTree();
void addChildNode(Node* parent, char data);
SearchNode* createSearchNode(Node *node);
SearchQueue* createSearchQueue();
void enqueue(SearchQueue* q, SearchNode* n);
Node* dequeue(SearchQueue* q);
int queueCnt(SearchQueue* q);
Node* breadthFirstSearch(Node* main, char data, int isPrinted);
void removeQueue(SearchQueue* q);
void removeTreeNode(Node* n);

int main(){
    char nodes[100];
    Tree* mainTree = createTree();
    Node* locateNode;
    printf("트리를 생성하였습니다.\n");
    printf("트리에 넣을 노드들을 입력해주세요.\n");
    printf("입력 순서는 부모노드 자식노드1 자식노드2 자식노드3 ... 순으로 입력해주세요.\n");
    printf("맨 처음 입력한 부모노드는 트리의 루트가 됩니다\n");
    printf("입력이 완료되면 *을 입력해주세요.\n");
    printf("ex)\nA B C D\nB E F\nD G H I\n*\n입력시\n");
    printf("     A\n B   C    D\nE F     G H I\n와 같은 트리가 만들어집니다.\n");
    while(1){
        gets(nodes);
        if(nodes[0]=='*') break;
        if(mainTree->root==NULL){
            mainTree->root = createNode(nodes[0]);
            locateNode = mainTree->root;
        } else{
            SearchQueue* queue = createSearchQueue();
            locateNode = breadthFirstSearch(mainTree->root, nodes[0], 0);
        }
        int locate=2;
        while(locate<strlen(nodes)){
            addChildNode(locateNode, nodes[locate]);
            locate += 2;
        }
    }
    printf("트리를 설정 완료했습니다.\n");
    printf("찾을 노드 데이터를 입력해주세요. >> ");
    char find;
    while(1){
        find = getchar();
        if(find!='\n') break;
    }
    Node* resultNode = breadthFirstSearch(mainTree->root, find, 1);
    if(resultNode != NULL) printf("노드 %c를 찾았습니다!\n", find);
    else printf("노드 %c를 찾지 못헀습니다.\n", find);
    removeTreeNode(mainTree->root);
    free(mainTree);
    getchar();
    getchar();
    return 0;
}

Node* createNode(char data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->degree=0;
    newNode->child=(Node**)malloc(sizeof(Node*)*MAXDEGREE);
    return newNode;
}
Tree* createTree(){
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;
    return newTree;
}
void addChildNode(Node* parent, char data){
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
Node* breadthFirstSearch(Node* main, char data, int isPrinted){
    SearchQueue* queue = createSearchQueue();
    SearchNode* insertSearchNode = createSearchNode(main);
    enqueue(queue, insertSearchNode);
    while(queueCnt(queue)){
        Node* outNode = dequeue(queue);
        if(isPrinted) printf("노드 %c를 확인합니다.\n", outNode->data);
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
void removeTreeNode(Node* n){
    for(int i=0;i<n->degree;i++) removeTreeNode(n->child[i]);
    free(n);
}