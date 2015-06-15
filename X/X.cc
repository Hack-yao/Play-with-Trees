#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN    100000 + 1
#define MAXE    2*(MAXN)

int N;

int E;
int v[MAXE];
int start[MAXE];
int nexte[MAXE];

int degree[MAXN];

int f_in[MAXN], f_not[MAXN];

void dp(int x, int p) {
    f_in[x] = 1; f_not[x] = 0;
    for (int i = start[x]; i != -1; i = nexte[i]) {
        int y = v[i];
        if (y == p) continue;
        dp(y, x);
        f_in[x] += min(f_in[y], f_not[y]);
        f_not[x] += f_in[y];
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
    }

    int root = 1;
    dp(root, -1);
    int ans = min(f_in[root], f_not[root]);
    printf("%d\n", ans);

    return 0;
}