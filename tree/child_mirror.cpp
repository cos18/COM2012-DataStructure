// 이진 트리의 좌우 child를 바꾸는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXDEPTH 10

// 0 / 1 2 / 3 4 5 6 /

typedef struct Tree{
    char* data;
    int depth;
};

Tree* makeTree();
void putData(Tree* tree, char data, char left, char right);
void mirrorTree(Tree* tree);
void printTree(Tree* tree);

int main(){
    char nodes[6];
    Tree* useTree = makeTree();
    printf("트리에 넣을 노드들을 입력해주세요.\n");
    printf("입력 순서는 부모노드 왼쪽자식노드 오른쪽자식노드 순으로 입력해주세요.\n");
    printf("자식노드가 비어있으면 *을 넣어주세요.\n");
    printf("맨 처음 입력한 부모노드는 트리의 루트가 됩니다\n");
    printf("입력이 완료되면 !을 입력해주세요.\n");
    printf("ex)\nA B C\nC D E\nE * F\n!\n입력시\n");
    printf("A\nB       C\n*   *   D   E\n* * * * * * * F\n와 같은 트리가 만들어집니다.\n");
    while(1){
        gets(nodes);
        if(nodes[0]=='!') break;
        putData(useTree, nodes[0], nodes[2], nodes[4]);
    }
    printf("====이전 트리====\n");
    printTree(useTree);
    mirrorTree(useTree);
    printf("====변경 트리====\n");
    printTree(useTree);
    return 0;
}

Tree* makeTree(){
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->data = (char*)malloc(sizeof(char)*(pow(2.0, MAXDEPTH+1)-1));
    newTree->depth = 0;
    return newTree;
}
void putData(Tree* tree, char parent, char left, char right){
    if(parent=='*'){
        printf("[ERROR] 빈 부모 노드를 설정 할 수 없습니다.\n");
        return;
    }
    if(!(tree->depth)){
        tree->data[0] = parent;
        tree->data[1] = left;
        tree->data[2] = right;
        tree->depth = 1;
        return;
    }
    int locate = 1, max = pow(2.0, tree->depth);
    while(locate < max){
        if(tree->data[locate]==parent){
            if(locate>=pow(2.0, MAXDEPTH)-1){
                printf("[ERROR] 지정한 최고 깊이보다 더 깊은 노드를 자식으로 둘 수 없습니다\n");
                return;
            }
            tree->data[locate*2+1] = left;
            tree->data[locate*2+2] = right;
            if(max < locate*2+2) (tree->depth)++;
            return;
        }
        locate++;
    }
    printf("[ERROR] 지정한 부모 노드가 트리 내 없는 노드입니다.\n");
}

void mirrorTree(Tree* tree){
    for(int i=1;i<tree->depth;i++){
        int swap = pow(2.0, i-1);
        int sum = (swap*3-1)*2-1;
        for(int j=0;j<swap;j++){
            int target = j+swap*2-1;
            tree->data[target] = tree->data[target] ^ tree->data[sum-target];
            tree->data[sum-target] = tree->data[target] ^ tree->data[sum-target];
            tree->data[target] = tree->data[target] ^ tree->data[sum-target];
        }
    }
}

void printTree(Tree* tree){
    for(int i=0;i<tree->depth;i++){
        int cnt = pow(2.0, i), space = pow(2.0, tree->depth - i)-1;
        for(int j=0;j<cnt;j++){
            if (tree->data[cnt-1+j]<'A' || tree->data[cnt-1+j]>'z') printf("*");
            else printf("%c", tree->data[cnt-1+j]);
            for(int k=0;k<space;k++) printf(" ");
        }
        printf("\n");
    }
}