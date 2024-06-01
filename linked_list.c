#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct NODE {
  char data;
  struct NODE* next;
} Node;

typedef struct Linked_list {
  Node *head;
  Node *tail;
  Node *cursor;
  int size;
} ADT;

void create(ADT *list);
void print(ADT *list);
void addTail(ADT *list, char data);
void add(ADT *list, char data);
void print(ADT *list);
void get_data(ADT *list);
void traverse_front(ADT *list);
void traverse_rear(ADT *list);
int cursor_next(ADT *list);
int cursor_previous(ADT *list);
void delete(ADT *list);
void replace(ADT *list, char data);
void data_count(ADT *list); 
void is_member(ADT *list, char data);
int clear(ADT *list);
void is_empty(ADT *list);
void addHead(ADT *list, char data);
void move(ADT *list, int num);
void reverse(ADT *list);//추가ADT1
void find_mid(ADT *list);//추가ADT2
void duplicates(ADT *list);//추가ADT3

int main() {
  
  ADT list;
  create(&list);
  
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
         if (list.size==0) {
          addTail(&list,request[i+1]);
         } else {
          add(&list, request[i+1]);
         }
          i++;
          break;
        case 'L':
          break;
        case 'G':
          get_data(&list);
          break;
        case '<':
            traverse_front(&list);
            if (request[i+1]=='+') {
              addHead(&list, request[i+2]);
              i++;
            }
          break;
        case '>':
          traverse_rear(&list);
          break;
        case 'N':
          cursor_next(&list);
          break;
        case 'P':
          cursor_previous(&list);
          break;
        case '-':
          delete(&list);
          break;
        case '=':
          replace(&list, request[i+1]);
          break;
        case '#':
          data_count(&list);
          break;
        case '?':
          is_member(&list, request[i+1]); 
          break;
        case 'C':
          clear(&list); 
          break;
        case 'E':
          is_empty(&list);
          break;
        case 'R':
          reverse(&list);
          break;
        case 'D':
          duplicates(&list);
          break;
        case 'F':
          find_mid(&list);
          break;
        default:
          if (isdigit(request[i])) {
            int num = request[i] - '0';
            move(&list,num-1);
          }
          break;
      }
    }
  print(&list);
  }
  return 0;
}

void create(ADT *list) {
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
    list->size = 0;
}

void addTail(ADT *list, char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->cursor = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
    list->cursor=newNode;
}


void add(ADT *list, char data) {

  if (list->cursor == NULL) { 
        printf("Cursor is not set. Cannot insert in the middle.\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->cursor->next; 

    list->cursor->next = newNode; 

    if (list->cursor == list->tail) { 
        list->tail = newNode;
    }
    list->size++;
    list->cursor=newNode;
}

void addHead(ADT *list, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head; 
    list->head = newNode;
    if (list->tail == NULL) { 
        list->tail = newNode;
    }
    if (list->size == 0) { 
        list->cursor = newNode;
    }
    list->size++;
    cursor_previous(list);
}

void print(ADT *list) {
    Node *current = list->head;
    int position = 0;

    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("My_List: ");
    while (current != NULL) {
        if (current == list->cursor) {
            printf("[%c] ", current->data);
        } else {
            printf("%c ", current->data);
        }
        current = current->next;
        position++;
    }
    printf("\n");
}

void get_data(ADT *list) {
  printf("%c\n", list->cursor->data);
}

void traverse_front(ADT *list) {
  list->cursor = list->head;
}

void traverse_rear(ADT *list) {
  list->cursor = list->tail;
}


int cursor_next(ADT *list) {
  if (list->cursor != NULL && list->cursor->next != NULL) {
    list->cursor = list->cursor->next;
  }
  return 1;
}

int cursor_previous(ADT *list) {
  if (list->cursor != list->head) {
    Node* tem = list->head;
    while (tem != NULL && tem->next != list->cursor) {
      tem = tem->next;
    }
    list->cursor = tem;
    return 1;
  }
  return 0;
}

void delete(ADT *list) {

  if (list->cursor == list->head) {
      Node* Del = list->cursor;
      list->head = list->head->next;
      if (list->head == NULL) {
          list->tail = NULL;
      }
      list->cursor = list->head;
      free(Del);
  } else {
      Node *tem = list->head;
      while (tem != NULL && tem->next != list->cursor) {
          tem = tem->next; 
      }

      Node* Del = list->cursor;
      tem->next = list->cursor->next;

      if (list->cursor == list->tail) {
          list->tail = tem; 
          list->cursor = list->head;
      } else {
          list->cursor = list->cursor->next;
      }

      free(Del);
  }
  list->size--;
}

void replace(ADT *list, char new_data) {
    if (list->head == NULL || list->cursor == NULL) {
        printf("List is empty or cursor is not set.\n");
        return;
    }
    list->cursor->data = new_data;
}

void data_count(ADT *list) {
    Node *current = list->head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("%d\n",count);
}

void is_member(ADT *list, char data) {
    Node *current = list->head;
    int position = 0; 

    while (current != NULL) {
        if (current->data == data) {
            printf("위치 : %d \n", position+1);
            return; 
        }
        current = current->next;
        position++;
    }
}

int clear(ADT *list) {
  list->head = NULL;
  list->tail = NULL;
  list->cursor = NULL;
  list->size = 0;
  return 1;
}

void is_empty(ADT *list) {
  if( clear(list)==1){
    printf("True\n");
  } else {
    printf("No\n");
  }
}

void move(ADT *list, int num) {
     list->cursor=list->head;
  for (int i=0; i<num; i++) {
    cursor_next(list);
  }
}

// 연결 리스트의 순서를 뒤집는 함수
void reverse(ADT *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->tail = list->head;
    list->head = prev;
}

// 연결 리스트에서 중복된 노드를 찾아 인덱스 번호와 값을 출력하는 함수
void duplicates(ADT *list) {
    Node *current = list->head;
    int position = 0;
    while (current != NULL) {
        Node *checker = current->next;
        int checkPos = position + 1;
        while (checker != NULL) {
            if (current->data == checker->data) {
                printf("Duplicate value: %c, Positions: %d and %d\n", current->data, position, checkPos);
            }
            checker = checker->next;
            checkPos++;
        }
        current = current->next;
        position++;
    }
}


// 리스트의 중간 노드를 찾는 함수
void find_mid(ADT *list) {
    Node *slow = list->head;
    Node *fast = list->head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list->cursor = slow;
}
