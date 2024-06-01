#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
    char data;
    struct NODE* prev;
    struct NODE* next;
} Node;

typedef struct Deque{
    Node* head;
    Node* tail;
    int size;
} ADT;

void create(ADT* deq);
void emplaceFront(ADT* deq, char data);
void emplaceRear(ADT* deq, char data);
void removeFront(ADT* deq);
void removeRear(ADT* deq);
void getFront(ADT* deq);
void getRear(ADT* deq);
void print(ADT* deq);
int is_empty(ADT* deq);


int main() {
  
  ADT deq;
  create(&deq);
  
  while (1) {
    char request[40];
    printf("=> ");
    fgets(request, sizeof(request), stdin);
    if (request[0]=='Q') {
      printf("The end\n");
      break; 
    }

    int length=strlen(request);

    for (int i=0;i<length;i++){
      char data;
      switch (request[i]) {
        case '+':
         if (request[i+1]=='>') {
          emplaceRear(&deq, request[i+2]);
          i+=2;
         } else if (request[i+1]=='<') {
          emplaceFront(&deq, request[i+2]);
          i+=2;
         } else {
          emplaceRear(&deq, request[i+1]);
          i++;
         }
          break;
        case 'L':
          break;
        case '-':
            if (request[i+1]=='>') {
              removeRear(&deq);
            } else if (request[i+1]=='<') {
              removeFront(&deq);
            }
            i++;
            break;
        case 'E':
          printf("Deque is empty? %s\n", is_empty(&deq) ? "Yes" : "No");
          break;
        case 'F':
          getFront(&deq);
          break;
        case 'R':
          getRear(&deq);
          break;
        default:
          break;
      }
    }
  print(&deq);
  }
  return 0;
}

void create(ADT* deq) {
    deq->head = NULL;
    deq->tail = NULL;
    deq->size = 0;
}

void emplaceFront(ADT* deq, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = deq->head;

    if (deq->head == NULL) { // Empty deque
        deq->tail = newNode;
    } else {
        deq->head->prev = newNode;
    }
    deq->head = newNode;
    deq->size++;
}

void emplaceRear(ADT* deq, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = deq->tail;

    if (deq->tail == NULL) { // Empty deque
        deq->head = newNode;
    } else {
        deq->tail->next = newNode;
    }
    deq->tail = newNode;
    deq->size++;
}

void removeFront(ADT* deq) {
    if (deq->head == NULL) return; // Empty deque

    Node* temp = deq->head;
    deq->head = deq->head->next;

    if (deq->head == NULL) {
        deq->tail = NULL;
    } else {
        deq->head->prev = NULL;
    }

    free(temp);
    deq->size--;
}

void removeRear(ADT* deq) {
    if (deq->tail == NULL) return; // Empty deque

    Node* temp = deq->tail;
    deq->tail = deq->tail->prev;

    if (deq->tail == NULL) {
        deq->head = NULL;
    } else {
        deq->tail->next = NULL;
    }

    free(temp);
    deq->size--;
}

void getFront(ADT* deq) {
    if (deq->head == NULL) {
        printf("Deque is empty. No front element.\n");
    }
    printf("%c\n",deq->head->data);
}

void getRear(ADT* deq) {
    if (deq->tail == NULL) {
        printf("Deque is empty. No rear element.\n");
    }
    printf("%c\n",deq->tail->data); 
}

void print(ADT* deq) {
    Node* current = deq->head;

    if (current == NULL) {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque: ");
    while (current != NULL) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

int is_empty(ADT* deq) {
    return deq->size == 0;
}