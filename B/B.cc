#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN    1000000 + 1
#define MAXE    2*MAXN

int N;

int E;
int v[MAXE];
int nexte[MAXE];
int start[MAXN];

int edgex[MAXN];
int edgey[MAXN];

int degree[MAXN];

bool flag[MAXN];

int dist[MAXN];
int stack[MAXN];

int traverse(int root) {
    int esp;
    dist[root] = degree[root] - 1; flag[root] = false;
    int ret = root;
    stack[0] = root; esp = 1; 
    while (esp) {
        int x = stack[esp - 1]; -- esp;
        if (dist[x] > dist[ret])
            ret = x;
        for (int i = start[x]; i != -1; i = nexte[i])
            if (flag[v[i]]) {
                stack[esp] = v[i]; ++ esp;
                flag[v[i]] = false;
                dist[v[i]] = dist[x] + degree[v[i]] - 1;
            }
    }
    return ret;
}

void find_path(int s, int t) {
    int esp;
    stack[0] = s; esp = 1;
    memset(flag, false, sizeof(flag));
    while (esp) {
        int x = stack[esp - 1];
        if (!flag[x]) {
            flag[x] = true;
            if (x == t) return;
            for (int i = start[x]; i != -1; i = nexte[i])
                if (!flag[v[i]]) {
                    stack[esp] = v[i]; ++ esp;
                }
        }
        else {
            flag[x] = false;
            -- esp;
        }
    }

}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));
    memset(degree, 0, sizeof(degree));

    scanf("%d", &N);
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
        ++ degree[x]; ++ degree[y];
        edgex[i] = x; edgey[i] = y;
    }

    if (N <= 3) {
        printf("%d\n", N);
        for (int i = 0; i < N - 1; ++ i)
            printf("%d %d\n", edgex[i], edgey[i]);
        return 0;
    }

    int u;
    for (int i = 1; i <= N; ++ i) {
        flag[i] = (degree[i] > 1);
        if (flag[i]) u = i;
    }
    u = traverse(u);

    for (int i = 1; i <= N; ++ i)
        flag[i] = (degree[i] > 1);
    int v = traverse(u);

    find_path(u, v);

    int ret = 2;
    for (int i = 1; i <= N; ++ i)
        if (flag[i])
            ret += degree[i] - 1;
    printf("%d\n", ret);

    for (int i = 0; i < N - 1; ++ i) {
        int x = edgex[i];
        int y = edgey[i];
        if (flag[x] || flag[y])
            printf("%d %d\n", x, y);
    }

    return 0;
}