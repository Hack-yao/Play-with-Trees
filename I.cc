#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN    1000 + 1
#define MAXE    2*(MAXN)

#define MAXST   100000
#define LogMAXST    18

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
int start[MAXN];
int nexte[MAXE];

bool flag[MAXN];

vector<int> EulerTour;
vector<int> level;
int first[MAXN];
SparseTable st;

void dfs(int x, int depth) {
    flag[x] = false;
    first[x] = EulerTour.size();
    EulerTour.push_back(x);
    level.push_back(depth);
    for (int i = start[x]; i != -1; i = nexte[i]) {
        if (!flag[v[i]]) continue;
        dfs(v[i], depth + 1);
        EulerTour.push_back(x);
        level.push_back(depth);
    }
}

int LCA(int x, int y) {
    int L = first[x], R = first[y];
    if (L > R) swap(L, R);
    return EulerTour[st.Query(L, R)];
}


bool node_on_path(int x, int p, int q) {
    int u = LCA(p, q); 
    if (LCA(u, x) != u) return false;
    return (LCA(x, p) == x || LCA(x, q) == x);
}

int entry_point(int x, int p, int q) {
    int u = LCA(p, q);
    if (LCA(u, x) != u) return u;
    int y = LCA(p, x);
    if (y == u) return LCA(q, x);
    return y;
}

pair<int, int> intersection(int x, int y, int p, int q) {
    int a = entry_point(x, p, q);
    int b = entry_point(y, p, q);
    if (node_on_path(a, x, y) && node_on_path(b, x, y))
        return make_pair(a, b);
    return make_pair(-1, -1);
}

int main() {
    int N;
    E = 0;
    memset(start, -1, sizeof(start));
    scanf("%d", &N);
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }

    memset(flag, true, sizeof(flag));

    int root = 1;

    dfs(root, 0);

    st.preprocess(level);

    int M;
    scanf("%d", &M);
    while (M --) {
        int x, y, p, q;

        scanf("%d%d%d%d", &x, &y, &p, &q);

        pair<int, int> ret = intersection(x, y, p, q);

        printf("%d %d\n", ret.first, ret.second);
    }

/*
    int M;
    scanf("%d", &M);
    while (M --) {
        int x, p, q;
        scanf("%d%d%d", &x, &p, &q);
        printf("%d\n", entry_point(x, p, q));
*/
        /*
        if (node_on_path(x, p, q))
            printf("yes\n");
        else
            printf("no\n");
        */
//    }

   return 0; 
}