#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN    1000000 + 1
#define MAXE    2*(MAXN)

#define MAXST   2000100 + 1
#define LogMAXST    22

int Level[MAXN];

inline int clz(int x){return __builtin_clz(x);}
inline int lg2(int x){return !x ? -1 : 31 - clz(x);}

int STN;
int F[LogMAXST][MAXST];

void STpreprocess(int *A, int n) {
    STN = n;
    for (int i = 0; i < STN; ++ i)
        F[0][i] = A[i];
    for (int k = 1; (1 << k) <= STN; ++ k)
        for (int i = 0; i + (1 << k) - 1 < STN; ++ i)
            if (Level[F[k - 1][i]] <= Level[F[k - 1][i + (1 << (k - 1))]])
                F[k][i] = F[k - 1][i];
            else
                F[k][i] = F[k - 1][i + (1 << (k - 1))];
}

int Query(int x, int y) {
    int k = lg2(y - x);
    return (Level[F[k][x]] <= Level[F[k][y - (1 << k) + 1]] ? F[k][x] : F[k][y - (1 << k) + 1]);
}


int E;
int v[MAXE];
int d[MAXE];
int start[MAXN];
int nexte[MAXE];

bool flag[MAXN];

int ETptr;
int EulerTour[MAXST];
int first[MAXN];

int dist[MAXN]; // from root = 1 to x

void dfs(int x) {
    flag[x] = false;
    first[x] = ETptr;
    EulerTour[ETptr] = x; ++ ETptr;
    for (int i = start[x]; i != -1; i = nexte[i]) {
        if (!flag[v[i]]) continue;
        Level[v[i]] = Level[x] + 1;
        dist[v[i]] = dist[x] + d[i];
        dfs(v[i]);
        EulerTour[ETptr] = x; ++ ETptr;
    }
}

#define MAXM    1000

struct ant {
    int s, t, v;
    int lca;
} A[MAXM];

inline int LCA(int x, int y) {
    if (x == y) return x;
    int L = first[x], R = first[y];
    if (L > R) {
        int k = L; L = R; R = k;
    }
    return Query(L, R);
}


inline bool node_on_path(int x, int i) {
    return LCA(A[i].lca, x) == A[i].lca && (LCA(x, A[i].s) == x || LCA(x, A[i].t) == x);
}

inline int entry_point(int x, int i) {
    int u = A[i].lca;
    if (LCA(u, x) != u) return u;
    int y = LCA(A[i].s, x);
    if (y != u) return y;
    return LCA(A[i].t, x);
}

int IX, IY;

inline void intersection(int i, int j) {
    int a = entry_point(A[i].s, j);
    if (!node_on_path(a, i)) {
        IX = IY = -1; return;
    }
    int b = entry_point(A[i].t, j);
    if (!node_on_path(b, i)) {
        IX = IY = -1; return;
    }
    IX = a; IY = b;
}

inline int getdist(int x, int y) {
    int u = LCA(x, y);
    return dist[x] + dist[y] - 2 * dist[u];
}
int main() {
    int N, M;

    int T;

    scanf("%d", &T);
    while (T --) {
        E = 0;
        memset(start, -1, sizeof(start));
        scanf("%d", &N);
        for (int i = 0; i < N - 1; ++ i) {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            v[E] = y; d[E] = k; nexte[E] = start[x]; start[x] = E; ++ E;
            v[E] = x; d[E] = k; nexte[E] = start[y]; start[y] = E; ++ E;
        }

        scanf("%d", &M);
        for (int i = 0; i < M; ++ i)
            scanf("%d%d%d", &A[i].s, &A[i].t, &A[i].v);

        memset(flag, true, sizeof(flag));
        int root = 1;
        ETptr = 0;
        dist[root] = 0; Level[root] = 0;
        dfs(root);


        STpreprocess(EulerTour, ETptr);

        //printf("%d\n", LCA(1, 2));

        for (int i = 0; i < M; ++ i)
            A[i].lca = LCA(A[i].s, A[i].t);

        int total = 0;
        for (int i = 0; i < M - 1; ++ i)
            for (int j = i + 1; j < M; ++ j) {
                intersection(i, j);
                //printf("%d %d\n", i, j);
                if (IX == -1) continue;
                double timePi = (double)getdist(A[i].s, IX) / (double)A[i].v;
                double timeQi = (double)getdist(A[i].s, IY) / (double)A[i].v;
                double timePj = (double)getdist(A[j].s, IX) / (double)A[j].v;
                double timeQj = (double)getdist(A[j].s, IY) / (double)A[j].v;
                //cout << timePi << " " << timeQi << " " << timePj << " " << timeQj << endl;
                //printf("%d %d\n", p, q);
                if (timePi <= timePj && timeQj <= timeQi)
                    ++ total;
                else if (timePj <= timePi && timeQi <= timeQj)
                    ++ total;
            }
        printf("%d\n", total);
    }
    return 0; 
}