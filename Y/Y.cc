#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN    10000 + 1
#define MAXE    2*(MAXN)

int N, M;

int E;
int v[MAXE];
int start[MAXE];
int nexte[MAXE];

int flag[MAXN];

void dfs(int x) {
    flag[x] = false;
    for (int i = start[x]; i != -1; i = nexte[i])
        if (flag[v[i]]) dfs(v[i]);
}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }

    if (N != M + 1) {
        printf("NO\n");
        return 0;
    }

    memset(flag, true, sizeof(flag));
    int root = 1;
    dfs(root);
    for (int i = 1; i <= N; ++ i)
        if (flag[i]) {
            printf("NO\n");
            return 0;
        }

    printf("YES\n");
    return 0;
}