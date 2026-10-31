#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int uniquePaths(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int MOD = 1000000007;

    // We can precompute the next non-mirror landing positions using 
    // running scans or a bottom-up DP state transition.
    // Let's use the optimized bottom-up recurrence:
    int*** go = (int***)malloc(m * sizeof(int**));
    for (int i = 0; i < m; i++) {
        go[i] = (int**)malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            go[i][j] = (int*)malloc(2 * sizeof(int));
            go[i][j][0] = -1;
            go[i][j][1] = -1;
        }
    }

    // Fill transition table from bottom-right to top-left in O(1) per state
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            for (int d = 0; d < 2; d++) { // 0: right, 1: down
                int next_i = i + (d == 1 ? 1 : 0);
                int next_j = j + (d == 0 ? 1 : 0);

                if (next_i < 0 || next_i >= m || next_j < 0 || next_j >= n) {
                    go[i][j][d] = -1;
                    continue;
                }

                if (grid[next_i][next_j] == 0) {
                    go[i][j][d] = next_i * n + next_j;
                } else {
                    // Hit mirror -> deflect perpendicular immediately, 
                    // and inherit the precomputed path from the mirror cell.
                    int next_d = 1 - d;
                    go[i][j][d] = go[next_i][next_j][next_d];
                }
            }
        }
    }

    // Standard DP to count paths
    long long** dp = (long long**)malloc(m * sizeof(long long*));
    for (int i = 0; i < m; i++) {
        dp[i] = (long long*)calloc(n, sizeof(long long));
    }

    dp[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == 0) continue;

            // Move right
            int target_r = go[i][j][0];
            if (target_r != -1) {
                int ni = target_r / n;
                int nj = target_r % n;
                dp[ni][nj] = (dp[ni][nj] + dp[i][j]) % MOD;
            }

            // Move down
            int target_d = go[i][j][1];
            if (target_d != -1) {
                int ni = target_d / n;
                int nj = target_d % n;
                dp[ni][nj] = (dp[ni][nj] + dp[i][j]) % MOD;
            }
        }
    }

    long long ans = dp[m - 1][n - 1];

    // Clean up memory
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(go[i][j]);
        }
        free(go[i]);
        free(dp[i]);
    }
    free(go);
    free(dp);

    return (int)ans;
}