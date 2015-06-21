#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN    10000 + 1
#define MAXE    2*(MAXN)

int N;

int E;
int v[MAXE];
int start[MAXN];
int next[MAXE];

int flag[MAXN];

int longest;
int target;

void dfs(int x, int dist) {
    flag[x] = false;
    if (dist > longest) {
        longest = dist;
        target = x;
    }
    for (int i = start[x]; i != -1; i = next[i])
        if (flag[v[i]]) dfs(v[i], dist + 1);
}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d", &N);
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; next[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; next[E] = start[y]; start[y] = E; ++ E;
    }

    memset(flag, true, sizeof(flag));
    longest = 0; target = 1;
    dfs(1, 0);

    memset(flag, true, sizeof(flag));
    longest = 0;
    dfs(target, 0);

    printf("%d\n", longest);

    return 0;
}