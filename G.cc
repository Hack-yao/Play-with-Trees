#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAXN    28

int color[MAXN];
bool flag[MAXN];

struct edge {
    int x, y;
};

edge E[MAXN];
int N;
int K, L;

inline int f() {
    int ret = 0;
    memset(flag, false, sizeof(flag));
    for (int i = 0; i < N - 1; ++ i) {
        int k = color[E[i].x] - color[E[i].y];
        if (k < 0) k = -k;
        if (!flag[k]) {
            flag[k] = true;
            ++ ret;
        }
    }
    return ret;
}


void solve1() {
    for (int i = 1; i <= N; ++ i)
        color[i] = i - 1;

    int temp;
    for (int i = 2; i <= N; ++ i) {
        int k = rand() % i + 1;
        temp = color[i]; color[i] = color[k]; color[k] = temp;
    }

    const int trial = (N * (N - 1) / 5 > 20) ? N * (N - 1) / 5 : 20;
    int cur = f();
    while (cur < N - 1) {
        //printf("%d\n", cur);
        int best = -1, best_x, best_y;
        int counter = 0;
        bool up = false;
        while (counter < trial) {
            int x = rand() % N + 1;
            int y = rand() % N + 1;
            if (x == y) continue;
            ++ counter;
            temp = color[x]; color[x] = color[y]; color[y] = temp;
            int next = f();
            if (next > cur) {
                up = true; cur = next; break;
            }
            if (next > best) {
                best = next;
                best_x = x; best_y = y;
            }
            temp = color[x]; color[x] = color[y]; color[y] = temp;
        }
        if (!up && best != -1) {
            temp = color[best_x]; color[best_x] = color[best_y]; color[best_y] = temp;
            cur = best;
        }
    }

    for (int i = 1; i < N; ++ i)
        printf("%d ", color[i]);
    printf("%d\n", color[N]);
}

void solve2() {
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
        if (k == 1) {
            scanf("%d", &N);
            for (int i = 0; i < N - 1; ++ i)
                scanf("%d%d", &E[i].x, &E[i].y);
            solve1();
        }
        else {
            scanf("%d%d", &K, &L);
            solve2();
        }
    }

    return 0;
}