#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct check{
    char sign[50];
    int locateAt;
};

check* createCheck();
void putSign(check* c, char data);
char popSign(check* c);
char peekSign(check* c);
int isCheckEmpty(check* c);
int isRightLine(char* line);

int main(){
    char line[100];
    printf("Python 명령어를 입력하세요.\n >> ");
    gets(line);
    if(isRightLine(line)) printf("올바른 명령어입니다!\n");
    else printf("잘못된 명령어입니다.");
    getchar();
    return 0;
}

check* createCheck(){
    check* newCheck = (check*)malloc(sizeof(check));
    newCheck->locateAt=-1;
    return newCheck;
}
void putSign(check* c, char data){
    c->sign[++(c->locateAt)]=data;
}
char popSign(check* c){
    if(c->locateAt < 0) return '\0';
    return c->sign[(c->locateAt)--];
}
char peekSign(check* c){
    if(c->locateAt < 0) return '\0';
    return c->sign[(c->locateAt)];
}
int isCheckEmpty(check* c){
    if(c->locateAt < 0) return 1;
    return 0;
}
int isRightLine(char* line){
    check* checkLine = createCheck();
    int lineSize = strlen(line);
    for(int i=0;i<lineSize;i++){
        switch(line[i]){
            case '\"':
            case '\'':
                if(peekSign(checkLine)==line[i]){
                    popSign(checkLine);
                    break;
                }
            case '(':
                putSign(checkLine, line[i]);
                break;
            case ')':
                if(peekSign(checkLine)=='('){
                    popSign(checkLine);
                    break;
                }
                free(checkLine);
                return 0;
        }
    }
    if(isCheckEmpty(checkLine)){
        free(checkLine);
        return 1;
    }
    free(checkLine);
    return 0;
}
