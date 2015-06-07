#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXN    100000 + 1
#define MAXE    2*MAXN

int N;

int E;
int v[MAXE];
int nexte[MAXE];
int start[MAXN];

int key[MAXN];
int L[MAXN], R[MAXN];

int X[MAXN];

// [L, R)
void dfs(int root) {
    int stack[MAXN];
    bool flag[MAXN];
    memset(flag, false, sizeof(flag));
    int esp = 1; stack[0] = root;

    int ptr = 0;

    while (esp) {
        int x = stack[esp - 1];
        if (!flag[x]) {
            flag[x] = true;
            X[ptr] = x; L[x] = ptr; ++ ptr;
            for (int i = start[x]; i != -1; i = nexte[i])
                if (!flag[v[i]]) {
                    stack[esp] = v[i]; ++ esp;
                }
        }
        else {
            flag[x] = false; -- esp;
            R[x] = ptr;
        }
    }
}

struct interval_tree {
    int *elem;
    int l, r; //[l, r)
} Tree[20 * MAXN];


void build_interval_tree(int t, int left, int right) {
    Tree[t].l = left; Tree[t].r = right;
    if (left + 1 == right) {
        Tree[t].elem = new int[1];
        Tree[t].elem[0] = X[left];
        return;
    }
    else {
        int mid = (left + right) >> 1;

        build_interval_tree(t * 2, left, mid);
        build_interval_tree(t * 2 + 1, mid, right);
        Tree[t].elem = new int[right - left];
        int x = 0, y = 0;
        int *ptrX = Tree[t * 2].elem;
        int *ptrY = Tree[t * 2 + 1].elem;
        int *ptr = Tree[t].elem;
        while (x < mid - left || y < right - mid) {
            if (x == mid - left) {
                *ptr ++ = *ptrY ++; ++ y;
            }
            else if (y == right - mid) {
                *ptr ++ = *ptrX ++; ++ x;
            }
            else if (key[*ptrX] < key[*ptrY]) {
                *ptr ++ = *ptrX ++; ++ x;
            }
            else {
                *ptr ++ = *ptrY ++; ++ y;
            }
        }
    }
}

// return #elements in A, which < key
int binary_search(int *A, int length, int K) {
    if (K > key[A[length - 1]]) return length;
    if (K <= key[A[0]]) return 0;

    int left = 0; int right = length - 1;
    // [left, right]
    while (left < right) {
        //printf("%d %d\n", left, right);
        int mid = (left + right) >> 1;
        if (key[A[mid]] == K) return mid;
        if (key[A[mid]] < K)
            left = mid + 1;
        else 
            right = mid;
    }
    return left;
}

// [left, right)
int rank_interval_tree(int root, int left, int right, int key) {
    top:
    if (left == Tree[root].l && right == Tree[root].r)
        return binary_search(Tree[root].elem, Tree[root].r - Tree[root].l, key);
    if (right <= Tree[root * 2].r) {
        root = root * 2; goto top;
    }
    if (left >= Tree[root * 2 + 1].l){
        root = root * 2 + 1; goto top;
    }
    return rank_interval_tree(root * 2, left, Tree[root * 2].r, key) +
           rank_interval_tree(root * 2 + 1, Tree[root * 2 + 1].l, right, key);
}


int query(int node, int rank) {
    int left = 0;
    int right = N;
    while (left + 1 < right) {
        int mid = (left + right) >> 1;
        int k = rank_interval_tree(1, L[node], R[node], key[Tree[1].elem[mid]]);
        if (k == rank - 1)
            left = mid;
        else if (k < rank - 1)
            left = mid + 1;
        else
            right = mid;
    }
    return Tree[1].elem[left];
}

int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i)
        scanf("%d", &key[i]);
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }

    int root = 1;
    dfs(root);

    build_interval_tree(1, 0, N);

    int M;
    scanf("%d", &M);
    while (M --) {
        int node, rank;
        scanf("%d %d", &node, &rank);
        printf("%d\n", query(node, rank));
    }

/*
    int A[10];
    A[0] = 0;
    A[1] = 1;
    A[2] = 2;
    A[3] = 3;
    A[4] = 4;
    A[5] = 5;
    printf("%d\n", binary_search(A, 6, -1));
    printf("%d\n", binary_search(A, 6, 0));
    printf("%d\n", binary_search(A, 6, 1));
    printf("%d\n", binary_search(A, 6, 2));
    printf("%d\n", binary_search(A, 6, 3));
    printf("%d\n", binary_search(A, 6, 4));
    printf("%d\n", binary_search(A, 6, 5));
    printf("%d\n", binary_search(A, 6, 6));
*/

    return 0;
}