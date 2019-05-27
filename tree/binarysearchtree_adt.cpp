#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int data;
    Node* child[2]; // 0 - left, 1 - right
    int childCnt;
    Node* parent;
};

Node* createNode(int data);
void insertNode(Node* rootNode, int data);
Node* findNode(Node* rootNode, int target);
void printBST(Node* rootNode);
void inorderTraverse(Node* rootNode, int isReversed); // 0 - inorder
int getMinMax(Node* rootNode, int isMax); // 0 - min , 1 - Max
void findNodePath(Node* rootNode, Node* target, int isSearching); // 시작시 0
void deleteNode(Node*& rootNode, Node* target, int getRightNode);
int getHeight(Node* rootNode, int level); // 기본값 - 1
int getChild(Node* target, int isRight);
int cntNode(Node* rootNode);
void clearBST(Node* rootNode);

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

int main(){
    Node *rootBSTNode = NULL;
    char command[50];
    int realnum;
    printf("[NOTICE] 지금부터 명령어를 입력하실 수 있습니다(도움이 필요하면 'h'를 입력하세요)\n");
    while(1) {
        scanf("%s", &command);
        if (command[0] == 'Q') break;
        if (command[1]>=49 && command[1]<=57){
            char num[10], pos=0;
            while(command[pos+1]>=48 && command[pos+1]<=57){
                num[pos]=command[pos+1];
                pos++;
            }
            num[pos]='\0';
            realnum = atoi(num);
        }
        switch(command[0]){
            case '+':
                if(rootBSTNode){
                    insertNode(rootBSTNode, realnum);
                } else{
                    rootBSTNode = createNode(realnum);
                }
                break;
            case 'P':
                printBST(rootBSTNode);
                break;
            case 'I':
                inorderTraverse(rootBSTNode, 0);
                printf("\n");
                break;
            case 'R':
                inorderTraverse(rootBSTNode, 1);
                printf("\n");
                break;
            case 'N':
                printf("%d\n", getMinMax(rootBSTNode, 0));
                break;
            case 'X':
                printf("%d\n", getMinMax(rootBSTNode, 1));
                break;
            case 'F':
                findNodePath(rootBSTNode, findNode(rootBSTNode, realnum), 0);
                break;
            case 'd':
                deleteNode(rootBSTNode, findNode(rootBSTNode, realnum), 0);
                break;
            case 'D':
                deleteNode(rootBSTNode, findNode(rootBSTNode, realnum), 1);
                break;
            case 'H':
                printf("%d\n", getHeight(rootBSTNode, 1));
                break;
            case 'G':
            case 'L': {
                int result = getChild(findNode(rootBSTNode, realnum), command[0] == 'G');
                if (result != -1) printf("%d\n", result);
                break;
            }
            case '#':
                printf("%d\n", cntNode(rootBSTNode));
                break;
            case 'C':
                clearBST(rootBSTNode);
                rootBSTNode = NULL;
                break;
            case 'h':
                help();
                break;
            default:
                printf("[ERROR] 잘못된 명령어를 입력하셨습니다. 입력하신 명령어는 \'%s\'입니다.\n", command);
                break;
        }
    }
    printf("[NOTICE] 프로그램을 종료합니다.\n");
    if(rootBSTNode!=NULL) clearBST(rootBSTNode);
    getchar();
    getchar();
    return 0;
}

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->child[0] = newNode->child[1] = NULL;
    newNode->parent = NULL;
    newNode->childCnt = 0;
    return newNode;
}
void insertNode(Node* rootNode, int data){
    if(rootNode->data==data){
        printf("[ERROR] 이미 있는 데이터를 넣을 수 없습니다.\n");
        return;
    }
    int locate = 0;
    if(rootNode->data < data) locate = 1;
    if(rootNode->child[locate]) return insertNode(rootNode->child[locate], data);
    rootNode->child[locate] = createNode(data);
    rootNode->child[locate]->parent = rootNode;
    rootNode->childCnt += 1;
}
Node* findNode(Node* rootNode, int target){
    if(!rootNode){
        printf("[ERROR] 값을 찾을 수 없습니다.\n");
        return NULL;
    }
    if(rootNode->data == target) return rootNode;
    return findNode(rootNode->child[rootNode->data < target], target);
}
void printBST(Node* rootNode){
    if(rootNode==NULL){
        printf("[NOTICE] 빈 트리입니다.\n");
        return;
    }
    if(!(rootNode->parent)) printf("(%d", rootNode->data);
    if(rootNode->childCnt){
        printf("(");
        if(rootNode->child[0]){
            printf("%d", rootNode->child[0]->data);
            printBST(rootNode->child[0]);
        }
        printf(",");
        if(rootNode->child[1]){
            printf("%d", rootNode->child[1]->data);
            printBST(rootNode->child[1]);
        }
        printf(")");
    }
    if(!(rootNode->parent)) printf(")\n");
}
void inorderTraverse(Node* rootNode, int isReversed){
    if(rootNode->child[isReversed]) inorderTraverse(rootNode->child[isReversed], isReversed);
    printf("%d ", rootNode->data);
    if(rootNode->child[1-isReversed]) inorderTraverse(rootNode->child[1-isReversed], isReversed);
}
int getMinMax(Node* rootNode, int isMax){
    if(rootNode->child[isMax]) return getMinMax(rootNode->child[isMax], isMax);
    return rootNode->data;
}
void findNodePath(Node* rootNode, Node* target, int isSearching){
    if(target==NULL) return;
    if(isSearching==0) printf("Root");
    if(rootNode == target){
        printf("\n");
        return;
    }
    printf(" > %s", (rootNode->data < target->data)?"Right":"Left");
    return findNodePath(rootNode->child[rootNode->data < target->data], target, 1);
}
void deleteNode(Node*& rootNode, Node* target, int getRightNode){
    if(!target) return;
    Node* parent = target->parent;
    if(parent){
        int isParentsRight = target->parent->data < target->data;
        switch (target->childCnt){
            case 0:
                parent->child[isParentsRight] = NULL;
                parent->childCnt -= 1;
                free(target);
                break;
            case 1:
                parent->child[isParentsRight] = (target->child[0])?target->child[0]:target->child[1];
                if(!parent->child[isParentsRight]) parent->childCnt -= 1;
                free(target);
                break;
            case 2: {
                Node* childTreeRoot = target->child[getRightNode];
                Node* changeNode = (childTreeRoot->child[1-getRightNode])?childTreeRoot->child[1-getRightNode]:childTreeRoot;
                while(changeNode->child[1-getRightNode]){
                    changeNode = childTreeRoot->child[1-getRightNode];
                }
                target->data = changeNode->data;
                if(childTreeRoot==changeNode) target->child[getRightNode] = changeNode->child[getRightNode];
                else changeNode->parent->child[1-getRightNode] = changeNode->child[getRightNode];
                if(changeNode->child[getRightNode]) changeNode->child[getRightNode]->parent = changeNode->parent;
                if(!changeNode->parent->child[1-getRightNode]) changeNode->parent->childCnt -= 1;
                free(changeNode);
                break;
            }
            default:
                break;
        }
    } else { // 지우려는 노드가 루트노드일 경우
        switch (target->childCnt){
            case 0:
                free(target);
                rootNode = NULL;
                break;
            case 1:
                rootNode = (target->child[0]) ? target->child[0] : target->child[1];
                free(target);
                break;
            case 2: {
                Node *childTreeRoot = target->child[getRightNode];
                Node *changeNode = (childTreeRoot->child[1 - getRightNode]) ? childTreeRoot->child[1 - getRightNode] : childTreeRoot;
                while (changeNode->child[1 - getRightNode]) {
                    changeNode = childTreeRoot->child[1 - getRightNode];
                }
                target->data = changeNode->data;
                if(childTreeRoot==changeNode) target->child[getRightNode] = changeNode->child[getRightNode];
                else changeNode->parent->child[1-getRightNode] = changeNode->child[getRightNode];
                if(changeNode->child[getRightNode]) changeNode->child[getRightNode]->parent = changeNode->parent;
                if(!changeNode->parent->child[1-getRightNode]) changeNode->parent->childCnt -= 1;
                free(changeNode);
                break;
            }
            default:
                break;
        }
    }

}
int getHeight(Node* rootNode, int level){
    int returnLevel = level;
    for(int i=0;i<2;i++){
        if(rootNode->child[i]){
            int check = getHeight(rootNode->child[i], level+1);
            if(returnLevel<check) returnLevel = check;
        }
    }
    return returnLevel;
}
int getChild(Node* target, int isRight){
    if(!target) return -1;
    if(target->child[isRight]) return target->child[isRight]->data;
    printf("[ERROR] %s쪽 자식이 없습니다.\n", isRight?"오른":"왼");
    return -1;
}
int cntNode(Node* rootNode){
    if(!(rootNode->childCnt)) return 1;
    int sum = 0;
    for(int i=0;i<2;i++){
        if(rootNode->child[i]){
            sum += cntNode(rootNode->child[i]);
        }
    }
    return sum+1;
}
void clearBST(Node* rootNode){
    for(int i=0;i<2;i++) if(rootNode->child[i]) clearBST(rootNode->child[i]);
    free(rootNode);
}
