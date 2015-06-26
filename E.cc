#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN    10000+1
#define MAXE    100000


#define MAXU    MAXN

struct UnionFind {
    int f[MAXU];
    int rank[MAXU];

    void clear() {
        memset(f, -1, sizeof(f));
        memset(rank, 0, sizeof(rank));
    }

    inline int root(int x) {
        int y = x;
        for (; f[x] != -1; x = f[x]);
        while (y != x) {
            int next = f[y]; f[y] = x;
            y = next;
        }
        return x;
    }

    int find(int x, int y) {
        return (root(x) == root(y));
    }

    void merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return;
        if (rank[x] < rank[y])
            f[x] = y;
        else {
            f[y] = x;
            if (rank[x] == rank[y]) ++ rank[x];
        }

    }
};

int N, M, B;

struct edge {
    int c, x, y; 
} E[MAXE];

bool cmp(const edge &A, const edge &B) {
    return A.c < B.c;
}

UnionFind S;

int degree[MAXN];

int T[MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &B);
    for (int i = 0; i < M; ++ i) {
        scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].c);
        //E[i].used = false;
    }

    sort(E, E + M, cmp);

    int LB;
    int cost;
    for (LB = B; ; ++ LB) {
        int tree = 0;
        cost = 0;
        S.clear();
        memset(degree, 0, sizeof(degree));
        for (int i = 0; i < M; ++ i) {
            int x = E[i].x, y = E[i].y;
            if (degree[x] < LB && degree[y] < LB && !S.find(x, y)) {
                ++ degree[x]; ++ degree[y];
                cost += E[i].c;
                S.merge(x, y);
                T[tree] = i; ++ tree;
            }
            if (tree == N - 1) break;
        }
        if (tree == N - 1) break;
    }

    if (LB == B) {
        LB = 0;
        for (int i = 1; i <= N; ++ i)
            if (degree[i] > LB) LB = degree[i];
    }
    printf("%d %d\n", cost, LB);
    for (int i = 0; i < N - 1; ++ i)
        printf("%d %d\n", E[T[i]].x, E[T[i]].y);


    return 0;
}
