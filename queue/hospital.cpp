#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * 이 병원의 대전제
 * 0. 병원은 오후 2시 오픈, 6시에 문을 닫는다. (6시까지 온 환자는 6시가 지나도 치료를 해 준다.)
 * 1. 오픈시 최소 5명, 최대 10명의 환자가 온다.
 * 2. 환자는 1~10분의 치료시간이 든다.
 * 3. 새로운 환자는 1~3분 뒤에 온다.
 * 4. 매 정각마다(오후 3시, 4시, 5시, 6시) 중간집계를 한다.
 */

int patNextNum = 1, clocktime = 0; // 오후 2시 ~ 6시 - 240분

typedef struct Patient{
    int patNum;
    int cureTime;
    int waitingTime;
    Patient* next;
};

typedef struct WaitingQueue{
    Patient* head;
    Patient* tail;
};

typedef struct Doctor{
    int curingTimeSum = 0;
    int curingLeftTime;
    int patientCNT = 0;
    int waitingSum = 0;
};

Patient* createPatient();
WaitingQueue* createWaitingQueue();
void enqueue(WaitingQueue* q, Patient* p);
Patient* dequeue(WaitingQueue* q);
int queueCnt(WaitingQueue* q);
void assignPatient(Doctor* d, WaitingQueue* q);
void addWaitingTime(WaitingQueue* q);
void useCureTime(Doctor* d);
void givesDoctorWork(Doctor* d, WaitingQueue* q);
void leftPatientCure(Doctor* d);
void printTime();
void printStatus(Doctor* d);

int main(){
    srand(time(NULL));
    Doctor doctors[3];
    printf("병원을 오픈할려면 엔터를 눌러주세요.\n");
    getchar();
    printTime();
    printf("병원이 오픈했습니다.\n");
    WaitingQueue* queue = createWaitingQueue();
    int randomPatientComeTime = rand()%3+1;
    int randomPatientComeFirst = rand()%6+5;
    for(int i=0;i<randomPatientComeFirst;i++) enqueue(queue, createPatient());
    for(int i=0;i<3;i++) assignPatient(&doctors[i], queue);
    while(clocktime<240){
        clocktime++;
        addWaitingTime(queue);
        randomPatientComeTime--;
        if(!randomPatientComeTime){
            enqueue(queue, createPatient());
            randomPatientComeTime = rand()%3+1;
        }
        useCureTime(doctors);
        givesDoctorWork(doctors, queue);
        if(!(clocktime%60)){
            printTime();
            printf("정각이 되었습니다. 중간점검을 출력합니다.\n");
            printStatus(doctors);
            printTime();
            printf("계속하시려면 엔터를 눌러주세요.\n");
            getchar();
        }
    }
    printTime();
    printf("병원 영업시간이 종료했습니다. 남은 환자들을 치료합니다.\n");
    while(queueCnt(queue)){
        clocktime++;
        addWaitingTime(queue);
        useCureTime(doctors);
        givesDoctorWork(doctors, queue);
    }
    leftPatientCure(doctors);
    printTime();
    printf("모든 환자를 치료했습니다. 최종 결과를 출력합니다.\n");
    printStatus(doctors);
    getchar();
    free(queue);
    return 0;
}

Patient* createPatient(){
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->patNum = patNextNum++;
    newPatient->cureTime = rand()%10+1;
    newPatient->waitingTime = 0;
    newPatient->next = NULL;
    printTime();
    printf("환자%d이(가) 병원에 왔습니다.\n", newPatient->patNum);
    return newPatient;
}

WaitingQueue* createWaitingQueue(){
    WaitingQueue* newQueue = (WaitingQueue*)malloc(sizeof(WaitingQueue));
    newQueue->head = newQueue->tail = NULL;
    return newQueue;
}

void enqueue(WaitingQueue* q, Patient* p){
    if(queueCnt(q)==0){
        q->head = q->tail = p;
        return;
    }
    q->tail->next = p;
    q->tail = p;
}
Patient* dequeue(WaitingQueue* q){
    if(queueCnt(q)==0) return NULL;
    Patient* outP = q->head;
    q->head = q->head->next;
    return outP;
}
int queueCnt(WaitingQueue* q){
    int cnt = 0;
    Patient* count = q->head;
    while(count){
        cnt++;
        count = count->next;
    }
    //if(!cnt) q->tail = NULL;
    return cnt;
}
void assignPatient(Doctor* d, WaitingQueue* q){
    Patient* newPatient = dequeue(q);
    if (newPatient==NULL) return;
    d->curingLeftTime = newPatient->cureTime;
    d->waitingSum += newPatient->waitingTime;
    (d->patientCNT)++;
    printTime();
    printf("환자%d이(가) 진료실에 들어갔습니다. 치료시간은 %d분 예상입니다. 대기시간은 %d분 입니다.\n",
            newPatient->patNum, newPatient->cureTime, newPatient->waitingTime);
    free(newPatient);
    newPatient=NULL;
}
void addWaitingTime(WaitingQueue* q){
    Patient* p = q->head;
    while(p){
        (p->waitingTime)++;
        p = p->next;
    }
}
void useCureTime(Doctor* d){
    for(int i=0;i<3;i++){
        if((d+i)->curingLeftTime!=0){
            ((d+i)->curingLeftTime)--;
            ((d+i)->curingTimeSum)++;
        }
    }
}
void givesDoctorWork(Doctor* d, WaitingQueue* q){
    for(int i=0;i<3;i++) if((d+i)->curingLeftTime==0) assignPatient(d+i, q);
}
void leftPatientCure(Doctor* d){
    int lefttime = 0;
    for(int i=0;i<3;i++){
        ((d+i)->curingTimeSum)+=((d+i)->curingLeftTime);
        if(lefttime<((d+i)->curingLeftTime)) lefttime = (d+i)->curingLeftTime;
    }
    clocktime += lefttime;
}
void printTime(){
    printf("[오후 %d시 %02d분] ", 2+clocktime/60, clocktime % 60);
}
void printStatus(Doctor* d){
    // 총 내원 환자수, 1인 평균 대기 시간, 각 의사별 진료 시간 출력
    int totalP = 0;
    double waiting = 0;
    for(int i=0;i<3;i++){
        totalP += (d+i)->patientCNT;
        waiting += (d+i)->waitingSum;
    }
    waiting /= (double)totalP;
    printf("=============================\n");
    printf("총 내원 환자수 : %d명\n", patNextNum-1);
    printf("1인 평균 대기 시간 : %lf분\n", waiting);
    for(int i=0;i<3;i++) printf("의사%d의 진료 시간 : %d분\n", i+1, (d+i)->curingTimeSum);
    printf("=============================\n");
}