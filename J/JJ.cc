#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAXN    100000 + 1
#define MAXE    2*MAXN

int N;

int E;
int v[MAXE];
int nexte[MAXE];
int start[MAXN];

int key[MAXN];
int L[MAXN], R[MAXN];

int X[MAXN];

int sorted[MAXN];

// [L, R]
void dfs(int root) {
    int stack[MAXN];
    bool flag[MAXN];
    memset(flag, false, sizeof(flag));
    int esp = 1; stack[0] = root;

    int ptr = 0;

    while (esp) {
        int x = stack[esp - 1];
        if (!flag[x]) {
            flag[x] = true;
            ++ ptr; X[ptr] = x; L[x] = ptr;
            for (int i = start[x]; i != -1; i = nexte[i])
                if (!flag[v[i]]) {
                    stack[esp] = v[i]; ++ esp;
                }
        }
        else {
            flag[x] = false; -- esp;
            R[x] = ptr;
        }
    }
}

#define MAXDEPTH    20
int Tree[MAXDEPTH][MAXN];
int f[MAXDEPTH][MAXN];

void build_interval_tree(int depth, int left, int right) {
    if (left == right) return;

    int mid = (left + right) >> 1;
    int median = sorted[mid];
    //printf("(left, right, median) = (%d, %d, %d)\n", left, right, median);

    int x = left; int y = mid + 1;
    for (int i = left; i <= right; ++ i) {
        f[depth][i] = (i == left ? 0 : f[depth][i - 1]);
        if (key[Tree[depth][i]] <= median) {
            Tree[depth + 1][x ++] = Tree[depth][i]; ++ f[depth][i];
        }
        else
            Tree[depth + 1][y ++] = Tree[depth][i];
        /*
        else {
            Tree[depth + 1][mid] = Tree[depth][i];
        }
        */
    }
    //f[depth][mid] = f[depth][mid - 1] + 1;
    build_interval_tree(depth + 1, left, mid);
    build_interval_tree(depth + 1, mid + 1, right);
}


int rank_interval_tree(int depth, int left, int right, int l, int r, int K) {
    top:
    
//printf("%d %d, %d %d\n", left, right, l, r);
    if (l == r) return Tree[depth][l];

    int mid = (left + right) >> 1;

    int leftL1 = (left == l ? 0 : f[depth][l - 1]);
    int leftR = f[depth][r];

    if (K <= leftR - leftL1) {
        l = left + leftL1;
        r = left + leftR - 1;
        right = mid;
        ++ depth; goto top;
    }
    else {
        K = K - (leftR - leftL1);
        l = mid + 1 + (l - left) - leftL1;
        r = mid + (r - left + 1) - leftR;
        left = mid + 1;
        ++ depth; goto top;
    }
}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        scanf("%d", &key[i]);
        sorted[i] = key[i];
    }
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }

    int root = 1;
    dfs(root);


    sort(sorted + 1, sorted + 1 + N);
    /*
    for (int i = 1; i <= N; ++ i)
        printf("%d ", median[i]);
    printf("\n");

    for (int i = 1; i <= N; ++ i)
        printf("%d ", X[i]);
    printf("\n");
    */

    for (int i = 1; i <= N; ++ i)
        Tree[0][i] = X[i];

    build_interval_tree(0, 1, N);

/*
    for (int i = 0; i < 5; ++ i) {
        for (int j = 1; j <= N; ++ j)
            printf("%d ", f[i][j]);
        printf("\n");
        for (int j = 1; j <= N; ++ j)
            printf("%d ", key[Tree[i][j]]);
        printf("\n");
        printf("--------------------------------\n");
    }
*/

    int M;
    scanf("%d", &M);
    while (M --) {
        int node, rank;
        scanf("%d %d", &node, &rank);
        printf("%d\n", rank_interval_tree(0, 1, N, L[node], R[node], rank));
    }

    return 0;
}