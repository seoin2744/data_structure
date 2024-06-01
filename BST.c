#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
  int key;
  struct _Node *left;
  struct _Node *right;
} Node;

typedef struct ADT {
  Node* root;
} BST;

void command_notice();
void create(BST *my_BST, int value);
Node* insert_node(BST *my_BST, int new_node);
void printNode(Node *current);
void print(BST *my_BST);
void inorder_traversal(Node* node);
void right_root_left_traversal(Node* node);
void get_min(BST *my_BST);
void get_max(BST *my_BST);
Node* find_node(BST *my_BST, int node_value);
void find_route(BST *my_BST, int value);
Node* delete_node(BST *my_BST, int node);
int height(Node *node);
void get_right_child(BST *my_BST, Node *node);
void get_left_child(BST *my_BST, Node *node);
int count_nodes(Node *node);
int count_node(BST *my_BST);
void clear_Node(Node* node);
void clear(BST* my_BST);
void root_node(BST* my_BST); // 추가 ADT1
void is_empty(BST *tree); // 추가 ADT2
void print_tree_structure(Node *node, int space); // 추가 ADT3

int main() {
  command_notice();
  BST *my_BST = malloc(sizeof(BST));
  my_BST->root = NULL;
  char request[30];
  char cmd;
  int value;

  while (1) {

    printf("=> ");
    fgets(request, sizeof(request), stdin);
    int length=strlen(request);

    
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n') {
        request[len - 1] = '\0';
    }
    if (request[0]=='Q') {
      printf("The end\n");
      break; 
    }

    if (sscanf(request, "%c%d", &cmd, &value) == 2) { 
        switch (cmd) {
          Node* result_node = NULL;
          case 'F': 
            result_node= find_node(my_BST,value);
            if (result_node == NULL ){
              printf("Error : Not Exist!\n");
            } else {
              find_route(my_BST, value);
            }
            break;
          case '+': 
            if (my_BST==NULL){
              create(my_BST,value);
            } else {
              insert_node(my_BST, value);
            }
            break;
          case '-': 
            delete_node(my_BST,value);
            break;
        }
    } else if (sscanf(request, "%c(%d)", &cmd, &value) == 2) { 
        Node* node = NULL;
        switch (cmd) {
          case 'G': 
              node = find_node(my_BST, value);
              get_right_child(my_BST, node);
            break; 
          case 'L': 
              node = find_node(my_BST, value);
              get_left_child(my_BST, node);
            break; 
        }
    } else { 
        switch (cmd) {
          case 'P':
            break;
          case 'I':
            inorder_traversal(my_BST->root);
            printf("\n");
            break;
          case 'R':
            right_root_left_traversal(my_BST->root);
            printf("\n");
            break;
          case 'N':
            get_min(my_BST);
            break;
          case 'X':
            get_max(my_BST);
            break;
          case 'H':
            printf("%d\n",height(my_BST->root));
            break;
          case '#':
            printf("%d\n",count_node(my_BST));
            break;
          case 'E':
            is_empty(my_BST);
            break;
          case '@':
            root_node(my_BST);
            break;
          case 'T':
            print_tree_structure(my_BST->root, 0);
            break;
          case 'C':
            clear(my_BST);
            break;
          default :
          break;
        }
    }
    print(my_BST);
  }
  return 0;
}

void create(BST *my_BST, int value) {
  Node *new_root=(Node*)malloc(sizeof(Node));
  new_root->key=value;
  new_root->left = new_root->right=NULL;
  my_BST->root=new_root;
}

Node* insert_node(BST *my_BST, int new_node) {
  if (my_BST->root == NULL) {
    create(my_BST, new_node);
    return my_BST->root;
  }

  Node* p = my_BST->root;
  Node* parent = NULL;

  while (p != NULL) {
    parent = p;
    if (p->key == new_node) {
      printf("같은 키가 있습니다.\n");
      return p;
    } else if (p -> key < new_node) {
      p = p -> right;
    } else {
      p = p -> left;
    }
  }

  Node *insert_node=(Node*)malloc(sizeof(Node));
  
  insert_node->key=new_node;
  insert_node->left= insert_node->right=NULL;

  if (parent!=NULL){
    if (parent->key < new_node) {
      parent->right=insert_node;
    } else {
      parent->left=insert_node;
    }
  } 

  return insert_node;
}

void printNode(Node* current) {
	if (current != NULL) printf("%d", current->key);
	else return;

	if (current->left != NULL || current->right != NULL) {
		printf("(");
		printNode(current->left);
		printf(",");
		printNode(current->right);
		printf(")");
	}
}

void print(BST* my_BST) {
	if (my_BST == NULL) printf("No Tree\n");
	else {
		printf("(");
		printNode(my_BST->root);
		printf(")\n");
	}
}

void inorder_traversal(Node* node) {
  if (node == NULL) {
    return ;
  }
  inorder_traversal(node->left);
  printf("%d ", node->key);
  inorder_traversal(node->right);
}

void right_root_left_traversal(Node* node) {
  if (node == NULL) {
    return ;
  }
  right_root_left_traversal(node->right);
  printf("%d ", node->key);
  right_root_left_traversal(node->left);
}

void get_min(BST *my_BST) {
  Node *current = my_BST->root;
  while (current->left != NULL) {
    current = current->left;
  }
  printf("%d\n", current->key);
}

void get_max(BST *my_BST) {
  Node *current = my_BST->root;
  while (current->right != NULL) {
    current = current->right;
  }
  printf("%d\n", current->key);
}

Node* find_node(BST *my_BST, int node_value) {
  Node* p = my_BST->root;
  while (p != NULL){
    if (p->key == node_value) {
      return p;
    } else if (p->key < node_value) {
      p = p->right;
    } else {
      p = p->left;
    }
  }
  return NULL;
}

void find_route(BST *my_BST, int value) {
    if (!my_BST || !my_BST->root) {
        printf("Tree is empty or not initialized.\n");
        return;
    }

    int h = height(my_BST->root);
    int *history = malloc((h + 1) * sizeof(int));
    if (!history) {
        printf("Memory allocation failed\n");
        return;
    }
    int i = 0;

    Node* currentNode = my_BST->root;
    while(currentNode != NULL) {
        if (value == currentNode->key) break;
        else if (value < currentNode->key) {
            currentNode = currentNode->left;
            history[i++] = 1;
        } else {
            currentNode = currentNode->right;
            history[i++] = 2;
        }
    }

    if (currentNode == NULL) {
        printf("ERROR: Such node doesn't exist\n");
    } else {
        printf("Root");
        for (int j = 0; j < i; j++) {
            printf(" > %s", (history[j] == 1) ? "Left" : "Right");
        }
        printf("\n");
    }

    free(history);
}


Node* delete_node(BST *my_BST, int node) {
  Node* p = my_BST->root;
  Node* parent = NULL;
  while ((p!=NULL)&&(p->key!=node)) {
    parent=p;
    if (p -> key < node) {
      p = p -> right;
    } else {
      p = p -> left;
    }
  }
  if (p==NULL) {
    printf("찾는 노드가 없습니다.\n");
    return my_BST->root;
  }

  if (p->left==NULL && p->right==NULL) { //차수가 0
    if (parent==NULL) {
      my_BST->root = NULL;
    } else {
      if ( parent->left ==p ) {
        parent->left = NULL;
      } else {
        parent->right=NULL;
      }
    }
  } else if ( p->left==NULL || p->right==NULL ) { //차수가 1
    Node *child = (p->left != NULL) ? p->left : p-> right ;
    if (parent == NULL) {
      my_BST->root = child;
    } else {
      if (parent->left == p) {
        parent->left = child;
      } else {
        parent->right = child;
      }
    }
  } else {
    Node *succ_parent = p;
    Node *succ = p->right;
    while (succ->left != NULL) {
      succ_parent = succ;
      succ = succ->left;
    }
    p->key=succ->key;
    if (succ_parent->left == succ) {
      succ_parent->left = succ->right;
    } else {
      succ_parent->right=succ->right;
    }
    p=succ;
  }

  free(p);
  return NULL;
}

int height(Node *node) {
    if (node == NULL) {
        return -1; 
    } else {
        int left_height = height(node->left);
        int right_height = height(node->right);

        return (left_height > right_height ? left_height : right_height) + 1; 
    }
}

void get_right_child(BST *my_BST, Node *node) {
  if (my_BST->root==NULL || node == NULL) {
    printf("There is no node or Tree is empty.\n");
    return;
  }
  Node *right_child = node->right;

  if (right_child!=NULL) {
    printf("%d\n", right_child->key);
  } else {
    printf("There is no right child\n");
  }
}

void get_left_child(BST *my_BST, Node *node) {
  if (my_BST->root==NULL || node == NULL) {
    printf("There is no node or Tree is empty.\n");
    return;
  }
  Node *left_child = node->left;

  if (left_child!=NULL) {
    printf("%d\n", left_child->key);
  } else {
    printf("NULL\n");
  }
}

int count_nodes(Node *node) {
    if (node == NULL) {
        return 0; 
    } else {
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }
}

int count_node(BST *my_BST) {
    if (my_BST == NULL || my_BST->root == NULL) {
        return 0;
    } else {
        return count_nodes(my_BST->root); 
    }
}


void clear_Node(Node* node) {
    if (node == NULL) return; 
    
    clear_Node(node->left); 
    clear_Node(node->right); 
    
    free(node);
}

void clear(BST* my_BST) {
    if (my_BST == NULL) return; 
    
    clear_Node(my_BST->root); 
    my_BST->root = NULL;   
}

void root_node(BST* my_BST) {
  printf("%d\n",my_BST->root->key);
}

void is_empty(BST *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("The tree is empty.\n");
    } else {
        printf("The tree is not empty.\n");
    }
}

void print_tree_structure(Node *node, int space) {
    if (node == NULL) {
        printf("%*s-\n", space, "");
        return;
    }
    space += 5;
    print_tree_structure(node->right, space);
    printf("%*s%d\n", space, "", node->key);
    print_tree_structure(node->left, space);
}


void command_notice() {
  char* items[16] = { "insert_node", "print", "inorder_traversal", "right_root_left_traversal", "get_min", "get_max", "find_node", 
                    "delete_node", "height", "get_right_child", "get_left_child", "count_node", "clear", "root_node", "is_empty", "print_tree_structure"};
  char* icons[16] = { "+value", "P", "I", "R", "N", "X", "Fvalue", 
                    "-value", "H", "G(value)", "L(value)", "#", "C", "@", "E", "T"};
  int len=sizeof(icons)/sizeof(icons[0]);
  printf("----------- command notice -----------\n\n"); 
  for (int i = 0; i < len; i++) {
    printf("%-20s: %s\n", items[i], icons[i]);
  }
  printf("\n");
  printf("---------------------------------------\n");
}


