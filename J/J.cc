#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXN    100000 + 1
#define MAXE    2*(MAXN)

int N;

int E;
int v[MAXE];
int nexte[MAXE];
int start[MAXN];

int key[MAXN];
int L[MAXN], R[MAXN];

int X[MAXN];

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

void build_interval_tree(int depth, int left, int right) {
    if (left == right) {
        Tree[depth][left] = X[left];
        return;
    }
    int mid = (left + right) >> 1;

    build_interval_tree(depth + 1, left, mid);
    build_interval_tree(depth + 1, mid + 1, right);
    int x = left, y = mid + 1;
    int ptr = left;
    while (x <= mid && y <= right) {
        if (key[Tree[depth + 1][x]] < key[Tree[depth + 1][y]])
            Tree[depth][ptr ++] = Tree[depth + 1][x ++];
        else
            Tree[depth][ptr ++] = Tree[depth + 1][y ++];
    }
    while (x <= mid)
        Tree[depth][ptr ++] = Tree[depth + 1][x ++];
    while (y <= right)
        Tree[depth][ptr ++] = Tree[depth + 1][y ++];
}


// [left, right]
int rank_interval_tree(int depth, int left, int right, int l, int r, int K) {
    top:
    if (left == l && right == r) {
        // find all <= K
        //printf("K = %d, largest = %d, left = %d, right = %d\n", K, key[Tree[depth][right]], left, right);
        if (K >= key[Tree[depth][right]]) return (right + 1) - left;
        //if (K < key[Tree[depth][left]]) return 0;
        int low = left;
        int high = right;
        while (low < high) {
            int mid = (low + high) >> 1;
            //printf("low = %d, high = %d, key = %d, K = %d\n", low, high, key[Tree[depth][mid]], K);
            if (key[Tree[depth][mid]] <= K)
                low = mid + 1;
            else
                high = mid;
        }
        return low - left;
    }
    int mid = (left + right) >> 1;
    if (r <= mid) {
        ++ depth; right = mid; goto top;
    }
    if (l >= mid + 1) {
        ++ depth; left = mid + 1; goto top;
    }
    return rank_interval_tree(depth + 1, left, mid, l, mid, K) + rank_interval_tree(depth + 1, mid + 1, right, mid + 1, r, K);
}


int query(int node, int rank) {
    int left = 1;
    int right = N;
    //printf("node = %d, rank = %d\n", node, rank);
    while (left < right) {
        int mid = (left + right) >> 1;
        int k = rank_interval_tree(0, 1, N, L[node], R[node], key[Tree[0][mid]]);
        //printf("%d %d %d, rank = %d\n", L[node], R[node], key[Tree[0][mid]], k);
        if (k == rank)
            right = mid;
        else if (k < rank)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return Tree[0][left];
}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i)
        scanf("%d", &key[i]);
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }

    int root = 1;
    dfs(root);

    build_interval_tree(0, 1, N);

/*
    for (int i = 0; i <= 4; ++ i) {
        for (int j = 1; j <= N; ++ j)
            printf("%d ", key[Tree[i][j]]);
        printf("\n");
    }

    for (int i = 1; i <= N; ++ i)
        printf("L = %d, R = %d\n", L[i], R[i]);
*/

    int M;
    scanf("%d", &M);
    while (M --) {
        int node, rank;
        scanf("%d %d", &node, &rank);
        printf("%d\n", query(node, rank));
    }

/*
    int A[10];
    A[0] = 0;
    A[1] = 1;
    A[2] = 2;
    A[3] = 3;
    A[4] = 4;
    A[5] = 5;
    printf("%d\n", binary_search(A, 6, -1));
    printf("%d\n", binary_search(A, 6, 0));
    printf("%d\n", binary_search(A, 6, 1));
    printf("%d\n", binary_search(A, 6, 2));
    printf("%d\n", binary_search(A, 6, 3));
    printf("%d\n", binary_search(A, 6, 4));
    printf("%d\n", binary_search(A, 6, 5));
    printf("%d\n", binary_search(A, 6, 6));
*/

    return 0;
}