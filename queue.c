#include <stdio.h>
#include <string.h>
#define MAX_SIZE 7

typedef struct Queue {
  int front;
  int rear; 
  char data[MAX_SIZE];
} ADT;

void command_notice();
void create(ADT *q);
void enqueue(ADT *q , int new_data);
void print(ADT *q);
void peek(ADT *q); 
void dequeue(ADT *q);
int is_full(ADT *q);
int data_count(ADT *q);
int head(ADT *q);
int tail(ADT *q);
int is_empty(ADT *q);
void is_member(ADT *q, char data);
void replace(ADT *q, char data);
void clear(ADT* q);
void Queue_print(ADT *q); //추가 기능 1 - 큐 모양으로 프린트해줌.
void Remain_Queue(ADT *q); //추가 기능 2 - 큐에 남아있는 자리 개수를 알려줌.
void number_index(ADT *q , char data); //추가 기능 3 - 찾고 싶은 값의 자리(인덱스+1)를 알려줌.

int main() {
  command_notice();

  ADT my_queue;
  create(&my_queue);
  int value;
  char request[20];
  
  while (1) {
    printf("=> ");
    fgets(request, sizeof(request), stdin);
    if (request[0]=='Q') {
      printf("The end\n");
      break; 
    }

    int length=strlen(request);

    for (int i=0;i<length;i++){
      switch (request[i]) {
        case '+':
          enqueue(&my_queue, request[i+1]);
          i++;
          break;
        case '-':
          dequeue(&my_queue);
          break;
        case 'L':
          break;
        case 'P':
          peek(&my_queue);
          break;
        case 'F':
          value=is_full(&my_queue);
          if (value == 0) {
            printf("True\n");
          } else {
            printf("False\n");
          }
          break;
        case 'E':
          value=is_empty(&my_queue);
          if (value == 0) {
            printf("True\n");
          } else {
            printf("False\n");
          }
          break;
        case '#':
          printf("%d\n", data_count(&my_queue));
          break;
        case 'H':
          printf("%d\n", head(&my_queue));
          break;
        case 'T':
          printf("%d\n", tail(&my_queue));
          break;
        case '?':
          is_member(&my_queue, request[i+1]);
          break;
        case '=':
          replace(&my_queue, request[i+1]);
          break;
        case 'C':
          clear(&my_queue);
          break;
        case '@':
          Queue_print(&my_queue);
          break;
        case 'R':
          Remain_Queue(&my_queue);
          break;
        case 'N':
          number_index(&my_queue, request[i+1]);
          break;
        default:
          if ('1' <= request[i] && request[i] <= '9' && request[i+1] == '-') {
            for (int j = (my_queue.front) +1; j < j + (request[i] - '0') ; j++) {
              if (data_count(&my_queue) > 0) {
                dequeue(&my_queue);
              } else {
                break;
              }
            }
            printf("\n");
          }
          i++;
          break;
      }
    }
    print(&my_queue);
  }
  return 0;
}

void command_notice() {
  char* items[15] = { "enqueue", "print", "peek", "dequeue", "is_full", "data_count", "head", 
                    "tail", "is_empty", "is_member", "replace", "clear", "Queue_print", "Remain_Queue", "number_index"};
  char* icons[15] = { "+(data)", "L", "P", "-", "F", "#", "H", 
                    "T", "E", "?(data)", "=(data)", "C", "@", "R", "N"};
  int len=sizeof(icons)/sizeof(icons[0]);
  printf("----------- command notice -----------\n\n"); 
  for (int i = 0; i < len; i++) {
    printf("%-20s: %s\n", items[i], icons[i]);
  }
  printf("\n");
  printf("---------------------------------------\n");
}


void create(ADT *q) {
  q->front = -1; 
  q->rear = -1;
}

void enqueue(ADT *q, int new_data){
  if (q->rear == MAX_SIZE - 1) {
    if (q->front==q->rear) { 
      q->front = -1;  
      q->rear = -1;  
    } else {
      printf("Error: Queue is full\n");
    }
  }

  q->rear++;
  q->data[q->rear] = new_data;
}

void dequeue(ADT *q) {
  if (q->front==q->rear){
    printf("Error(nothing to dequeue)\n");
  } else {
    printf("Return : %c \n", (q->data[q->front+1]));
    q->front++;
  }
}

void print(ADT *q){
  if (q->front==q->rear) {
    printf("Empty Queue\n");
  } else {
    for (int i = (q->front) +1 ;i< ((q->rear)+1); i++) {
    printf("%c ",q->data[i]);
    }
    printf("\n");
  }
}

void peek(ADT *q){ 
  if (q->front==q->rear){
    printf("Error (Queue is empty)\n");
  } else {
    printf("%c\n", q->data[q->front+1]);
  }
}

int is_full(ADT *q) { 
  if ((q->rear == MAX_SIZE -1) && (MAX_SIZE - ((q->rear)-(q->front)) == 0)) {
    return 0;
  } else {
    return 1;
  }
  
}

int data_count(ADT* q){
  int count = (q->rear) - (q->front);
  return count;
}

int head(ADT *q) {
  return q->front +2;
}

int tail(ADT *q) { 
  return q->rear+1;
}

int is_empty(ADT *q) {
  if (q->front==q->rear) {
    return 0;
  } else {
    return 1;
  }
} 

void is_member(ADT *q, char data){
  int found ;
  for ( int i = (q->front) +1 ; i <= (q->rear) ; i++) {
      if ( (q->data[i]) == data) {
          found = 1;
      }
  }
  if (found) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

void replace(ADT *q, char data) {
  q->data[q->rear] = data;
}

void clear(ADT* q) {
  int count=data_count(q);
  for ( int i = (q->front) +1 ; i<count; i++){
    q->front++;
  }
  q->front = q->rear = -1;
}

void Queue_print(ADT *q) {
  printf("\n\n");
  printf("my_Queue : \n\n");
  if (q->front == q->rear) {
    printf("ㅣㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅣ\n");
    printf("ㅣ  ㅣ  ㅣ  ㅣ  ㅣ  ㅣ  ㅣ  ㅣ\n");
    printf("ㅣㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅣ\n");
  }else {
    printf("ㅣㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅣ\n");
    printf("ㅣ");
    for (int i=0 ; i<q->front+1; i++) {
      printf("  ㅣ");
    }
    for (int j=q->front+1 ; j<q->rear+1; j++) {
      printf(" %cㅣ",q->data[j]);
    }
    for (int k=q->rear+1 ; k<MAX_SIZE; k++) {
      printf("  ㅣ");
    }
    printf("\nㅣㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅣ");
  }
  
  printf("\n\n");
}

void Remain_Queue(ADT *q) {
  int cnt = MAX_SIZE - data_count(q);
  printf("The number of ramaining Queue : %d \n", cnt);
}

void number_index(ADT *q, char data) {
  for ( int i = (q->front) +1 ; i <= (q->rear) ; i++) {
      if ( (q->data[i]) == data) {
          printf( "%d번 자리입니다.\n", i+1);
      }
  }
}