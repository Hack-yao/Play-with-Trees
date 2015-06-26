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


int MST(int &bound, int *T) {
    int tree, cost, maxdeg;
    tree = cost = maxdeg = 0;
    S.clear();
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < M; ++ i) {
        int x = E[i].x, y = E[i].y;
        if (degree[x] < bound && degree[y] < bound && !S.find(x, y)) {
            ++ degree[x]; ++ degree[y];
            if (degree[x] > maxdeg) maxdeg = degree[x];
            if (degree[y] > maxdeg) maxdeg = degree[y];
            cost += E[i].c;
            S.merge(x, y);
            T[tree] = i; ++ tree;
        }
        if (tree == N - 1) break;
    }
    if (tree != N - 1) return -1;
    bound = maxdeg;
    return cost;
}

void print(int cost, int bound, int *T) {
    printf("%d %d\n", cost, bound);
    for (int i = 0; i < N - 1; ++ i)
        printf("%d %d\n", E[T[i]].x, E[T[i]].y);
}

int LB_T[MAXN], LB, LB_cost;
int UB_T[MAXN], UB, UB_cost;
int LB_score;
int UB_score;

int temp[MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &B);
    for (int i = 0; i < M; ++ i) {
        scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].c);
    }

    sort(E, E + M, cmp);

    UB = N - 1;
    UB_cost = MST(UB, UB_T);
    if (UB <= B) {
        print(UB_cost, UB, UB_T);
        return 0;
    }

    for (LB = B; ; ++ LB) {
        LB_cost = MST(LB, LB_T);
        if (LB_cost != -1) break;
    }

    if (LB == B)
        LB_score = 5 * LB_cost;
    else
        LB_score = 15 * LB_cost * LB;
    UB_score = 15 * UB_cost * UB;

    int delta = (UB - LB) / 10 + 1;

    int best = -1;
    int best_score = (LB_score < UB_score ? LB_score : UB_score);
    for (int bound = LB + 1; bound < UB; bound += delta) {
        int cost = MST(bound, temp);
        int score = 15 * cost * bound;
        if (score < best_score) {
            best_score = score;
            best = bound;
        }
    }
    if (best == -1) {
        if (LB_score <= UB_score)
            print(LB_cost, LB, LB_T);
        else
            print(UB_cost, UB, UB_T);
    }
    else {
        int cost = MST(best, temp);
        print(cost, best, temp);
    }
    return 0;
}
