#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int type;
    int shift;
    int dist;
} State;

int minOperations(int* nums, int numsSize) {
    int n = numsSize;
    if (n <= 1) return 0;
    
    // Find the index of 0
    int idx0 = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            idx0 = i;
            break;
        }
    }
    
    // Check if cyclically increasing
    bool is_increasing = true;
    for (int k = 0; k < n; k++) {
        if (nums[(idx0 + k) % n] != k) {
            is_increasing = false;
            break;
        }
    }
    
    // Check if cyclically decreasing
    bool is_decreasing = true;
    for (int k = 0; k < n; k++) {
        if (nums[(idx0 - k + n) % n] != k) {
            is_decreasing = false;
            break;
        }
    }
    
    if (!is_increasing && !is_decreasing) {
        return -1;
    }
    
    int target_type = is_increasing ? 0 : 1;
    int target_shift = is_increasing ? idx0 : (idx0 + 1) % n;
    
    // BFS over 2 * n states
    int **visited = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        visited[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            visited[i][j] = -1;
        }
    }
    
    State *queue = (State *)malloc((2 * n + 5) * sizeof(State));
    int front = 0, rear = 0;
    
    // Start from state (0, 0)
    queue[rear++] = (State){0, 0, 0};
    visited[0][0] = 0;
    
    while (front < rear) {
        State curr = queue[front++];
        
        if (curr.type == target_type && curr.shift == target_shift) {
            for (int i = 0; i < 2; i++) free(visited[i]);
            free(visited);
            free(queue);
            return curr.dist;
        }
        
        // Operation 1: Rotate Left
        int nxt_t1 = curr.type;
        int nxt_s1 = (curr.shift + 1) % n;
        if (visited[nxt_t1][nxt_s1] == -1) {
            visited[nxt_t1][nxt_s1] = curr.dist + 1;
            queue[rear++] = (State){nxt_t1, nxt_s1, curr.dist + 1};
        }
        
        // Operation 2: Reverse
        int nxt_t2 = 1 - curr.type;
        int nxt_s2 = (n - curr.shift) % n;
        if (visited[nxt_t2][nxt_s2] == -1) {
            visited[nxt_t2][nxt_s2] = curr.dist + 1;
            queue[rear++] = (State){nxt_t2, nxt_s2, curr.dist + 1};
        }
    }
    
    for (int i = 0; i < 2; i++) free(visited[i]);
    free(visited);
    free(queue);
    return -1;
}