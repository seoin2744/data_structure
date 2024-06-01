#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node* left; 
  int value;
  struct node* right;
} node;


typedef struct tree {
  node* root;
} tree;

void create(tree *my_tree, char root);
node* find(node* root, char value);
node* find_parent(node* root, node* child);
void get_parent(tree* my_tree, char child_value);
void get_child(tree* my_tree, char parent_node);
void insert_node(tree *my_tree, char parent, char* list, int binary);
void get_sibling(tree *my_tree, char Node);
void print(tree* my_tree);
int find_level (node* Node, char value, int level);
int level_of_node (tree* my_tree, char node);
int level_cal(node* root);
int level_of_tree(tree* my_tree);
void delete_node(tree* my_tree, char node);
void get_ancestors(tree* my_tree, char Node);
void find_descendants(node* root);
void get_descendants(tree* my_tree, char Node);
void degree_of_node(tree* my_tree, char Node);
void degree_of_tree(tree* my_tree);
int count(node* root);
void count_node(tree* my_tree);
int get_degree(node* Node);
void degree_of_tree(tree* my_tree);
void insert_sibling(tree* my_tree, char node_value, const char* s_list);
void join_trees(char new_root_value, tree* my_tree, tree* tree2);
void clear_tree(node* root);
void clear(tree* my_tree);



int main() {

  tree my_tree;
  my_tree.root = NULL;
  node* sibling = NULL;
  char request[20];

  tree tree2;
  
  char isBinary;
	printf("Is this tree binary?[y/n] : "); 
	scanf("%c", &isBinary);
  getchar();

  while (1) {
    printf("\n=> ");
    fgets(request, sizeof(request), stdin);
    if (request[0]=='Q') {
      printf("The end\n");
      break; 
    }

    int length=strlen(request);

      switch (request[0]) {
        case '+':
          if (request[1]=='^') {
            create(&my_tree, request[2]);
          } else {
              if (request[1] == '^') {
                create(&my_tree, request[2]);
              } else {
                insert_node(&my_tree, request[1], request+2, (isBinary == 'y'));
              }
          }
          print(&my_tree);
          break;
        case 'S':
            get_sibling(&my_tree, request[2]);
            print(&my_tree);
          break;
        case 'T':
          print(&my_tree);
          break;
        case 'P':
          get_parent(&my_tree, request[2]);
          print(&my_tree);
          break;
        case 'C':
          get_child(&my_tree, request[2]);
          print(&my_tree);
          break;
        case 'L':
          if (request[1]=='(') {
            printf("%d\n",level_of_node(&my_tree, request[2]));
          } else {
            printf("%d\n",level_of_tree(&my_tree));
          }
          print(&my_tree);
          break;
        case '-':
          delete_node(&my_tree, request[1]);
          print(&my_tree);
          break;
        case 'A':
          get_ancestors(&my_tree, request[2]);
          print(&my_tree);
          break;
        case 'D':
          get_descendants(&my_tree, request[2]);
          print(&my_tree);
          break;
        case 'G':
          if (request[1]=='(') {
            degree_of_node(&my_tree, request[2]);
          } else {
            degree_of_tree(&my_tree);
          }
          print(&my_tree);
          break;
        case '#':
          count_node(&my_tree);
          print(&my_tree);
          break;
        case '=':
          if (request[1] == '+') {
            char* start_bracket = strchr(request + 3, '(');
            if (start_bracket != NULL) {
                char* end_bracket = strchr(start_bracket, ')');
                if (end_bracket != NULL) {
                  size_t s_list_length = end_bracket - start_bracket - 1;
                  char* s_list = (char*) malloc(s_list_length + 1);
                  strncpy(s_list, start_bracket + 1, s_list_length);
                  s_list[s_list_length] = '\0'; 
                  insert_sibling(&my_tree, request[2], s_list);
                  free(s_list);
                }
              }
            }
          print(&my_tree);
          break;
        case 'J':
          join_trees(request[2], &my_tree, &tree2);
          break;
        case 'K':
          clear(&my_tree);
          print(&my_tree);
          break;
        default :
          break;
      }
  }
  return 0;
}

void create(tree *my_tree, char root){
  node* new_node = malloc (sizeof(node));

  if (!new_node) {
    printf("ERROR: Memory allocation failed\n");
    return;
  }

  new_node->value = root;
  new_node->left = NULL;
  new_node->right = NULL;

  my_tree->root = new_node;
}

node* find(node* root, char value) {
  if (root==NULL) return NULL;
  if (root->value==value) return root;

  node* find_value= find(root->left, value);
  if (find_value) return find_value;
  return find(root->right, value);
}

node* find_parent(node* root, node* child) {
    if (root == NULL || child == NULL) return NULL;
    node* current = root->left;  

    while (current != NULL) {
        if (current == child) {
            return root; 
        }
        node* sibling = current->right;
        while (sibling != NULL) {
            if (sibling == child) {
                return root;
            }
            sibling = sibling->right; 
        }
        current = current->right; 
    }

    current = root->left;
    while (current != NULL) {
        node* result = find_parent(current, child);
        if (result != NULL) return result; 
        current = current->right;
    }

    return NULL;
}

void get_sibling(tree *my_tree, char Node) {
  if (my_tree->root == NULL) {
        printf("Error. Tree is empty\n");
        return;
  }

  node* targetNode = find(my_tree->root, Node);
  if (targetNode == NULL) {
      printf("No such node exists.\n");
      return;
  }

  if (targetNode == my_tree->root) {
      printf("No sibling. It is the root.\n");
      return;
  }

  node* parent = find_parent(my_tree->root, targetNode);
  if (parent == NULL) {
      printf("Error. Could not find parent node.\n");
      return;
  }

  node* sibling = parent->left;
  if (sibling == targetNode && sibling->right == NULL) {
      printf("No siblings.\n");
      return;
  }

  printf("{");
  int first = 0;
  while (sibling != NULL) {
      if (sibling != targetNode) {
          if (first++) printf(", ");
          printf("%c", sibling->value);
      }
      sibling = sibling->right;
  }
  printf("}\n");
}

void get_parent(tree* my_tree, char child_value){
  node* child= find(my_tree->root, child_value);
  if (child == NULL) {
    printf("Error. Such node doesn't exist.\n");
  } 
  if (child ==my_tree->root) {
    printf("This node is the root. There is no parent node\n");
  }
    
  node* parent= find_parent(my_tree->root, child);
  if ( parent!= NULL ) {
    printf("%c\n", parent->value);
  } else {
    printf("Error. No found parent node.\n");
  }
}

void get_child(tree* my_tree, char parent_node) {
  node* parent= find(my_tree->root, parent_node);
  if (parent == NULL) {
    printf("That node doesn't exist.\n");
  }

  if(parent->left==NULL) {
    printf("There is no child.\n"); 
    return;
  } else {
    node* search = parent->left;
    printf("{%c", search->value);
    search = search->right;
    while (search!=NULL) {
      printf(",%c", search->value);
      search = search->right;
    }
    printf("}\n");
  }  
}

void insert_node(tree *my_tree, char parent, char* c_list, int binary) {
  if (my_tree->root == NULL) {
    printf("root value doesn't exist, tree is not gernerated.\n");
    return;
  }

  node* parent_node = find(my_tree->root, parent);
  if (parent_node == NULL) {
    printf("Error. // No %c\n", parent);
    return;
  }

  char* start = strchr(c_list, '(') + 1;
  char* end = strchr(start, ')');
  if (end) *end = '\0';

  int children_count = 0;
  char* ptr = start;
  while(*ptr) {
    if (*ptr != ' ' && *ptr != ',') {
      ++children_count;
      if (binary && children_count > 2) {
        printf("Error: Binary tree cannot have more than two children.\n");
        return;
      }
    }
    ++ptr;
  }

  char* split = strtok(start, ", ");
  node* last_child = parent_node->left;
  while (last_child && last_child->right) {
    last_child = last_child->right;
  }

  while (split) {
    node* new_child = malloc(sizeof(node));
    if (!new_child) {
      printf("Memory allocation failed.\n");
      return;
    }
    new_child->value = split[0];
    new_child->left = NULL;
    new_child->right = NULL;

    if (last_child) {
      last_child->right = new_child;
    } else {
      parent_node->left = new_child;
    }
    last_child = new_child;
    split = strtok(NULL, ", ");
  }
}


void print(tree* my_tree) {
  
  if (my_tree->root == NULL) {
    printf("There is no root. please insert root\n");
    return; 
  }
  
  if (my_tree->root->value) {
    printf("%c", my_tree->root->value);
  }


  if (my_tree->root->left){
    printf("(");
    tree left_tree;
    left_tree.root=my_tree->root->left;
    print(&left_tree);
    printf(")");
  } 

  if (my_tree->root->right){
    printf(",");
    tree right_tree;
    right_tree.root=my_tree->root->right;
    print(&right_tree);
  }
}

int find_level(node* root, char value, int level) {
    if (root == NULL) return -1; 

    if (root->value == value) return level;

    int child_level = find_level(root->left, value, level + 1);
    if (child_level != -1) return child_level;

    return find_level(root->right, value, level);
}

int level_of_node(tree* my_tree, char node) {
    if (my_tree->root == NULL) {
        printf("The tree is empty\n");
        return -1;
    }
    int level = find_level(my_tree->root, node, 0);
    return level;
}

int level_cal(node* root) { 
    if (root == NULL) return 0; 

    int level = 1 + level_cal(root->left);  
    int sibling_level = level_cal(root->right);

    return (level > sibling_level) ? level : sibling_level;  
}

int level_of_tree(tree* my_tree) {
    if (my_tree->root == NULL) {
        printf("The tree is empty\n");
        return -1;
    }
    return level_cal(my_tree->root) - 1;
}

void delete_node(tree* my_tree, char Node) {
  node* target = find(my_tree->root, Node);
  node* target_parent = find_parent(my_tree->root, target);
  if( target == NULL ) {
    printf("Error. // There is no such node.\n");
    return;
  } else if (target->left != NULL) {
    printf("Error. // parent node.\n");
    return;
  } else if (target_parent == NULL) {
    my_tree->root=NULL;
    return;
  }

  if (target_parent->left==target) {
    target_parent->left=target->right;
  } else {
    node* sibling_serach = target_parent->left;
    while (sibling_serach != NULL && sibling_serach->right != target) {
      sibling_serach = sibling_serach->right;
    }
    if (sibling_serach == NULL) {
      printf("Error. // node not found.\n");
      return;
    }
    sibling_serach->right = target->right;
  }
}

void get_ancestors(tree* my_tree, char Node) { 
    node* search = find(my_tree->root, Node);
    if (search == NULL) {
        printf("No such node exists.\n");
        return;
    }
    while (search != my_tree->root) {
        search = find_parent(my_tree->root, search);
        if (search == NULL) {
            printf("Error. //There is no ancestors.\n");
            return;
        }
        printf("%c ", search->value);
    }
    printf("\n");
}

void find_descendants(node* root) {
    if (root == NULL) return;

    printf("%c ", root->value);
    find_descendants(root->left);   
    find_descendants(root->right); 
}

void get_descendants(tree* my_tree, char Node) {
    if (my_tree->root == NULL) {
        printf("Error. //Tree is empty\n");
        return;
    }

    node* target = find(my_tree->root, Node);
    if (target == NULL) {
        printf("No such node exists.\n");
        return;
    }

    find_descendants(target->left);
    printf("\n");
}

void degree_of_node(tree* my_tree, char Node) {
	node* targetNode = find(my_tree->root, Node); 
	if (targetNode == NULL) {
		printf("Error. // Such node doesn't exist\n"); 
		return;
	} else if (targetNode->left == NULL) {
		printf("0\n"); 
		return;
	} else {
		int degree = 0;
		targetNode = targetNode->left; 
		while(targetNode != NULL) {
			degree++;
			targetNode = targetNode->right;  
		}
		printf("%d\n", degree); 
	}
}

int get_degree(node* Node) { 
    int maxDegree = 0; 
    int childDegree = 0; 

    for (node* child = Node->left; child != NULL; child = child->right) {
        maxDegree++;
        int degree = get_degree(child); 
        if (degree > childDegree) { 
            childDegree = degree;
        }
    }
    return (maxDegree > childDegree) ? maxDegree : childDegree;
}

int count(node* root) { 
    if (root == NULL) {
        return 0;
    }
    return 1 + count(root->left) + count(root->right);
}

void count_node(tree* myTree) { 
    if (myTree == NULL || myTree->root == NULL) {
        return;
    }
    printf("%d\n", count(myTree->root));
}

void degree_of_tree(tree* my_tree) { 
  if (my_tree->root == NULL) {
        printf("The tree is empty.\n");
        return;
    }
  printf("%d\n", get_degree(my_tree->root));
}

void insert_sibling(tree* my_tree, char node_value, const char* s_list) {

    if (my_tree->root == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    node* target_node = find(my_tree->root, node_value);
    if (target_node == NULL) {
        printf("Node %c not found.\n", node_value);
        return;
    }

    if (target_node == my_tree->root) {
        printf("Cannot add siblings to the root.\n");
        return;
    }

    node* parent_node = find_parent(my_tree->root, target_node);
    node* sibling = parent_node->left;
    node* last_sibling = NULL;

    while (sibling != NULL) {
        if (sibling->right == NULL) {
            last_sibling = sibling;
            break;
        }
        sibling = sibling->right;
    }

    for (int i = 0; s_list[i] != '\0'; ++i) {
        if (s_list[i] != ',' && s_list[i] != ' ') { 
            node* new_sibling = (node*) malloc(sizeof(node));
            if (new_sibling == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            new_sibling->value = s_list[i];
            new_sibling->left = NULL;
            new_sibling->right = NULL;

            if (last_sibling != NULL) {
                last_sibling->right = new_sibling;
            }
            last_sibling = new_sibling; 
        }
    }
}

void join_trees(char new_root_value, tree* my_tree, tree* tree2) {

    node* new_root = malloc(sizeof(node));
    if (new_root == NULL) {
        printf("Memory allocation failed for new root node.\n");
        return;
    }
    new_root->value = new_root_value;
    new_root->left = my_tree->root;   
    new_root->right = tree2->root;  

    tree* new_tree = malloc(sizeof(tree));
    if (new_tree == NULL) {
        printf("Memory allocation failed for new tree.\n");
        free(new_root); 
        return;
    }
    new_tree->root = new_root;
    print(new_tree);
}

void clear_tree(node* root) {
    if (root) {
        clear_tree(root->left); 
        clear_tree(root->right); 
        free(root);
    }
}

void clear(tree* my_tree) {
    clear_tree(my_tree->root); 
    my_tree->root = NULL;
}
