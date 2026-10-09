#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Helper function to check if a string is valid parentheses
bool isValid(char *s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

// Node structure for queue
typedef struct Node {
    char *str;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
} Queue;

Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, char *str) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->str = strdup(str);
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

char* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    Node *temp = q->front;
    char *str = temp->str;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return str;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// Simple hash set node for visited check
typedef struct HashNode {
    char *str;
    struct HashNode *next;
} HashNode;

#define HASH_SIZE 10007

unsigned int hash(char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

bool contains(HashNode *table[], char *str) {
    unsigned int h = hash(str);
    HashNode *curr = table[h];
    while (curr) {
        if (strcmp(curr->str, str) == 0) return true;
        curr = curr->next;
    }
    return false;
}

void insert(HashNode *table[], char *str) {
    if (contains(table, str)) return;
    unsigned int h = hash(str);
    HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->str = strdup(str);
    newNode->next = table[h];
    table[h] = newNode;
}

char** removeInvalidParentheses(char *s, int *returnSize) {
    *returnSize = 0;
    if (!s) return NULL;

    Queue *q = createQueue();
    HashNode *visited[HASH_SIZE] = {NULL};
    HashNode *addedToQueue[HASH_SIZE] = {NULL};

    enqueue(q, s);
    insert(addedToQueue, s);

    bool found = false;
    
    // Dynamic array to store final results
    int capacity = 100;
    char **result = (char**)malloc(capacity * sizeof(char*));

    while (!isEmpty(q)) {
        char *curr = dequeue(q);

        if (isValid(curr)) {
            found = true;
            if (*returnSize >= capacity) {
                capacity *= 2;
                result = (char**)realloc(result, capacity * sizeof(char*));
            }
            result[(*returnSize)++] = strdup(curr);
        }

        // If we found valid strings at this level, don't go deeper (minimum removals constraint)
        if (found) {
            free(curr);
            continue;
        }

        // Generate all possible states by removing one parenthesis
        int len = strlen(curr);
        for (int i = 0; i < len; i++) {
            if (curr[i] != '(' && curr[i] != ')') continue;

            // Create new string excluding character at index i
            char *nextStr = (char*)malloc(len * sizeof(char));
            strncpy(nextStr, curr, i);
            strcpy(nextStr + i, curr + i + 1);

            if (!contains(addedToQueue, nextStr)) {
                insert(addedToQueue, nextStr);
                enqueue(q, nextStr);
            }
            free(nextStr);
        }
        free(curr);
    }

    // Free queues and hash tables if needed...
    return result;
}