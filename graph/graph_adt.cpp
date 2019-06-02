// 무방향 그래프 ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct connectNode{
    char data;
    connectNode* next;
};

typedef struct graphNode{
    char data;
    connectNode* connect;
    graphNode* next;
};

void help(){
    printf("=====HELP=====\n");
    printf("기본 기능은 실습활동 명령어와 동일하나 일부 변경사항이 존재합니다.\n");
    printf("1. deleteNode 작업의 명령어가 세분화되었습니다.\n");
    printf("지우려는 노드의 자식노드가 두개 존재시 대체할 노드를 선택할 수 있습니다.\n");
    printf("\'d33\' 입력시 지우려는 노드의 왼쪽 자식노드트리에서,\n");
    printf("\'D33\' 입력시 지우려는 노드의 오른쪽 자식노드트리에서 대체할 노드를 가져옵니다.\n");
    printf("\'-33\' 명령어는 사용할 수 없습니다.\n\n");
    printf("2. G, L 명령어 입력시 괄호를 쓰면 안됩니다.\n");
    printf("ex) \'G(30)\' (X) -> \'G30\' (O)\n\n");
    printf("3. 이하 명령어는 실습활동지에 없는 명령어를 구현한 목록입니다.\n");
    printf("h : 도움말 출력 (소문자에 유의)\n");
    printf("Q : 프로그램 종료\n");
    printf("==============\n");
}

connectNode* createConnectNode(char data);
graphNode* createGraph();
void insertVertex(graphNode* root, char data);
graphNode* getVertex(graphNode* root, char data);
void addEdge(graphNode* root, char v1, char v2);
void printGraph(graphNode* root);
void printEdge(connectNode* connect);
int getDegreeOfVertex(graphNode* target);
int isConnected(graphNode* root);
int isEmpty(graphNode* root);
void deleteVertex(graphNode*& root, char target);
void removeGraphNode(graphNode*& root, char target);
int isPathExist(graphNode* root, char v1, char v2);
int getVertexCNT(graphNode* root);
int getEdgeCNT(graphNode* root);
void deleteEdge(graphNode* root, char v1, char v2);
void removeConnetNode(connectNode*& root, char target);
void renameVertex(graphNode* root, char before, char after);
void clear(graphNode* root);

int main(){
    graphNode *rootGraphNode=NULL;
    char command[20];
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'S'를 입력하세요)\n");
    while(1) {
        scanf("%s", &command);
        if (command[0] == 'Q') break;
        switch(command[0]){
            case 'S':
                help();
                break;
            case 'G':
                rootGraphNode = createGraph();
                break;
            default:
                break;
        }
        if ((command[0]!='H')&&(command[0]!='S')&&(!rootGraphNode)){
            printf("[ERROR] 그래프를 만든 이후 명령어를 실행할 수 있습니다.\n");
            continue;
        }
        switch(command[0]){
            case '+':
                insertVertex(rootGraphNode, command[1]);
                break;
            case 'E':
                addEdge(rootGraphNode, command[2], command[4]);
                break;
            case 'L':
                printf("(");
                printGraph(rootGraphNode);
                printf(")\n");
                break;
            case 'V':{
                int d = getDegreeOfVertex(getVertex(rootGraphNode, command[2]));
                if(d!=-1) printf("%d\n", d);
                break;
            }
            case 'N':{
                int e = isEmpty(rootGraphNode);
                if(e!=-1) printf("%s\n", e?"TRUE":"FALSE");
                break;
            }
            case 'A':{
                graphNode* target = getVertex(rootGraphNode, command[2]);
                if(target){
                    printf("{");
                    printEdge(target->connect);
                    printf("}\n");
                }
                break;
            }
            case '-':
                deleteVertex(rootGraphNode, command[1]);
                break;
            case 'P':{
                int p = isPathExist(rootGraphNode, command[2], command[4]);
                if(p!=-1) printf("%s\n", p?"TRUE":"FALSE");
                break;
            }
            case 'X':
                printf("%d\n", getVertexCNT(rootGraphNode));
                break;
            case 'H':
                printf("%d\n", getEdgeCNT(rootGraphNode));
                break;
            case 'D':
                deleteEdge(rootGraphNode, command[2], command[4]);
                break;
            case 'R':
                renameVertex(rootGraphNode, command[2], command[4]);
                break;
            case 'K':
                clear(rootGraphNode);
                rootGraphNode=NULL;
                break;
            default:
                if(command[0]!='S'&&command[0]!='G') printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    if(rootGraphNode!=NULL) clear(rootGraphNode);
    getchar();
    getchar();
    return 0;
}

connectNode* createConnectNode(char data){
    connectNode* newNode = (connectNode*)malloc(sizeof(connectNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
graphNode* createGraph(){
    graphNode* newNode = (graphNode*)malloc(sizeof(graphNode));
    newNode->data='\0';
    newNode->connect=NULL;
    newNode->next=NULL;
    return newNode;
}
void insertVertex(graphNode* root, char data){
    while(root->next){
        if(root->data==data){
            printf("[ERROR] 이미 존재하는 정점입니다.\n");
            return;
        }
        root = root->next;
    }
    if(root->data!='\0'){
        root->next = createGraph();
        root = root->next;
    }
    root->data = data;
}
graphNode* getVertex(graphNode* root, char data){
    while(root){
        if(root->data==data) return root;
        root = root->next;
    }
    printf("[ERROR] 정점 \'%c\'은(는) 존재하지 않는 정점입니다.\n");
    return NULL;
}
void addEdge(graphNode* root, char v1, char v2){
    graphNode* n[2];
    n[0] = getVertex(root, v1);
    n[1] = getVertex(root, v2);
    if(n[0] == NULL || n[1] == NULL) return;
    if(isPathExist(root, v1, v2)){
        printf("[ERROR] 정점 \'%c\'와(과) \'%c\' 사이 경로는 이미 존재하는 경로입니다.\n", v1, v2);
        return;
    }
    for(int i=0;i<2;i++){
        connectNode* c = n[i]->connect;
        if(!c){
            n[i]->connect = createConnectNode(i?v1:v2);
            continue;
        }
        while(c->next){
            c = c->next;
        }
        c->next = createConnectNode(i?v1:v2);
    }
}
void printGraph(graphNode* root){
    if(root->data=='\0') return;
    printf("%c", root->data);
    if(root->connect){
        printf("(");
        printEdge(root->connect);
        printf(")");
    }
    if(!root->next) return;
    printf(",");
    printGraph(root->next);
}
void printEdge(connectNode* connect){
    printf("%c", connect->data);
    if(!connect->next) return;
    printf(",");
    printEdge(connect->next);
}
int getDegreeOfVertex(graphNode* target){
    if(!target) return -1;
    int result = 0;
    connectNode* c = target->connect;
    while(c){
        result++;
        c = c->next;
    }
    return result;
}
int isConnected(graphNode* root);
int isEmpty(graphNode* root){
    if(!root){
        printf("[ERROR] 현제 그래프가 만들어지지 않았습니다.\n");
        return -1;
    }
    if(root->data=='\0') return TRUE;
    return FALSE;
}
void deleteVertex(graphNode*& root, char target){
    graphNode* targetNode = getVertex(root, target);
    if(!targetNode) return;
    connectNode* c = targetNode->connect;
    while(c){
        removeConnetNode(getVertex(root, c->data)->connect, target);
        c = c->next;
    }
    removeGraphNode(root, target);
}
void removeGraphNode(graphNode*& root, char target){
    graphNode* freeNode = root;
    if(freeNode->data == target){
        root = root->next;
        return free(freeNode);
    }
    while(freeNode->next->data!=target) freeNode = freeNode->next;
    graphNode* targetNode = freeNode->next;
    freeNode->next = targetNode->next;
    return free(targetNode);
}
int isPathExist(graphNode* root, char v1, char v2){
    graphNode* target = getVertex(root, v1);
    if(!target || !getVertex(root, v2)) return -1;
    connectNode* c = target->connect;
    while(c){
        if(c->data == v2) return TRUE;
        c = c->next;
    }
    return FALSE;
}
int getVertexCNT(graphNode* root){
    int result = 0;
    while(root){
        if(root->data=='\0') break;
        result++;
        root = root->next;
    }
    return result;
}
int getEdgeCNT(graphNode* root){
    int result=0;
    while(root){
        connectNode* c = root->connect;
        while(c){
            result++;
            c = c->next;
        }
        root = root->next;
    }
    return result/2;
}
void deleteEdge(graphNode* root, char v1, char v2){
    int path = isPathExist(root, v1, v2);
    if(path!=1){
        if(path==FALSE) printf("[ERROR] \'%c\'에서 \'%c\'로 이어지는 경로가 존재하지 않습니다.\n", v1, v2);
        return;
    }
    graphNode* n1 = getVertex(root, v1);
    graphNode* n2 = getVertex(root, v2);
    removeConnetNode(n1->connect, v2);
    removeConnetNode(n2->connect, v1);
}
//Node*&
void removeConnetNode(connectNode*& root, char target){
    connectNode* freeNode = root;
    if(freeNode->data == target){
        root = root->next;
        return free(freeNode);
    }
    while(freeNode->next->data!=target) freeNode = freeNode->next;
    connectNode* targetNode = freeNode->next;
    freeNode->next = targetNode->next;
    return free(targetNode);
}
void renameVertex(graphNode* root, char before, char after){
    graphNode* target = getVertex(root, before);
    if(target==NULL) return;
    connectNode* c = target->connect;
    while(c){
        connectNode* changec = getVertex(root, c->data)->connect;
        while(changec->data!=before) changec = changec->next;
        changec->data = after;
        c = c->next;
    }
    target->data = after;
}
void clear(graphNode* root){
    if(!root) return;
    clear(root->next);
    free(root->connect);
    free(root);
}