#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN    200+1
#define INF     100000000

int N;

int Graph[MAXN][MAXN];
int dist[MAXN][MAXN];

pair<int, int> convex[MAXN];
pair<int, int> temp[MAXN];

int distCenter[MAXN];

bool visited[MAXN];
void dfs(int x) {
    visited[x] = true;
    for (int i = 1; i <= N; ++ i)
        if (!visited[i] && distCenter[i] == distCenter[x] + Graph[x][i]) {
            printf("%d %d\n", x, i);
            dfs(i);
        }
}

int main() {
    int M;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; ++ i) {
        for (int j = 1; j <= N; ++ j) {
            Graph[i][j] = -1;
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    while (M --) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        w <<= 1; // double length
        if (Graph[x][y] == -1)
            Graph[x][y] = Graph[y][x] = dist[x][y] = dist[y][x] = w;
        else
            Graph[x][y] = Graph[y][x] = dist[x][y] = dist[y][x] = min(w, Graph[x][y]);
    }

    for (int k = 1; k <= N; ++ k)
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j <= N; ++ j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int diameter = INF;
    pair<int, int> center_edge;
    int offset;

    for (int u = 1; u < N; ++ u)
        for (int v = u + 1; v <= N; ++ v) {
            if (Graph[u][v] == -1) continue;
            for (int w = 1; w <= N; ++ w)
                temp[w - 1] = make_pair(dist[u][w], dist[v][w]);
            sort(temp, temp + N);
            int ptr = 0;
            for (int i = 0; i < N; ++ i) {
                while (ptr && convex[ptr - 1].second <= temp[i].second) -- ptr;
                convex[ptr] = temp[i]; ++ ptr;
            }
            bool updated = false;
            if (convex[0].second < diameter) {
                diameter = convex[0].second; offset = Graph[u][v]; updated = true;
            }
            if (convex[ptr - 1].first < diameter) {
                diameter = convex[ptr - 1].first; offset = 0; updated = true;
            }

            for (int i = 1; i < ptr; ++ i) {
                int k = (Graph[u][v] + convex[i - 1].first + convex[i].second) >> 1;
                if (k < diameter) {
                    diameter = k;
                    offset = (Graph[u][v] - convex[i - 1].first + convex[i].second) >> 1;
                    updated = true;
                }
            }
            if (updated)
                center_edge = make_pair(u, v);
        }

    printf("%d\n", diameter);

    int u = center_edge.first;
    int v = center_edge.second;
    for (int k = 1; k <= N; ++ k)
        distCenter[k] = min(dist[u][k] + offset, dist[v][k] + Graph[u][v] - offset);

    memset(visited, false, sizeof(visited));

    if (offset == 0)
        dfs(u);
    else if (offset == Graph[u][v])
        dfs(v);
    else {
        printf("%d %d\n", u, v);
        dfs(u); dfs(v);
    }

    return 0;
}
