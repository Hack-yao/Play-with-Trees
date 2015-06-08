#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

#define N 100000
#define M 10000
//#define N 50
//#define M 50

int v[(N + 1) * 2];
int nexte[(N + 1) * 2];
int start[N + 1];

int f[N + 1];

int size[N + 1];

void dfs(int x) {
    size[x] = 1;
    for (int i = start[x]; i != -1; i = nexte[i])
        if (size[v[i]] == -1) {
            dfs(v[i]);
            size[x] += size[v[i]];
        }
}

int main() {
    srand(time(NULL));
    printf("%d\n", N);

    int all = N;
    for (int i = 1; i <= N; ++ i)
        f[i] = i;
    while (all > 1) {
        int x = (rand() % all) + 1;
        printf("%d ", f[x]);
        int temp = f[x]; f[x] = f[all]; f[all] = temp;
        -- all;
    }
    printf("%d\n", f[1]);
    /*
    int all;
    for (int i = 1; i < N; ++ i)
        printf("%d ", i);
    printf("%d\n", N);

    for (int i = 1; i <= N - 1; ++ i)
        printf("%d %d\n", i, i + 1);
    */
    int E = 0;
    memset(start, -1, sizeof(start));

    all = N;
    for (int i = 1; i <= N; ++ i)
        f[i] = i;
    while (all > 1) {
        int x = (rand() % all) + 1;
        int y = (rand() % all) + 1;
        if (x == y) continue;
        printf("%d %d\n", f[x], f[y]);

        v[E] = f[y]; nexte[E] = start[f[x]]; start[f[x]] = E; ++ E;
        v[E] = f[x]; nexte[E] = start[f[y]]; start[f[y]] = E; ++ E;

        int k = rand() & 1;
        if (k == 0) {
            int temp = f[x]; f[x] = f[all]; f[all] = temp;
        }
        else {
            int temp = f[y]; f[y] = f[all]; f[all] = temp;
        }
        -- all;
    }

    int root = 1;
    memset(size, -1, sizeof(size));
    dfs(root);

    printf("%d\n", M);
    all = M;
    while (all --) {
        int x = (rand() % N) + 1;
        int rank = (rand() % size[x]) + 1;
        printf("%d %d\n", x, rank);
    }
    return 0; 
}
