#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN    1000000 + 1
#define MAXE    2*(MAXN)

#define MAXST   2000100 + 1
#define LogMAXST    22

struct SparseTable {
    int N;
    int F[LogMAXST][MAXST];
    vector<int> A;

    SparseTable() {}
    SparseTable(const vector<int> &A) {
        preprocess(A);
    }

    void preprocess(const vector<int> &A) {
        N = A.size();
        this->A = A;
        for (int i = 0; i < N; ++ i)
            F[0][i] = i;
        for (int k = 1; (1 << k) <= N; ++ k)
            for (int i = 0; i + (1 << k) - 1 < N; ++ i)
                if (A[F[k - 1][i]] <= A[F[k - 1][i + (1 << (k - 1))]])
                    F[k][i] = F[k - 1][i];
                else
                    F[k][i] = F[k - 1][i + (1 << (k - 1))];
    }

    int Query(int x, int y) const {
        int len = y - x + 1;
        int k;
        for (k = 0; (1 << k) <= len; ++ k);
        -- k;
        return (A[F[k][x]] <= A[F[k][y - (1 << k) + 1]] ? F[k][x] : F[k][y - (1 << k) + 1]);
    }
};


int E;
int v[MAXE];
int d[MAXE];
int start[MAXN];
int nexte[MAXE];

bool flag[MAXN];

vector<int> EulerTour;
vector<int> level;
int first[MAXN];
SparseTable st;

int dist[MAXN]; // from root = 1 to x

void dfs(int x, int depth, int cur_dist) {
    flag[x] = false;
    dist[x] = cur_dist;
    first[x] = EulerTour.size();
    EulerTour.push_back(x);
    level.push_back(depth);
    for (int i = start[x]; i != -1; i = nexte[i]) {
        if (!flag[v[i]]) continue;
        dfs(v[i], depth + 1, cur_dist + d[i]);
        EulerTour.push_back(x);
        level.push_back(depth);
    }
}

inline int LCA(int x, int y) {
    int L = first[x], R = first[y];
    if (L > R) swap(L, R);
    return EulerTour[st.Query(L, R)];
}


inline bool node_on_path(int x, int p, int q) {
    int u = LCA(p, q); 
    if (LCA(u, x) != u) return false;
    return (LCA(x, p) == x || LCA(x, q) == x);
}

inline int entry_point(int x, int p, int q) {
    int u = LCA(p, q);
    if (LCA(u, x) != u) return u;
    int y = LCA(p, x);
    if (y == u) return LCA(q, x);
    return y;
}

inline pair<int, int> intersection(int x, int y, int p, int q) {
    int a = entry_point(x, p, q);
    int b = entry_point(y, p, q);
    if (node_on_path(a, x, y) && node_on_path(b, x, y))
        return make_pair(a, b);
    return make_pair(-1, -1);
}

inline int getdist(int x, int y) {
    int u = LCA(x, y);
    return dist[x] + dist[y] - 2 * dist[u];
}

#define MAXM    1000

struct ant {
    int s, t, v;
} A[MAXM];

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

        //cout << "hereA" << endl;
        memset(flag, true, sizeof(flag));
        int root = 1;
        EulerTour.clear();
        level.clear();
        dfs(root, 0, 0);

        //cout << "hereB" << endl;

        st.preprocess(level);

        int total = 0;
        for (int i = 0; i < M - 1; ++ i)
            for (int j = i + 1; j < M; ++ j) {
                pair<int, int> path = intersection(A[i].s, A[i].t, A[j].s, A[j].t);
                if (path.first == -1) continue;
                int p = path.first;
                int q = path.second;
                double timePi = (double)getdist(A[i].s, p) / (double)A[i].v;
                double timeQi = (double)getdist(A[i].s, q) / (double)A[i].v;
                double timePj = (double)getdist(A[j].s, p) / (double)A[j].v;
                double timeQj = (double)getdist(A[j].s, q) / (double)A[j].v;
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