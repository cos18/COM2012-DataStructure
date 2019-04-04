#include <stdio.h>
#include <stdlib.h>

typedef struct Hang{
    int coef;
    int seung;
    Hang* next;
}Hang;

void createHang(Hang** node, int coef, int seung);
void printHang(Hang* node);
void sumHang(Hang* f, Hang* g, Hang** result);
void chaHang(Hang* f, Hang* g, Hang** result);
void attachHang(int coef, Hang* f, Hang** attach);
void removeHang(Hang** node);

int main(){
    Hang* fx = NULL;
    Hang* gx = NULL;
    Hang* sum = NULL;
    Hang* cha = NULL;

    createHang(&fx, 5, 12);
    createHang(&fx, -3, 9);
    createHang(&fx, 2, 7);
    createHang(&fx, -10, 5);
    createHang(&fx, 5, 4);
    createHang(&fx, -8, 3);
    createHang(&fx, 6, 2);
    createHang(&fx, -4, 1);
    createHang(&fx, 10, 0);
    printf("f(x) = ");
    printHang(fx);

    createHang(&gx, 13, 11);
    createHang(&gx, 7, 10);
    createHang(&gx, 5, 9);
    createHang(&gx, 3, 8);
    createHang(&gx, -4, 7);
    createHang(&gx, 1, 6);
    createHang(&gx, -12, 5);
    createHang(&gx, 9, 4);
    createHang(&gx, -5, 3);
    createHang(&gx, 1, 2);
    createHang(&gx, 7, 1);
    createHang(&gx, -23, 0);
    printf("g(x) = ");
    printHang(gx);

    sumHang(fx, gx, &sum);
    printf("f(x) + g(x) = ");
    printHang(sum);

    chaHang(fx, gx, &cha);
    printf("f(x) - g(x) = ");
    printHang(cha);

    removeHang(&fx);
    removeHang(&gx);
    removeHang(&sum);
    removeHang(&cha);
    return 0;
}

void createHang(Hang** node, int coef, int seung){
    if(*node!=NULL){
        return createHang(&((*node)->next), coef, seung);
    }
    *node = (Hang *)malloc(sizeof(Hang));
    (*node)->coef = coef;
    (*node)->seung = seung;
    (*node)->next = NULL;
}

void printHang(Hang* node){
    if(node==NULL){
        printf("\n");
        return;
    }
    if(node->coef==1) printf("+");
    else if(node->coef==-1) printf("-");
    else printf("%+d", node->coef);
    if(node->seung!=0) printf("x^%d", node->seung);
    return printHang(node->next);
}

void sumHang(Hang* f, Hang* g, Hang** result){
    if(f==NULL && g==NULL) return;
    if(f==NULL) return attachHang(1, g, result);
    if(g==NULL) return attachHang(1, f, result);
    if(f->seung > g->seung){
        createHang(result, f->coef, f->seung);
        sumHang(f->next, g, result);
    } else if (f->seung < g->seung){
        createHang(result, g->coef, g->seung);
        sumHang(f, g->next, result);
    } else {
        createHang(result, f->coef + g->coef, f->seung);
        sumHang(f->next, g->next, result);
    }
}

void chaHang(Hang* f, Hang* g, Hang** result){
    if(f==NULL && g==NULL) return;
    if(f==NULL) return attachHang(-1, g, result);
    if(g==NULL) return attachHang(1, f, result);
    if(f->seung > g->seung){
        createHang(result, f->coef, f->seung);
        chaHang(f->next, g, result);
    } else if (f->seung < g->seung){
        createHang(result, (-1) * g->coef, g->seung);
        chaHang(f, g->next, result);
    } else {
        createHang(result, f->coef - g->coef, f->seung);
        chaHang(f->next, g->next, result);
    }
}

void attachHang(int coef, Hang* f, Hang** attach){
    if(f==NULL) return;
    createHang(attach, coef * f->coef, f->seung);
    attachHang(coef, f->next, attach);
}

void removeHang(Hang** node){
    if(*node){
        removeHang(&((*node)->next));
        free(*node);
        *node = NULL;
    }
}