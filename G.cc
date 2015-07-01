#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAXN    28
#define MAXQUEUE   16 

int color[MAXN];
int flag[MAXN];

int ALL;

int graph[MAXN][MAXN];

int N;
int K, L;

bool tabu[MAXN][MAXN];
int queue[MAXQUEUE];
int queuePtr;

inline void inc(int x) {
    if (x < 0) x = -x;
    if (!flag[x]) ++ ALL;
    ++ flag[x];
}

inline void dec(int x) {
    if (x < 0) x = -x;
    -- flag[x];
    if (!flag[x]) -- ALL;
}

inline void swap(int x, int y) {
    for (int i = 1; i <= graph[x][0]; ++ i) {
        if (graph[x][i] == y) continue;
        dec(color[graph[x][i]] - color[x]);
        inc(color[graph[x][i]] - color[y]);
    }
    for (int i = 1; i <= graph[y][0]; ++ i) {
        if (graph[y][i] == x) continue;
        dec(color[graph[y][i]] - color[y]);
        inc(color[graph[y][i]] - color[x]);
    }
    int temp = color[x]; color[x] = color[y]; color[y] = temp;
}

inline int max(int a, int b) { return a > b ? a : b; }

struct edge {
    int x, y;
} E[MAXN];

inline void solve1() {
    scanf("%d", &N);

    for (int i = 1; i <= N; ++ i)
        color[i] = i - 1;

    int temp;
    for (int i = 2; i <= N; ++ i) {
        int k = rand() % i + 1;
        temp = color[i]; color[i] = color[k]; color[k] = temp;
    }

    ALL = 0;
    memset(flag, 0, sizeof(flag));
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        E[i].x = x; E[i].y = y;
        ++ graph[x][0]; graph[x][graph[x][0]] = y;
        ++ graph[y][0]; graph[y][graph[y][0]] = x;
        inc(color[x] - color[y]);
    }

    memset(tabu, false, sizeof(tabu));
    memset(queue, -1, sizeof(queue));
    queuePtr = 0;
    int counter = 0;
    while (ALL < N - 1) {
        ++ counter;
        if (counter > 3000) {
            counter = 0;
            memset(tabu, false, sizeof(tabu));
            memset(queue, -1, sizeof(queue));
            queuePtr = 0;
            for (int i = 2; i <= N; ++ i) {
                int k = rand() % i + 1;
                temp = color[i]; color[i] = color[k]; color[k] = temp;
            }
            ALL = 0;
            memset(flag, 0, sizeof(flag));
            for (int i = 0; i < N - 1; ++ i)
                inc(color[E[i].x] - color[E[i].y]);
        }
        int best = -1, best_x, best_y;
        bool up = false;
        for (int x = 1; x < N; ++ x)
            for (int y = x + 1; y <= N; ++ y) {
                if (tabu[x][y]) continue;
                int last = ALL;
                swap(x, y);
                if (ALL > last) {
                    up = true;
                    if (queue[queuePtr] != -1)
                        tabu[queue[queuePtr] >> 5][queue[queuePtr] & 31] = false;
                    queue[queuePtr] = (x << 5) + y;
                    tabu[x][y] = true;
                    queuePtr = (queuePtr + 1) & (MAXQUEUE - 1);
                    break;
                }
                if (ALL > best) {
                    best = ALL;
                    best_x = x; best_y = y;
                }
                else if (ALL == best) {
                    if (rand() & 1)
                        best_x = x; best_y = y;
                }
                swap(x, y);
            }
            if (!up) {
                if (best == -1) {
                    /*
                    counter = 0;
                    memset(tabu, false, sizeof(tabu));
                    memset(queue, -1, sizeof(queue));
                    queuePtr = 0;
                    for (int i = 2; i <= N; ++ i) {
                        int k = rand() % i + 1;
                        temp = color[i]; color[i] = color[k]; color[k] = temp;
                    }
                    ALL = 0;
                    memset(flag, 0, sizeof(flag));
                    for (int i = 0; i < N - 1; ++ i)
                        inc(color[E[i].x] - color[E[i].y]);
                    */
                }
                else {
                    swap(best_x, best_y);
                    if (queue[queuePtr] != -1)
                        tabu[queue[queuePtr] >> 5][queue[queuePtr] & 31] = false;
                    queue[queuePtr] = (best_x << 5) + best_y;
                    tabu[best_x][best_y] = true;
                    queuePtr = (queuePtr + 1) & (MAXQUEUE - 1);
                }
            }
    }

    for (int i = 1; i < N; ++ i)
        printf("%d ", color[i]);
    printf("%d\n", color[N]);
    //fprintf(stderr, "%d\n", counter);
}

inline void solve2() {
    scanf("%d%d", &K, &L);
    int head = 1;
    int tail = K * (L + 1);
    printf("0");
    for (int i = 0; i <= L; ++ i)
        if ((i & 1) == 0) {
            for (int j = 0; j < K; ++ j)
                printf(" %d", tail - j * (L + 1));
            -- tail;
        }
        else {
            for (int j = 0; j < K; ++ j)
                printf(" %d", head + j * (L + 1));
            ++ head;
        }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int T;
    scanf("%d", &T);
    while (T --) {
        int k;
        scanf("%d", &k);
        if (k == 1)
            solve1();
        else
            solve2();
    }

    return 0;
}