#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN    1000009
#define MAXE    2*(MAXN)

#define MAXST   2*(MAXN)
#define LogMAXST    22

int Level[MAXN];

inline int clz(int x){return __builtin_clz(x);}
inline int lg2(int x){return !x ? -1 : 31 - clz(x);}

struct SparseTable {
    int N;
    int F[LogMAXST][MAXST];

    SparseTable() {}
    SparseTable(int *A, int n) {
        preprocess(A, n);
    }

    void preprocess(int *A, int n) {
        N = n;
        for (int i = 0; i < N; ++ i)
            F[0][i] = A[i];
        for (int k = 1; (1 << k) <= N; ++ k)
            for (int i = 0; i + (1 << k) - 1 < N; ++ i)
                if (Level[F[k - 1][i]] <= Level[F[k - 1][i + (1 << (k - 1))]])
                    F[k][i] = F[k - 1][i];
                else
                    F[k][i] = F[k - 1][i + (1 << (k - 1))];
    }

    int Query(int x, int y) const {
        int k = lg2(y - x + 1);
        return (Level[F[k][x]] <= Level[F[k][y - (1 << k) + 1]] ? F[k][x] : F[k][y - (1 << k) + 1]);
    }
};


int E;
int v[MAXE];
int d[MAXE];
int start[MAXN];
int nexte[MAXE];

bool flag[MAXN];

int ETptr;
int EulerTour[MAXST];
int first[MAXN];
SparseTable st;

int dist[MAXN]; // from root = 1 to x

int Stack[MAXN];
int ESP;

void dfs(int root) {
    Stack[0] = root; ESP = 1;
    while (ESP) {
        int x = Stack[ESP - 1];
        if (flag[x]) {
            flag[x] = false;
            first[x] = ETptr;
        }
        EulerTour[ETptr] = x; ++ ETptr;
        while (start[x] != -1 && !flag[v[start[x]]]) start[x] = nexte[start[x]];
        if (start[x] == -1) {
            -- ESP;
        }
        else {
            int y = v[start[x]];
            Level[y] = Level[x] + 1;
            dist[y] = dist[x] + d[start[x]];
            Stack[ESP] = y; ++ ESP;
        }
    }
}

#define MAXM    1009

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
    return st.Query(L, R);
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
        IX = IY = -1;
        return;
    }
    int b = entry_point(A[i].t, j);
    if (!node_on_path(b, i)) {
        IX = IY = -1;
        return;
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


        st.preprocess(EulerTour, ETptr);

        for (int i = 0; i < M; ++ i)
            A[i].lca = LCA(A[i].s, A[i].t);

        int total = 0;
        for (int i = 0; i < M - 1; ++ i)
            for (int j = i + 1; j < M; ++ j) {
                intersection(i, j);
                if (IX == -1) continue;
                
                long long timePi = getdist(A[i].s, IX) * (long long)A[j].v;
                long long timePj = getdist(A[j].s, IX) * (long long)A[i].v;
                long long timeQi = getdist(A[i].s, IY) * (long long)A[j].v;
                long long timeQj = getdist(A[j].s, IY) * (long long)A[i].v;

                if (timePi <= timePj && timeQj <= timeQi)
                    ++ total;
                else if (timePj <= timePi && timeQi <= timeQj)
                    ++ total;
            }
        printf("%d\n", total);
    }
    return 0; 
}