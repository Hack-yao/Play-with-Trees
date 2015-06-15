#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

#define MAXN    100000 + 1
#define MAXE    2*(MAXN)

int N;

int E;
int v[MAXE];
int nexte[MAXE];
int start[MAXN];


struct TreeNode {
    TreeNode *left, *right, *father;
    int size;
    pair<int, int> key;
};

TreeNode *build(pair<int, int> x) {
    TreeNode *ret = (TreeNode *)malloc(sizeof(TreeNode));
    ret->left = ret->right = ret->father = NULL;
    ret->size = 1;
    ret->key = x;
    return ret;
}

TreeNode *splay(TreeNode *x) {
    if (x == NULL) return NULL;
    while (x->father != NULL) {
        TreeNode *y = x->father;
        TreeNode *z = y->father;
        if (z == NULL) {
            if (x == y->left) {
                x->father = NULL; 
                if (x->right != NULL)
                    x->right->father = y;
                y->father = x;

                y->left = x->right;
                x->right = y;

                y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
            }
            else {
                x->father = NULL;
                if (x->left != NULL)
                    x->left->father = y;
                y->father = x;

                y->right = x->left;
                x->left = y;

                y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
            }
        }
        else {
            if (x == y->left) {
                if (y == z->left) {
                    if (z->father != NULL) {
                        if (z == z->father->left)
                            z->father->left = x;
                        else
                            z->father->right = x;
                    }
                    x->father = z->father;
                    y->father = x;
                    z->father = y;
                    if (x->right != NULL)
                        x->right->father = y;
                    if (y->right != NULL)
                        y->right->father = z;

                    y->left = x->right;
                    z->left = y->right;
                    x->right = y;
                    y->right = z;

                    z->size = 1 + (z->left == NULL ? 0 : z->left->size) + (z->right == NULL ? 0 : z->right->size);
                    y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                    x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
                }
                else {
                    if (z->father != NULL) {
                        if (z == z->father->left)
                            z->father->left = x;
                        else
                            z->father->right = x;
                    }
                    x->father = z->father;
                    y->father = z->father = x;
                    if (x->right != NULL)
                        x->right->father = y;
                    if (x->left != NULL)
                        x-> left->father = z;

                    y->left = x->right;
                    z->right = x->left;
                    x->left = z;
                    x->right = y;

                    z->size = 1 + (z->left == NULL ? 0 : z->left->size) + (z->right == NULL ? 0 : z->right->size);
                    y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                    x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
                }
            }
            else {
                if (y == z->left) {
                    if (z->father != NULL) {
                        if (z == z->father->left)
                            z->father->left = x;
                        else
                            z->father->right = x;
                    }
                    x->father = z->father;
                    y->father = z->father = x;
                    if (x->left != NULL)
                        x->left->father = y;
                    if (x->right != NULL)
                        x->right->father = z;

                    y->right = x->left;
                    z->left = x->right;
                    x->left = y;
                    x->right = z;

                    z->size = 1 + (z->left == NULL ? 0 : z->left->size) + (z->right == NULL ? 0 : z->right->size);
                    y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                    x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
                }
                else {
                    if (z->father != NULL) {
                        if (z == z->father->left)
                            z->father->left = x;
                        else
                            z->father->right = x;
                    }
                    x->father = z->father;
                    y->father = x;
                    z->father = y;
                    if (x->left != NULL)
                        x->left->father = y;
                    if (y->left != NULL)
                        y->left->father = z;

                    y->right = x->left;
                    z->right = y->left;
                    x->left = y;
                    y->left = z;

                    z->size = 1 + (z->left == NULL ? 0 : z->left->size) + (z->right == NULL ? 0 : z->right->size);
                    y->size = 1 + (y->left == NULL ? 0 : y->left->size) + (y->right == NULL ? 0 : y->right->size);
                    x->size = 1 + (x->left == NULL ? 0 : x->left->size) + (x->right == NULL ? 0 : x->right->size);
                }
            }
        }
    }
    return x;
}

TreeNode *insert(pair<int, int> key) {
    TreeNode *New = (TreeNode *)malloc(sizeof(TreeNode));
    New -> key = key; New -> count = 1;
    New -> left = New -> right = New -> father = NULL;

    if (Root == NULL)
    {
        Root = New;
        return;
    }
    if (key < Root -> key)
    {
        New -> left = Root -> left;
        if (New -> left != NULL)
            New -> left -> father = New;
        Root -> left = NULL;
        New -> right = Root;
    }
    else
    {
        New -> right = Root -> right;
        if (New -> right != NULL)
            New -> right -> father = New;
        Root -> right = NULL;
        New -> left = Root;
    }
    Root -> father = New;
    Root = New;
}

TreeNode *find_kth(TreeNode *x, int K) {
    if (x->size < K) return 0;
    while (x) {
        if (x->left == NULL) {
            if (K == 1)
                return splay(x);
            else {
                printf("stupid!\n");
                return NULL;
            }
        }
        if (K == x->left->size + 1)
            return splay(x);
        if (K <= x->left->size)
            x = x->left;
        else {
            K -= x->left->size + 1;
            x = x->right;
        }
    }
    printf("stupid!\n");
    return NULL;
}


int key[MAXN];

vector< pair<int, int> > query[MAXN];

#define MAXM    10000
int answer[MAXM];

TreeNode *trees[MAXN];

bool flag[MAXN];

void dfs(int x) {
    bool leaf = true;
    flag[x] = false;
    for (int i = start[x]; i != -1; i = next[i]) {
        if (!flag[v[i]]) continue;
        leaf = false;
        dfs(v[i]);
    }
    trees[x] = build();

}


int main() {
    E = 0;
    memset(start, -1, sizeof(start));

    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        scanf("%d", &key[i]);
        query.clear();
    }
    for (int i = 0; i < N - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }


    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        query[x].push_back(make_pair(y, i));
    }

    memset(flag, true, sizeof(flag));

    int root = 1;
    dfs(root);

    for (int i = 0; i < M; ++ i)
        printf("%d\n", answer[i]);

    return 0;
}
