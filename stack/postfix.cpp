#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct infix{
    char sign[30];
    int locateAt;
};

typedef struct postfix{
    int value[30];
    int locateAt;
};

infix* createInfix();
void putInfix(infix* somef, char data);
char popInfix(infix *somef);
int isInfixEmpty(infix *somef);
char* infixToPostfix(char* infix);

postfix* createPostfix();
void putPostfix(postfix* somef, int data);
int popPostfix(postfix *somef);
int isPostfixEmpty(postfix *somef);
int postfixToValue(char* postchar);

int main(){
    char input_infix[50];
    char *postfix;
    int result;

    printf("일반 식을 입력하세요.\n >> ");
    gets(input_infix);
    postfix = infixToPostfix(input_infix);
    if(!strcmp(postfix, "error")){
        printf("중위표기식이 잘못되었습니다.\n");
        getchar();
        return 0;
    }
    printf("중위표기식에서 후위표기식으로 바꾼 식은 \"%s\" 입니다.\n", postfix);
    result = postfixToValue(postfix);
    if(result == INT_MAX){
        printf("후위표기식이 잘못되었습니다.\n");
        getchar();
        return 0;
    }
    printf("최종 계산 결과는 \"%d\"입니다.", result);
    getchar();
    return 0;
}

infix* createInfix(){
    infix* newfix = (infix *)malloc(sizeof(infix));
    newfix->locateAt=-1;
    return newfix;
}

void putInfix(infix* somef, char data){
    somef->sign[++(somef->locateAt)] = data;
}

char popInfix(infix *somef) {
    if(somef->locateAt<0) return '!'; // error
    return somef->sign[(somef->locateAt)--];
}

int isInfixEmpty(infix *somef){
    if(somef->locateAt<0) return 1;
    return 0;
}

char* infixToPostfix(char* inchar){
    infix* changeInfix = createInfix();
    char* postfix = (char*)malloc(sizeof(char)*strlen(inchar));
    int postLocation = 0;
    for(int i=0;i<strlen(inchar);i++){
        if(inchar[i]>47 && inchar[i]<58){
            postfix[postLocation++] = inchar[i];
            continue;
        }
        switch(inchar[i]){
            case ')':
                postfix[postLocation++] = popInfix(changeInfix);
                if(postfix[postLocation-1]=='!' || popInfix(changeInfix)!='('){
                    free(changeInfix);
                    return "error";
                }
                break;
            default:
                putInfix(changeInfix, inchar[i]);
        }
    }
    while(!isInfixEmpty(changeInfix)){
        postfix[postLocation++] = popInfix(changeInfix);
        if(postfix[postLocation-1] == '('){
            free(changeInfix);
            return "error";
        }
    }
    postfix[postLocation+1]='\0';
    free(changeInfix);
    return postfix;
}

postfix* createPostfix(){
    postfix* newfix = (postfix *)malloc(sizeof(postfix));
    newfix->locateAt=-1;
    return newfix;
}

void putPostfix(postfix* somef, int data){
    somef->value[++(somef->locateAt)] = data;
}

int popPostfix(postfix *somef){
    if(somef->locateAt<0) return INT_MAX; // error
    return somef->value[(somef->locateAt)--];
}

int isPostfixEmpty(postfix *somef){
    if(somef->locateAt<0) return 1;
    return 0;
}

int postfixToValue(char* postchar){
    postfix* changePostfix = createPostfix();
    for(int i=0;i<strlen(postchar);i++){
        if(postchar[i]>47 && postchar[i]<58){
            putPostfix(changePostfix, postchar[i]-48);
            continue;
        }
        int operand1, operand2;
        operand2 = popPostfix(changePostfix);
        operand1 = popPostfix(changePostfix);
        if(operand1==INT_MAX || operand2==INT_MAX){
            free(changePostfix);
            return INT_MAX;
        }
        switch(postchar[i]){
            case '+':
                putPostfix(changePostfix, operand1+operand2);
                break;
            case '-':
                putPostfix(changePostfix, operand1-operand2);
                break;
            case '*':
                putPostfix(changePostfix, operand1*operand2);
                break;
            case '/':
                putPostfix(changePostfix, operand1/operand2);
                break;
            default:
                free(changePostfix);
                return INT_MAX;
        }
    }
    int result = popPostfix(changePostfix);
    if(!isPostfixEmpty(changePostfix)){
        free(changePostfix);
        return INT_MAX;
    }
    free(changePostfix);
    return result;
}
