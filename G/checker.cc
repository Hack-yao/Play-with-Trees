#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN 30

FILE *Graph = fopen("in", "r");
FILE *Color = fopen("out", "r");

bool checkA() {
    int N;
    fscanf(Graph, "%d", &N);
    int color[MAXN];
    for (int i = 1; i <= N; ++ i)
        fscanf(Color, "%d", &color[i]);
    bool flag[MAXN]; 
    memset(flag, false, sizeof(flag));
    bool ret = true;
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        fscanf(Graph, "%d%d", &x, &y);
        int k = color[x] - color[y];
        if (k < 0) k = -k;
        if (k <= 0 || k >= N || flag[k]) {
            ret = false;
            printf("--> %d -- x(color) = %d(%d), y(color) = %d(%d)\n", k, x, color[x], y, color[y]);
        }
        else {
            flag[k] = true;
            //printf("%d -- x(color) = %d(%d), y(color) = %d(%d)\n", k, x, color[x], y, color[y]);
        }
    }
    if (!ret) {
        printf("%d\n", N);
    }
    return ret;
}

bool checkB() {
    int K, L;
    fscanf(Graph, "%d%d", &K, &L);
    int N = K * (L + 1) + 1;
    int color[MAXN];
    for (int i = 1; i <= N; ++ i)
        fscanf(Color, "%d", &color[i]);
    return true;
}

int main() {
    int T;
    fscanf(Graph, "%d", &T);
    while (T --) {
        int k;
        fscanf(Graph, "%d", &k);
        if (k == 1)
            if (checkA()) printf("Accept!\n"); else printf("Wrong Answer!\n");
        else
            if (checkB()) printf("Accept!\n"); else printf("Wrong Answer!\n");
    }
    fclose(Graph);
    fclose(Color);
    return 0; 
}