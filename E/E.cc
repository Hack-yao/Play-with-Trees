#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#include <vector>
#include <ctime>
#include <cstdlib>

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

/*
bool rand_cmp(const edge &A, const edge &B) {
    return A.c + (rand() % 1000) < B.c + (rand() % 1000);
}
*/

UnionFind S;
int degree[MAXN];

struct XY {
    int x, y;
};

int MST(int &bound, XY *T) {
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
            T[tree].x = x; T[tree].y = y; ++ tree;
        }
        if (tree == N - 1) break;
    }
    if (tree != N - 1) return -1;
    bound = maxdeg;
    return cost;
}

void print(int cost, int bound, XY *T) {
    printf("%d %d\n", cost, bound);
    for (int i = 0; i < N - 1; ++ i)
        printf("%d %d\n", T[i].x, T[i].y);
}



int LB, LB_cost;
int UB, UB_cost;

XY LB_T[MAXN];
XY UB_T[MAXN];
XY temp[MAXN];
XY best[MAXN];
/*
int LB_score;
int UB_score;
*/


void shuffle() {
    int T = M / 5;
    while (T --) {
        int k = rand() % (M - 1);
        swap(E[k], E[k + 1]);
    }
}

int main() {
    srand(time(NULL));
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

    //printf("find! %d\n", LB);

    int best_cost = LB_cost;
    int T = 200;
    while (T --) {
        shuffle();
//        sort(E, E + M, rand_cmp);
        //random_shuffle(E, E + M);
        int cost = MST(LB, temp);
        if (cost != -1 && cost < best_cost) {
            //printf("update! %d -> %d\n", best_cost, cost);
            best_cost = cost;
            for (int i = 0; i < N - 1; ++ i)
                best[i] = temp[i];
        }
    }
    if (best_cost == LB_cost)
        print(LB_cost, LB, LB_T);
    else
        print(best_cost, LB, best);

/*
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
*/
    return 0;
}
