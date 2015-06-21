#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN    10000 + 1
#define MAXE    2*(MAXN)

int N;

int E;
int v[MAXE];
int start[MAXE];
int nexte[MAXE];

int f[MAXN], g[MAXN];

// f -- x is visited
// g -- x is not visited

vector<int> path[MAXN];

const int inf = 100000000;

bool flag[MAXN];

int ptrA[MAXN], ptrB[MAXN];


void dp(int x) {
    flag[x] = false;
    int children = 0;

    int childrenG = 0;
    int deltaA = inf, deltaB = inf;
    ptrA[x] = -1; ptrB[x] = -1;
    for (int i = start[x]; i != -1; i = nexte[i]) {
        int y = v[i];
        if (!flag[y]) continue;
        ++ children;
        dp(y);

        childrenG += g[y];
        if (f[y] - g[y] <= deltaA) {
            deltaB = deltaA; deltaA = f[y] - g[y];
            ptrB[x] = ptrA[x]; ptrA[x] = y;
        }
        else if (f[y] - g[y] < deltaB) {
            deltaB = f[y] - g[y];
            ptrB[x] = y;
        }
    }
    if (children == 0) {
        f[x] = g[x] = 1;
        return;
    }

    f[x] = childrenG + deltaA;
    if (children == 1)
        g[x] = f[x];
    else
        g[x] = childrenG + deltaA + deltaB - 1;
}

int label;

void findpath_f(int x, bool order) {
    if (x == -1) return;
    flag[x] = false;
    if (order) {
        path[label].push_back(x);
        findpath_f(ptrA[x], order);
    }
    else {
        findpath_f(ptrA[x], order);
        path[label].push_back(x);
    }
}

void findpath_g(int x) {
    if (x == -1) return;
    flag[x] = false;
    findpath_f(ptrA[x], false);
    path[label].push_back(x);
    findpath_f(ptrB[x], true);
}

void dfs(int x, int parent) {
    if (flag[x]) {
        if (f[x] <= g[x])
            findpath_f(x, true);
        else
            findpath_g(x);
        ++ label;
    }
    for (int i = start[x]; i != -1; i = nexte[i]) {
        if (parent == v[i]) continue;
        dfs(v[i], x);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    int root = 1;
    while (T --) {
        E = 0;
        memset(start, -1, sizeof(start));
        scanf("%d", &N);
        for (int i = 0; i < N - 1; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
            v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
        }

        memset(flag, true, sizeof(flag));
        dp(root);

        int ans = min(f[root], g[root]);
        printf("%d\n", ans);


        memset(flag, true, sizeof(flag));
        for (int i = 0; i < ans; ++ i)
            path[i].clear();
        label = 0;
/*
        for (int i = 1; i <= N; ++ i) {
            printf("ptrA(%d) = %d, ptrB(%d) = %d\n", i, ptrA[i], i, ptrB[i]);
            printf("f(%d) = %d, g(%d) = %d\n", i, f[i], i, g[i]);
        }
*/
        dfs(root, -1);

        for (int i = 0; i < ans; ++ i) {
            for (int j = 0; j < path[i].size() - 1; ++ j)
                printf("%d ", path[i][j]);
            printf("%d\n", path[i][path[i].size() - 1]);
        }
    }

    return 0;
}