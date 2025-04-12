/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
}NODE;

typedef struct g {
    int node_number;
    int *visited;
    struct Node **adjacency_lists;
}GRAPH;

typedef struct s {
    int top;
    int capacity;
    int *elements;
}STACK;

NODE *create_node(int node_number) {
    NODE *link = malloc(sizeof(NODE));
    link->data = node_number;
    link->next = NULL;
    return link;
}

void addEdge(GRAPH *g, int source, int dest) {
    NODE *newNode = create_node(dest);
    newNode->next = g->adjacency_lists[source];
    g->adjacency_lists[source] = newNode;

    newNode = create_node(source);
    newNode->next = g->adjacency_lists[dest];
    g->adjacency_lists[dest] = newNode;
}

GRAPH *create_graph(int node_number) {
    GRAPH *g = malloc(sizeof(GRAPH));
    g->node_number = node_number;
    g->adjacency_lists = malloc(sizeof(NODE *)* node_number);
    g->visited = malloc(sizeof(int) * node_number);

    for ( int i = 0 ; i < node_number ; i++ ) {
        g->adjacency_lists[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}

STACK *create_stack(int capacity) {
    STACK *stack = malloc (sizeof(STACK));
    stack->elements = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

int isFullStiva(STACK *stack) {
    return stack->top == stack->capacity - 1;
}

void push (int value, STACK *stack) {
    if(!isFullStiva(stack)) {
        stack->top=stack->top + 1;
        stack->elements[stack->top]=value;
    }
    else {
        printf("Overflow!\n");
    }
}

int pop(STACK *stack) {
    if( stack->top == -1 ) {
        return -1;
    }
    int data = stack->elements[stack->top];
    stack->top = stack->top - 1;

    return data;
}

int IsVisited(GRAPH *graph, int node) {
    return graph->visited[node];
}

void DFS(GRAPH *graph, STACK *stack, int start) {
    push(start, stack);
    graph->visited[start] = 1;
    printf("DFS incepe de la nodul %d\n", start);

    while (stack->top != -1) {
        int currentNode = pop(stack);
        if (currentNode == -1) break;
        printf("Vizitat: %d\n", currentNode);

        NODE *adjacency=graph->adjacency_lists[currentNode];
        while (adjacency!=NULL) {
            int neighbour = adjacency->data;
            if (!IsVisited(graph, neighbour)) {
                push(neighbour, stack);
                graph->visited[neighbour] = 1;
            }
            adjacency=adjacency->next;
        }
    }

}

void insertEdges(GRAPH *graph, int edge_nr, int number_of_nodes) {
    int source, dest;
    printf("adauga %d muchii (de la 1 la %d)\n", edge_nr, number_of_nodes - 1);
    for (int i = 0; i < edge_nr; i++)
        {
            scanf("%d %d", &source, &dest);
            addEdge(graph, source, dest);
        }
}

void wipe(GRAPH *graph, int number_of_nodes)
{
    for (int i = 0; i < number_of_nodes; i++)
    {
        graph->visited[i] = 0;
    }
}

bool canbePathBetween(GRAPH *graph, int source, int dest, STACK *stack, int number_of_nodes) {
    DFS(graph,stack,source);
    bool found = graph->visited[dest];
    wipe(graph, number_of_nodes);
    return found;
}

int main() {
    int number_of_nodes, edge_nr;
    int source, dest;

    printf("Cate noduri are graful? ");
    scanf("%d", &number_of_nodes);

    printf("Cate muchii are graful? ");
    scanf("%d", &edge_nr);

    GRAPH *graph = create_graph(number_of_nodes);
    STACK *stack = create_stack(2 * number_of_nodes);

    printf("Adauga %d muchii (de la 0 la %d):\n", edge_nr, number_of_nodes - 1);
    for (int i =0; i < edge_nr; i++) {
        printf("Muchia %d: ", i+1);
        scanf("%d%d", &source, &dest);
        addEdge(graph, source, dest);
    }

    printf("Exista drum intre restaurantele urmatoare?: \n");
    printf("Introdu primul restaurant: ");
    scanf("%d", &source);
    printf("\nIntrodu al doilea restaurant: ");
    scanf("%d", &dest);
    bool exista = canbePathBetween(graph, source, dest, stack, number_of_nodes);
    if (exista) {
        printf("Exista drum intre cele doua restaurante");
    }
    else {
        printf("Nu exista drum intre cele doua restaurante");
    }

    return 0;
}
