//
//  main.c
//  미로탐색BFS
//
//  Created by Kumushai Nazhimidin kyzy on 2021/09/25.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
    int x;
    int y;
}Location2D;

typedef Location2D Element;
Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void init_deque() {
    front = rear = 0;
}
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
int is_empty() {
    return (front == rear);
}
int size(){
    return (rear-front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
}
int is_full() {
    return ((rear+1)%MAX_QUEUE_SIZE == front);
}
void print_queue(char msg[]) {
    printf("%s[%d] = ", msg, size());
    
    if (!is_empty()) {
        int i = front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf(" %d ", data[i]);
            if (i == rear){
                break;
            }
        } while (i != front);
    }
    printf("\n");
}

void add_rear(Element item) {
    if (is_full()) {
        error("큐 포화 상태 !!");
    }
    
    rear = (rear+1)%MAX_QUEUE_SIZE;
    data[rear] = item;
}
Element delete_front() {
    if (is_empty())
        error("큐 공백 상태 !!");
    
    front = (front+1)%MAX_QUEUE_SIZE;
    
    return data[front];
}
Element get_front() {
    if (is_empty())
        error("큐 공백 상태 !!");
    
    return data[(front+1)%MAX_QUEUE_SIZE];
}
void add_front(Element val) {
    if (is_full())
        error("큐 포화 상태 !!");
    
    data[front] = val;
    front=(front-1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
Element delete_rear() {
    int prev = rear;
    
    if (is_empty())
        error("큐 공백 상태 !!");
    
    rear = (rear-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
    
    return data[prev];
}
Element get_rear() {
    if (is_empty())
        error("큐 공백 상태 !!");
    
    return data[rear];
}

#define MAZE_SIZE 6

char map[MAZE_SIZE][MAZE_SIZE] = {
    { '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' },
};
Location2D getLocation2D(int x, int y) {
    Location2D p;
    p.x = x;
    p.y = y;
    return p;
}
int is_valid(int x, int y) {
    if (x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE) return 0;
    else return map[y][x] == '0' || map[y][x] == 'x';
}
int DFS()
{
    int x, y;
    Location2D here;
    
    init_deque();
    add_rear(getLocation2D(0, 1));
    printf(" DFS: ");
    while (is_empty() == 0) {
        here = delete_rear();
        printf("(%2d,%2d)", here.x, here.y);
        x = here.x;
        y = here.y;
        if (map[y][x] == 'x') return 1;
        else {
            map[y][x] = '.';
            if (is_valid(x-1, y)) add_rear(getLocation2D(x-1, y));
            if (is_valid(x+1, y)) add_rear(getLocation2D(x+1, y));
            if (is_valid(x, y-1)) add_rear(getLocation2D(x, y-1));
            if (is_valid(x, y+1)) add_rear(getLocation2D(x, y+1));
        }
    }
    return 0;
}

int BFS()
{
    int x, y;
    Location2D here;
    
    init_deque();
    add_rear(getLocation2D(0, 1));
    printf(" BFS: ");
    while (is_empty() == 0) {
        here = delete_front();
        printf("(%2d,%2d)", here.x, here.y);
        x = here.x;
        y = here.y;
        if (map[y][x] == 'x') return 1;
        else {
            map[y][x] = '.';
            if (is_valid(x - 1, y)) add_rear(getLocation2D(x - 1, y));
            if (is_valid(x + 1, y)) add_rear(getLocation2D(x + 1, y));
            if (is_valid(x, y - 1)) add_rear(getLocation2D(x, y - 1));
            if (is_valid(x, y + 1)) add_rear(getLocation2D(x, y + 1));
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    printf(" 학번: 202068060 이름: 쿠무샤이\n");
//    printf("->%s\n", DFS() ? "성공" : "실패");
        printf("->%s\n", BFS() ? "성공" : "실패");
    
}
