#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for adjacency list nodes
typedef struct Edge {
    int v;
    int w;
    struct Edge* next;
} Edge;

// Structure for priority queue element
typedef struct {
    long long weight;
    int u;
    int count;
} PQNode;

// Min-Heap implementation
typedef struct {
    PQNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (PQNode*)malloc(sizeof(PQNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(PQNode* a, PQNode* b) {
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(MinHeap* heap, long long weight, int u, int count) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = (PQNode*)realloc(heap->data, sizeof(PQNode) * heap->capacity);
    }
    int i = heap->size++;
    heap->data[i] = (PQNode){weight, u, count};
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].weight > heap->data[i].weight) {
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        } else {
            break;
        }
    }
}

PQNode popHeap(MinHeap* heap) {
    PQNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        
        if (heap->data[left].weight < heap->data[smallest].weight)
            smallest = left;
        if (right < heap->size && heap->data[right].weight < heap->data[smallest].weight)
            smallest = right;
            
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

int shortestPath(int n, int** edges, int edgesSize, int* edgesColSize, char* labels, int k) {
    // Build adjacency list
    Edge** adj = (Edge**)calloc(n, sizeof(Edge*));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        newEdge->v = v;
        newEdge->w = w;
        newEdge->next = adj[u];
        adj[u] = newEdge;
    }
    
    // Distance table: min_dist[u][count]
    // Since count is 1-indexed up to k, we can allocate (n * (k + 1))
    long long* min_dist = (long long*)malloc(sizeof(long long) * n * (k + 1));
    for (int i = 0; i < n * (k + 1); i++) {
        min_dist[i] = -1; // -1 represents infinity
    }
    
    MinHeap* heap = createHeap(1024);
    
    // Start at node 0 with count 1 and weight 0
    pushHeap(heap, 0, 0, 1);
    min_dist[0 * (k + 1) + 1] = 0;
    
    int ans = -1;
    
    while (heap->size > 0) {
        PQNode curr = popHeap(heap);
        long long w = curr.weight;
        int u = curr.u;
        int count = curr.count;
        
        if (u == n - 1) {
            ans = (int)w;
            break;
        }
        
        if (w > min_dist[u * (k + 1) + count]) {
            continue;
        }
        
        for (Edge* edge = adj[u]; edge != NULL; edge = edge->next) {
            int v = edge->v;
            int weight = edge->w;
            
            int next_count = (labels[u] == labels[v]) ? count + 1 : 1;
            
            if (next_count <= k) {
                long long next_w = w + weight;
                int idx = v * (k + 1) + next_count;
                
                if (min_dist[idx] == -1 || next_w < min_dist[idx]) {
                    min_dist[idx] = next_w;
                    pushHeap(heap, next_w, v, next_count);
                }
            }
        }
    }
    
    // Cleanup memory
    for (int i = 0; i < n; i++) {
        Edge* curr = adj[i];
        while (curr != NULL) {
            Edge* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adj);
    free(min_dist);
    free(heap->data);
    free(heap);
    
    return ans;
}