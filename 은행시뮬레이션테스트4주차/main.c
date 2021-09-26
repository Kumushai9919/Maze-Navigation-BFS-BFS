//
//  main.c
//  은행시뮬레이션테스트4주차
//
//  Created by Kumushai Nazhimidin kyzy on 2021/09/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_QUEUE_SIZE 100
typedef struct BankCustomer {
    int id;
    int tArrival;
    int tService;
} Customer;

typedef Customer Element;

Element data[MAX_QUEUE_SIZE];

int front, rear;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

void init_queue() {
    front = rear = 0;
}
int is_empty() {
    return front == rear;
}
int is_full() {
    return front == (rear + 1) % MAX_QUEUE_SIZE;
}
int size() {
    return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void enqueue(Element val)
{
    if (is_full())
        error("큐 포화 에러");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue()
{
    if (is_empty())
        error("큐 공백 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element peek()
{
    if (is_empty())
        error("큐 공백 에러");
    return data[(front + 1) % MAX_QUEUE_SIZE];
}

int nSimulation;
double probArrival;
int tMaxService;
int totalWaitTime;
int nCustomers;
int nServedCustomers;

double rand0to1(){
    return rand()/(double)RAND_MAX;
}
void insert_customer(int arrivalTime){
    Customer a;
    a.id = ++nCustomers;
    a.tArrival = arrivalTime;
    a.tService = (int)(tMaxService*rand0to1()) + 1;
    printf("   고객 %d 방문 (서비스 시간: %d분)\n", a.id, a.tService);
    enqueue(a);
}
void read_sim_params(){
    printf("시뮬레이션 할 최대 시간 (예:10) = ");
    scanf("%d", &nSimulation);
    printf("단위시간에 도착하는 고객 수 (예:0.5) = ");
    scanf("%lf", &probArrival);
    printf("한 고객에 대한 최대 서비스 시간 (예:5) = ");
    scanf("%d", &tMaxService);
    printf("====================================================\n");
}
void run_simulation(){
    Customer a;
    int clock = 0;
    int serviceTime = -1;
    init_queue();
    nCustomers = totalWaitTime = nServedCustomers = 0;
    while(clock<nSimulation){
        clock++;
        printf("현재시각 = %d\n", clock);
        if(rand0to1() > probArrival)
            insert_customer(clock);
        if(serviceTime > 0)
            serviceTime--;
        else{
            if(is_empty()) continue;
            a = dequeue();
            nServedCustomers++;
            totalWaitTime += clock - a.tArrival;
            printf(" 고객 %d 서비스 시작 (대기시간:%d분)\n", a.id, clock - a.tArrival);
            serviceTime = a.tService - 1;
        }
    }
}
void print_result(){
    printf("=================================================\n");
    printf(" 서비스 받은 고객수 = %d\n", nServedCustomers);
    printf(" 전체 대기 시간 = %d분\n", totalWaitTime);
    printf(" 서비스고객 평균대기시간 = %-5.2f분\n", (double)totalWaitTime / nServedCustomers);
    printf(" 현재 대기 고객 수 = %d\n", nCustomers - nServedCustomers);
}
int main(){
    printf(" 학번: 202068060 이름: 쿠무샤이\n");
    srand((unsigned int)time(NULL));
    read_sim_params();
    run_simulation();
    print_result();
}
 
