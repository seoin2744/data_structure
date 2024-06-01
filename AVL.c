#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
  int key;
  int height;
  struct _Node *left;
  struct _Node *right;
  struct _Node *parent;
} Node;

typedef struct ADT {
  Node* root;
} AVL;

int max(int a, int b) {
  return (a > b)? a : b;
}

void create(AVL *my_AVL, int value);
int height(Node *node);
int balance_factor(Node* node);
Node* RR(Node* node);
Node* LL(Node* node);
Node* LR(Node* node);
Node* RL(Node* node);
Node* insert(Node* node, int new_node);
Node* AVLSet(Node* node);
void printNode(Node* current);
void print(AVL* my_AVL);
void inorder_traversal(Node* node);
void right_root_left_traversal(Node* node);
void get_min(AVL *my_AVL);
void get_max(AVL *my_AVL);
int heightTree(AVL *my_AVL);
void heightNode(AVL *my_AVL, int value);
void get_right_child(AVL *my_AVL, Node *node);
void get_left_child(AVL *my_AVL, Node *node);
Node* find_node(AVL *my_AVL, int node_value);
void find_route(AVL *my_AVL, int value);
int count_nodes(Node *node);
int count_node(AVL *my_AVL);
void clear_Node(Node* node);
void clear(AVL* my_AVL);
Node* delete(Node* node, int data);
Node* get_min_subtree(Node* node);

int main() {

  AVL *my_AVL = malloc(sizeof(AVL));
  my_AVL->root = NULL;

  char request[30];
  char cmd;
  int value;

  Node* result_node = NULL;

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
          case 'F': 
            result_node= find_node(my_AVL,value);
            if (result_node == NULL ){
              printf("Error : Not Exist!\n");
            } else {
              find_route(my_AVL, value);
            }
            break;
          case 'B': 
            result_node= find_node(my_AVL,value);
            if (result_node == NULL ){
              printf("Error : Not Exist!\n");
            } else {
              printf("%d\n",balance_factor(result_node));
            }
            break;
          case '+': 
            if (my_AVL->root==NULL){
              create(my_AVL, value);
            } else {
              my_AVL->root = insert(my_AVL->root, value);
            }
            break;
          case 'H': 
            heightNode(my_AVL, value);
            break;
          case 'G': 
            result_node= find_node(my_AVL,value);
            get_right_child(my_AVL, result_node);
            break;
          case 'L': 
            result_node= find_node(my_AVL,value);
            get_left_child(my_AVL, result_node);
            break;
          case '-': 
            result_node= find_node(my_AVL,value);
            delete(result_node,value);
            printf("오른쪽 subtree의 가장 최솟값을 가져옴.\n");
            break;
        }
    } else { 
        switch (cmd) {
          case 'P':
            break;
          case 'I':
            inorder_traversal(my_AVL->root);
            printf("\n");
            break;
          case 'R':
            right_root_left_traversal(my_AVL->root);
            printf("\n");
            break;
          case 'T':
            printf("%d\n", heightTree(my_AVL));
            break;
          case 'N':
            get_min(my_AVL);
            break;
          case 'X':
            get_max(my_AVL);
            break;
          case '#':
            printf("%d\n",count_node(my_AVL));
            break;
          case 'C':
            clear(my_AVL);
            break;
          default :
          break;
        }
    }
    print(my_AVL);
  }
  return 0;
}

void create(AVL *my_AVL, int value) {
  Node *new_root=(Node*)malloc(sizeof(Node));

  new_root->key = value;
  new_root->left = new_root->right = NULL;
  new_root->height = 0;
  new_root->parent = NULL; 
  my_AVL->root = new_root;
}

int height(Node *node) {
  if (node == NULL) {
      return 0; 
  } else {
      int left_height = height(node->left);
      int right_height = height(node->right);

      node->height = (left_height > right_height ? left_height : right_height) + 1 ;
      return node->height; 
  }
}

int heightTree(AVL *my_AVL) {
  return my_AVL->root->height -1;
}

void heightNode(AVL *my_AVL, int value) {
	Node* targetNode = find_node(my_AVL, value);
	if (targetNode) printf("%d\n", targetNode->height-1);
}

int balance_factor(Node* node) {
  if (node == NULL){
    return 0;
  }
  return height(node->left) - height(node->right);
}

Node* RR(Node* node) {
    Node* childNode = node->right;
    node->right = childNode->left;
    if (childNode->left != NULL)
        childNode->left->parent = node;

    childNode->left = node;
    childNode->parent = node->parent;
    node->parent = childNode;
    node->height = 1+ max(height(node->left), height(node->right));
    childNode->height = 1+ max(height(childNode->left), height(childNode->right));

    return childNode;
}

Node* LL(Node* node) {
    Node* childNode = node->left;
    node->left = childNode->right;
    if (childNode->right != NULL)
        childNode->right->parent = node;
	
    childNode->right = node;
    childNode->parent = node->parent;
    node->parent = childNode;

    node->height = 1+ max(height(node->left), height(node->right));
    childNode->height = 1+ max(height(childNode->left), height(childNode->right));
	
    return childNode;
}

Node* LR(Node* node) {
    node->left = RR(node->left);
    return LL(node);
}

Node* RL(Node* node) {
    node->right = LL(node->right);
    return RR(node);
}

Node* insert(Node* node, int new_node) {
    if (node == NULL) {
        node = (Node*)malloc(sizeof(Node));
        node->height = 0; 
        node->left = node->right = node->parent = NULL;
        node->key = new_node;
        return node;
    }
    if (new_node < node->key) {
        node->left = insert(node->left, new_node);
        node->left->parent = node;
    } else if (new_node > node->key) {
        node->right = insert(node->right, new_node);
        node->right->parent = node;
    } else {
        return node;
    }
    Node* balancedNode = AVLSet(node);
    return balancedNode;
}

Node* AVLSet(Node* node) {
    if (node == NULL) return NULL;

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = balance_factor(node);

    if (balance > 1 && balance_factor(node->left) >= 0) { // LL Case
        return LL(node);
    }
    if (balance < -1 && balance_factor(node->right) <= 0) { // RR Case
      return RR(node);
    }
    if (balance > 1 && balance_factor(node->left) < 0) { // LR Case
        node->left = RR(node->left);
        return LL(node);
    }
    if (balance < -1 && balance_factor(node->right) > 0) { // RL Case
        node->right = LL(node->right);
        return RR(node);
    }

    return node;
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

void print(AVL* my_AVL) {
	if (my_AVL == NULL) printf("No Tree\n");
	else {
		printf("(");
		printNode(my_AVL->root);
		printf(")\n");
	}
}

Node* find_node(AVL *my_AVL, int node_value) {
  Node* p = my_AVL->root;
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

void find_route(AVL *my_AVL, int value) {
    if (!my_AVL || !my_AVL->root) {
        printf("Tree is empty or not initialized.\n");
        return;
    }

    int h = height(my_AVL->root);
    int *history = malloc((h + 1) * sizeof(int));
    if (!history) {
        printf("Memory allocation failed\n");
        return;
    }
    int i = 0;

    Node* currentNode = my_AVL->root;
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

void get_min(AVL *my_AVL) {
  Node *current = my_AVL->root;
  while (current->left != NULL) {
    current = current->left;
  }
  printf("%d\n", current->key);
}

void get_max(AVL *my_AVL) {
  Node *current = my_AVL->root;
  while (current->right != NULL) {
    current = current->right;
  }
  printf("%d\n", current->key);
}

void get_right_child(AVL *my_AVL, Node *node) {
  if (my_AVL->root==NULL || node == NULL) {
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

void get_left_child(AVL *my_AVL, Node *node) {
  if (my_AVL->root==NULL || node == NULL) {
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

int count_node(AVL *my_AVL) {
    if (my_AVL == NULL || my_AVL->root == NULL) {
        return 0;
    } else {
        return count_nodes(my_AVL->root); 
    }
}

void clear_Node(Node* node) {
    if (node == NULL) return; 
    
    clear_Node(node->left); 
    clear_Node(node->right); 
    
    free(node);
}

void clear(AVL* my_AVL) {
    if (my_AVL == NULL) return; 
    
    clear_Node(my_AVL->root); 
    my_AVL->root = NULL;   
}

Node* delete(Node* node, int data) {
    if (node == NULL) {
        return NULL; 
    }

    if (data < node->key) { 
        node->left = delete(node->left, data);
    } else if (data > node->key) {
        node->right = delete(node->right, data);
    } else {
        if (node->left == NULL || node->right == NULL) { 
            Node* temp = node->left ? node->left : node->right;
            if (temp == NULL) { 
                temp = node;
                node = NULL;
            } else { 
                *node = *temp; 
            }
            free(temp);
        } else { 
            Node* temp = get_min_subtree(node->right);
            node->key = temp->key; 
            node->right = delete(node->right, temp->key); 
        }
    }

    if (node == NULL) {
        return node;
    }

    return AVLSet(node);
}

Node* get_min_subtree(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
