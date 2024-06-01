#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex; // 정점(=데이터 필드)
    struct GraphNode* link; // 다음 노드를 가리키는 포인터
} Node;

typedef struct graph {
    int n;  // 그래프의 정점 갯수 n
    char vertices[MAX_VERTICES]; // 정점들을 저장할 배열
    Node* adj_list[MAX_VERTICES];   // 헤드 포인터들을 저장할 배열, 헤드 포인터 수 = 정점 수
} Graph;

void create(Graph* my_graph) {
    int v;
    my_graph->n = 0;
    for (v = 0; v < MAX_VERTICES; v++) {
        my_graph->adj_list[v] = NULL;
        my_graph->vertices[v] = '\0';
    }
}

void insert_vertex(Graph* my_graph, char v) {
    if (my_graph->n + 1 > MAX_VERTICES) {
        return;
    }
    my_graph->vertices[my_graph->n++] = v;
}

int find_vertex_index(Graph* my_graph, char v) {
    for (int i = 0; i < my_graph->n; i++) {
        if (my_graph->vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

void add_edge(Graph* my_graph, char tail, char head) {
    int tail_index = find_vertex_index(my_graph, tail);
    int head_index = find_vertex_index(my_graph, head);

    if (tail_index == -1 || head_index == -1) {
        return;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = head_index;
    node->link = NULL;

    if (my_graph->adj_list[tail_index] == NULL) {
        my_graph->adj_list[tail_index] = node;
    } else {
        Node* temp = my_graph->adj_list[tail_index];
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = node;
    }

    node = (Node*)malloc(sizeof(Node));
    node->vertex = tail_index;
    node->link = NULL;

    if (my_graph->adj_list[head_index] == NULL) {
        my_graph->adj_list[head_index] = node;
    } else {
        Node* temp = my_graph->adj_list[head_index];
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = node;
    }
}


void print(Graph* my_graph) {
    printf("(");
    for (int i = 0; i < my_graph->n; i++) {
        printf("%c", my_graph->vertices[i]);
        Node* node = my_graph->adj_list[i];
        if (node != NULL) {
            printf("(");
            while (node != NULL) {
                printf("%c", my_graph->vertices[node->vertex]);
                node = node->link;
                if (node != NULL) {
                    printf(",");
                }
            }
            printf(")");
        }
        if (i < my_graph->n - 1) {
            printf(",");
        }
    }
    printf(")\n");
}

int degree_of_vertex(Graph* my_graph, char vertex) {
    int vertex_index = find_vertex_index(my_graph, vertex);
    if (vertex_index == -1) {
        return -1;
    }

    int degree = 0;
    Node* node = my_graph->adj_list[vertex_index];
    while (node != NULL) {
        degree++;
        node = node->link;
    }
    return degree;
}

void dfs(Graph* my_graph, int vertex, int* visited) {
    visited[vertex] = 1; 
    Node* node = my_graph->adj_list[vertex];
    while (node != NULL) {
        if (!visited[node->vertex]) {
            dfs(my_graph, node->vertex, visited); 
        }
        node = node->link;
    }
}

int is_connected(Graph* my_graph) {
    if (my_graph->n == 0) {
        return 0; 
    }
    int visited[MAX_VERTICES] = {0}; 
    dfs(my_graph, 0, visited);

    for (int i = 0; i < my_graph->n; i++) {
        if (!visited[i]) {
            return 0;
        }
    }
    return 1; 
}

int is_empty(Graph* my_graph) {
    if (my_graph->n == 0) {
        return 1;
    } else {
        return 0;
    }
}

void adjacent(Graph* my_graph, char vertex) {
    int vertex_index = find_vertex_index(my_graph, vertex);
    if (vertex_index == -1) {
        printf("It does not exist in the graph.\n");
        return;
    }

    Node* node = my_graph->adj_list[vertex_index];
    if (node == NULL) {
        printf("It has no adjacent nodes.\n");
        return;
    }

    printf("{");
    while (node != NULL) {
        printf("%c", my_graph->vertices[node->vertex]);
        node = node->link;
        if (node != NULL) {
            printf(",");
        }
    }
    printf("}\n");
}

void delete_vertex(Graph* my_graph, char vertex) {
    int vertex_index = find_vertex_index(my_graph, vertex);
    if (vertex_index == -1) {
        printf("Vertex %c does not exist in the graph.\n", vertex);
        return;
    }

    Node* node = my_graph->adj_list[vertex_index];
    while (node != NULL) {
        int adj_vertex_index = node->vertex;
        Node* adj_node = my_graph->adj_list[adj_vertex_index];
        Node* prev_node = NULL;

        while (adj_node != NULL) {
            if (adj_node->vertex == vertex_index) {
                if (prev_node == NULL) {
                    my_graph->adj_list[adj_vertex_index] = adj_node->link;
                } else {
                    prev_node->link = adj_node->link;
                }
                free(adj_node);
                break;
            }
            prev_node = adj_node;
            adj_node = adj_node->link;
        }
        Node* temp = node;
        node = node->link;
        free(temp);
    }
    my_graph->adj_list[vertex_index] = NULL;

    for (int i = vertex_index; i < my_graph->n - 1; i++) {
        my_graph->vertices[i] = my_graph->vertices[i + 1];
        my_graph->adj_list[i] = my_graph->adj_list[i + 1];
    }
    my_graph->vertices[my_graph->n - 1] = '\0';
    my_graph->adj_list[my_graph->n - 1] = NULL;
    my_graph->n--;

    for (int i = 0; i < my_graph->n; i++) {
        Node* current = my_graph->adj_list[i];
        while (current != NULL) {
            if (current->vertex > vertex_index) {
                current->vertex--;
            }
            current = current->link;
        }
    }
}

int path_exist(Graph* my_graph, char vertex1, char vertex2) {
    int index1 = find_vertex_index(my_graph, vertex1);
    int index2 = find_vertex_index(my_graph, vertex2);
    
    if (index1 == -1 || index2 == -1) {
        printf("One or both vertices do not exist in the graph.\n");
        return 0;
    }

    int visited[MAX_VERTICES] = {0}; 
    dfs(my_graph, index1, visited);
    
    return visited[index2]; 
}

int num_of_vertex(Graph* my_graph) {
    return my_graph->n;
}

int num_of_edge(Graph* my_graph) {
    int edge_count = 0;

    for (int i = 0; i < my_graph->n; i++) {
        Node* node = my_graph->adj_list[i];
        while (node != NULL) {
            edge_count++;
            node = node->link;
        }
    }

    return edge_count / 2;
}

int remove_edge(Node** head, int target) {
    Node* current = *head;
    Node* previous = NULL;
    while (current != NULL) {
        if (current->vertex == target) {
            if (previous == NULL) {
                *head = current->link;
            } else {
                previous->link = current->link;
            }
            free(current);
            return 1; 
        }
        previous = current;
        current = current->link;
    }
    return 0;
}

void delete_edge(Graph* my_graph, char vertex1, char vertex2) {
    int index1 = find_vertex_index(my_graph, vertex1);
    int index2 = find_vertex_index(my_graph, vertex2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both vertices do not exist in the graph.\n");
        return;
    }

    int removed1 = remove_edge(&(my_graph->adj_list[index1]), index2);
    int removed2 = remove_edge(&(my_graph->adj_list[index2]), index1);

    if (removed1 == 0 || removed2 == 0) {
        printf("Error\n");
    }
}


void rename_vertex(Graph* my_graph, char old_v, char new_v) {
    int old_index = find_vertex_index(my_graph, old_v);
    int new_index = find_vertex_index(my_graph, new_v);

    if (old_index == -1) {
        printf("Error: Vertex %c does not exist in the graph.\n", old_v);
        return;
    }

    if (new_index != -1) {
        printf("Error: Vertex %c already exists in the graph.\n", new_v);
        return;
    }

    my_graph->vertices[old_index] = new_v;

    for (int i = 0; i < my_graph->n; i++) {
        Node* node = my_graph->adj_list[i];
        while (node != NULL) {
            if (node->vertex == old_index) {
                node->vertex = new_index;
            }
            node = node->link;
        }
    }
}

void clear(Graph* my_graph) {
    for (int i = 0; i < my_graph->n; i++) {
        Node* node = my_graph->adj_list[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->link;
            free(temp);
        }
        my_graph->adj_list[i] = NULL;
    }

    for (int i = 0; i < my_graph->n; i++) {
        my_graph->vertices[i] = '\0';
    }

    my_graph->n = 0;
}

int main() {
  Graph *my_graph;
  my_graph=(Graph*)malloc(sizeof(Graph));
  create(my_graph);

  char request[30];
  char cmd;
  char value, value1, value2;

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
    switch (request[0]) {
        case 'G':
            create(my_graph);
            break;
        case '+':
            insert_vertex(my_graph, request[1]);
            break;
        case 'E':
            add_edge(my_graph, request[2], request[4]);
            break;
        case 'L':
            break;
        case 'V':
            printf("%d\n", degree_of_vertex(my_graph, request[2]));
            break;
        case 'C':
            printf("%s\n", (is_connected(my_graph)==1) ? "True" : "False");
            break;
        case 'N':
            printf("%s\n", (is_empty(my_graph)==1) ? "True" : "False");
            break;
        case 'A':
            adjacent(my_graph, request[2]);
            break;
        case '-':
            delete_vertex(my_graph, request[1]);
            break;
        case 'P':
            printf("%s\n", (path_exist(my_graph, request[2], request[4])) ? "True" : "False");
            break;
        case 'X':
            printf("%d\n", num_of_vertex(my_graph));
            break;
        case 'H':
            printf("%d\n", num_of_edge(my_graph));
            break;
        case 'D':
            delete_edge(my_graph,request[2], request[4]);
            break;
        case 'R':
            rename_vertex(my_graph, request[2], request[4]);
            break;
        case 'K':
            clear(my_graph);
            break;
        default :
            break;
    }
    print(my_graph);
  }
  return 0;
}

