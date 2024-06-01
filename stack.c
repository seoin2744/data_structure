#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 학기말에 다시 제출해야됨.

#define MAX_SIZE 6

typedef struct Stack {
  char arr[MAX_SIZE];
  int top;
} ADT;

void create(ADT *stk);
void push(ADT *stk, char element);
int pop(ADT* stk);
void print(ADT *stk);
void peek(ADT *stk);
void is_Full(ADT* stk);
int element_count(ADT* stk);
void is_member(ADT* stk, char element);
void top(ADT* stk);
void clear(ADT* stk);
void replace(ADT *stk, char new_element);
void remain_stack(ADT *stk);//스택에 넣을 수 있는 자리가 얼마나 남아있는지 알려주는 기능 - 추가기능1
void is_empty(ADT* stk); //스택이 비어있는지 - 추가기능2
void stack_print(ADT* stk); //스택처럼 프린트 - 추가기능3


int main() {
  ADT my_stack;
  create(&my_stack);
  char value;
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
          push(&my_stack, request[i+1]);
          i++;
          break;
        case '-':
          printf("Return : ");
          printf("%c", pop(&my_stack));
          printf("\n");
          break;
        case 'L':
          break;
        case 'P':
          peek(&my_stack);
          break;
        case 'F':
          is_Full(&my_stack);
          break;
        case '#':
          printf("%d\n", element_count(&my_stack));
          break;
        case 'T':
          top(&my_stack);
          break;
        case '?':
          is_member(&my_stack, request[i+1]);
          break;
        case '=':
          replace(&my_stack, request[i+1]);
          break;
        case 'C':
          clear(&my_stack);
          break;
        case 'R':
          remain_stack(&my_stack);
          break;
        case 'E':
          is_empty(&my_stack);
          break;
        case 'S':
          stack_print(&my_stack);
          break;
        default:
          if ('1' <= request[i] && request[i] <= '9' && request[i+1] == '-') {
            printf("Return : ");
					  for (int j=0; j<request[0] - '0' ; j++) {
              if (element_count(&my_stack) > 0) {
                printf("%c ", pop(&my_stack));
              } else {
                break; // 스택이 비었다면 더 이상 pop하지 않고 중단
              }
            }
            printf("\n");
				  }
          i++;
          break;
      }
    }
    print(&my_stack);
  }
  return 0;
}

void create(ADT *stk) {
  stk->top=-1;
}

void push(ADT *stk, char element) {
  if (stk->top ==MAX_SIZE-1){
    printf("\nstack overflow\n"); 
    return;
  }
  stk->arr[++stk->top]=element;
}

int pop(ADT* stk) {
  if (stk->top==-1){
    printf("Error (nothing to pop)");
    return 0;
  }
  return stk->arr[(stk->top)--];
}

int element_count(ADT* stk){
  return stk->top +1 ;
}

void print(ADT *stk) {

    if (stk->top == -1) {
        printf("-\n");
    }else {
      ADT tempStack;
	    create(&tempStack);
      int cnt=element_count(stk);
      for (int i=0 ; i < cnt ; i++) {
        push(&tempStack, pop(stk));
      }
      for (int i=0 ; i < cnt ; i++) {
        char temp = pop(&tempStack);
		    printf("%c ", temp);
		    push(stk, temp);
      }

    printf("\n");
    }
}

void peek(ADT *stk) {
  if (stk->top != -1) {
    printf("%c", stk->arr[stk->top]);
  } else {
    printf("Stack is empty");
  }
  printf("\n");
}

void is_Full(ADT* stk) {
    printf((stk->top == MAX_SIZE-1) ? "True\n" : "False\n");
}

void is_member(ADT* stk, char element) {
  for (int i = 0; i <= stk->top; i++) {
        if (stk->arr[i] == element) {
            printf("True\n");
          return;
        }
    }
    printf("False\n");
}

void top(ADT* stk){
  if (stk->top != -1) {
    printf("( %d , %c )\n", (stk->top)+1, stk->arr[stk->top]);
  } else {
    printf("Stack is empty\n");
  }
}

void clear(ADT* stk) {
  int count=element_count(stk);
  for (int i=0 ; i<count; i++){
    pop(stk);
  }
}

void replace(ADT *stk, char new_element) {
  stk->arr[stk->top] = new_element;
}

//추가기능1
void remain_stack(ADT *stk){
  int index = MAX_SIZE - stk->top;
  printf("The number of ramaining stack : %d \n", index-1);
}

//추가기능2
void is_empty(ADT* stk) {
  printf((stk->top == -1) ? "True\n" : "False\n");
}

//추가기능3
void stack_print(ADT* stk) {
  printf("\n\n");
  if (stk->top == -1) {
      printf("ㅣ   ㅣ\n");
      printf("ㅣ   ㅣ\n");
      printf("ㅣ   ㅣ\n");
      printf("ㅣ   ㅣ\n");
      printf("ㅣ   ㅣ\n");
      printf("ㅣ   ㅣ\n");
      printf("ㅣ---ㅣ\n");
  }else {
      if ((stk->top != MAX_SIZE-1)) {
        int cnt= MAX_SIZE - (stk->top);
        for (int k=0;k<cnt-1;k++){
          printf("ㅣ   ㅣ\n");
        }
      }
      for (int i = stk->top; i >= 0; i--) {
            printf("ㅣ %c ㅣ\n", stk->arr[i]);
        }
      printf("ㅣ---ㅣ\n\n");
  }
}
