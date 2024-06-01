#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 30

typedef struct {
  char my_array[MAX_SIZE];
  int current;
  int end;
} ADT;

void command_notice();
void create(ADT *array);
void insert(ADT *array, char data);
void traverse_front(ADT *array);
void traverse_rear(ADT *array);
void cursor_next(ADT *array);
void cursor_previous(ADT *array);
void delete(ADT *array);
void get_data(ADT *array);
void replace(ADT *array, char data);
void empty(ADT *array);
void move(ADT *array, int new_position);
int data_count(ADT *array);
void print(ADT *array);
void ascending_order(ADT *array); //오름차순 정렬-추가기능1
void descending_order(ADT *array); //내림차순 정렬-추가기능2
void remain_seat(ADT *array);//배열에 넣을 수 있는 자리가 얼마나 남아있는지 알려주는 기능-추가기능3

int main() {
  command_notice();

  ADT my_array ;
  create(&my_array);
  
  while (1) {
    char request[20];
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
          insert(&my_array,request[i+1]);
          i++;
          break;
        case '<':
          traverse_front(&my_array);
          break;
        case '>':
          traverse_rear(&my_array);
          break;
        case 'N':
          cursor_next(&my_array);
          break;
        case 'P':
          cursor_previous(&my_array);
          break;
        case '-':
          delete(&my_array);
          break;
        case '@':
          get_data(&my_array);
          break;
        case '=':
          replace(&my_array, request[i+1]);
          break;
        case 'E':
          empty(&my_array);
          break;
        case 'M':
          if (isdigit(request[i+1])) {
            int num = request[i+1] - '0';
            move(&my_array, num);
          } else if (request[i+1]=='N')
          {
            int num = my_array.current+1;
            move(&my_array, num);
            my_array.current=my_array.current-1;
          } else if (request[i+1]=='P')
          {
            int num=my_array.current-1;
            move(&my_array, num);
            my_array.current=my_array.current+1;
          } else if (request[i+1]=='n')
          {
            int num=data_count(&my_array);
            move(&my_array, num);
            my_array.current=my_array.end-1;
          }
          break;
        case 'A':
          ascending_order(&my_array);
          break;
        case 'D':
          descending_order(&my_array);
          break;
        case 'R':
          remain_seat(&my_array);
          break;
        case 'L':
          break;
          
        default:
          break;
      }
    }
    print(&my_array);
  }
  return 0;
}



void create(ADT *array) {
  for (int i = 0; i < MAX_SIZE; i++) {
        array->my_array[i] = 0;
    }
  array->current=-1;
  array->end=0;
}

void insert(ADT *array, char data) {
  if (array->end == MAX_SIZE) {
    printf("배열이 가득 찼습니다.\n");
    return;
  }
  if (array->current==array->end-1) {
    array->my_array[array->current+1]=data;
  } else {
    for (int j = array->end ; j > (array->current) ; j--){
      array->my_array[j]=array->my_array[j-1];
    }
    array->my_array[array->current+1]=data; 
  }
  array->end++;
  array->current++;
}

void traverse_front(ADT *array) {
  array->current=0;
}

void traverse_rear(ADT *array) {
  array->current=array->end-1;
}

void cursor_next(ADT *array) {
  if (array->current>=array->end) {
    printf("커서 위치가 배열을 벗어났습니다.");
  } else {
    array->current++;
  }
}

void cursor_previous(ADT *array) {
  if (array->current==0) {
    printf("커서 위치가 배열을 벗어났습니다.");
  } else {
    array->current--;
  }
}

void delete(ADT *array) {
  for (int i=array->current ; i<MAX_SIZE ; i++){
    array->my_array[i]=array->my_array[i+1];
  }
  array->end--;
  if (array->my_array[array->current]==0) {
    array->current=0;
  }
}

void get_data(ADT *array) {
  if(array->current >= 0 && array->current < array->end) {
    printf("Return %c\n", array->my_array[array->current]);
  }
}

void replace(ADT *array, char data) {
  if(array->current >= 0 && array->current < array->end) {
    array->my_array[array->current] = data;
  }
}

void empty(ADT *array) {
  for (int i = 0; i < MAX_SIZE; i++) {
        array->my_array[i] = 0;
    }
  array->current=-1;
  array->end=0;
}

void move(ADT *array, int new_position) {
  if (new_position < 0 || new_position > array->end) {
    printf("이동할 수 없는 위치입니다.\n");
    return;
  }

  char variable=array->my_array[array->current];
  if ( (array->current) < new_position ){
    for (int i=array->current; i <= new_position ; i++) {
      array->my_array[i]=array->my_array[i+1];
    }
  } else {
    for (int i=array->current; i > new_position ; i--) {
      array->my_array[i]=array->my_array[i-1];
    }
  }
  array->my_array[new_position]=variable;
  array->current=new_position; 
  return;
}

void print(ADT *array) {
  if (array->end==0) {
    printf("Empty Array\n");
  } else {
    printf("*my_array = [");
    for (int i=0 ;i<array->end+1;i++) {
    printf("%c",array->my_array[i]);
    }
    printf("]\n");
    printf("*현재 위치 : %d번째 인덱스의 값 [%c]\n", array->current, array->my_array[array->current]);
  }
}

int data_count(ADT *array) {
  return array->end-1;
}

void ascending_order(ADT *array) {
  char t ;
  for (int j=0 ; j < array->end-1 ; j++) {
    for ( int i=0 ; i < array->end-1; i++){
      if (array->my_array[i] > array->my_array[i+1]) {
        t=array->my_array[i];
        array->my_array[i]=array->my_array[i+1];
        array->my_array[i+1]=t;
      }
    }
  }
  array->current=array->end-1;
}

void descending_order(ADT *array) {
  char t ;
  for (int i=0 ; i < array->end-1 ; i++) {
    for ( int j=0 ; j < array->end-1; j++){
      if (array->my_array[j] < array->my_array[j+1]) {
        t=array->my_array[j];
        array->my_array[j]=array->my_array[j+1];
        array->my_array[j+1]=t;
      }
    }
  }
  array->current=array->end-1;
}

void remain_seat(ADT *array) {
  int seat = MAX_SIZE - array->end;
  printf("The number of ramaining seat : %d \n", seat);
}

void command_notice() {
  char* items[18] = { "insert", "delete", "trverse_front", "traverse_rear", "get_data", "replace", "empty", 
                    "move", "move end", "move prev", "move next", "print", "prev", "next", "ascending_sort", "descending_sort", "remain_seat", "quit"};
  char* icons[18] = { "+(data)", "-", "<", ">", "@", "=(data)", "E", 
                    "M(position)", "Mn", "MP", "MN", "L", "P", "N", "A", "D", "R", "Q"};
  int len=sizeof(icons)/sizeof(icons[0]);
  printf("----------- command notice -----------\n\n"); 
  for (int i = 0; i < len; i++) {
    printf("%-20s: %s\n", items[i], icons[i]);
  }
  printf("\n");
  printf("---------------------------------------\n");
}