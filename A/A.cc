#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN    100000+1
#define MAXE    2*(MAXN)
#define min(X,Y)    ((X < Y) ? X : Y)

int N;

int E;
int v[MAXE];
int start[MAXN];
int nexte[MAXE];

bool visited[MAXN];
int enterT[MAXN];
int lowT[MAXN];
int DFSTime;
int root;

/*
void dfs(int x, int parent) {
    visited[x] = true;
    enterT[x] = lowT[x] = DFSTime; ++ DFSTime;
    for (int i = start[x]; i != -1; i = nexte[i]) {
        if (!visited[v[i]]) {
            dfs(v[i], x);
            lowT[x] = min(lowT[x], lowT[v[i]]);
        }
        else if (v[i] != parent)
            lowT[x] = min(lowT[x], enterT[v[i]]);
    }
}
*/

int Stack[MAXN];
int Ptrs[MAXN];

inline void dfs() {
    DFSTime = 0;
    memset(visited + 1, false, sizeof(bool) * N);
    int ESP = 1; Stack[0] = root;
    for (int i = 1; i <= N; ++ i)
        Ptrs[i] = start[i];
    while (ESP) {
        int x = Stack[ESP - 1];
        int &i = Ptrs[x];
        if (!visited[x]) {
            visited[x] = true;
            enterT[x] = lowT[x] = DFSTime; ++ DFSTime;
            //printf("visiting %d\n", x);
        }
        else {
            lowT[x] = min(lowT[x], lowT[v[i]]);
            i = nexte[i];
        }
        while (i != -1 && visited[v[i]]) {
            if (x == root || v[i] != Stack[ESP - 2]) 
                lowT[x] = min(lowT[x], enterT[v[i]]);
            i = nexte[i];
        }
        if (i == -1)
            -- ESP;
        else if (!visited[v[i]]) {
            Stack[ESP] = v[i]; ++ ESP;
        }
    }
    /*
    for (int i = 1; i <= N; ++ i)
        printf("%d, enter time = %d, low time = %d\n", i, enterT[i], lowT[i]);
    */
}

int Color[MAXN];
int colors;

int loops[MAXN];

int newE;
int newv[MAXE];
int newstart[MAXN];
int newnexte[MAXE];

void ContractGraph() {
    memset(Color + 1, -1, sizeof(int) * N);
    Color[root] = colors = 0;

    int ESP = 1; Stack[0] = root;
    while (ESP) {
        int x = Stack[ESP - 1]; -- ESP;
        for (int i = start[x]; i != -1; i = nexte[i]) {
            //printf("edge %d %d\n", x, v[i]);
            if (Color[v[i]] != -1) continue;
            if (lowT[v[i]] > enterT[x])
                Color[v[i]] = ++ colors;
            else
                Color[v[i]] = Color[x];
            //printf("color(%d) --> %d\n", v[i], Color[v[i]]);
            Stack[ESP] = v[i]; ++ ESP;
        }
    }
    /*
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = start[x]; i != -1; i = nexte[i]) {
            //printf("edge %d %d\n", x, v[i]);
            if (Color[v[i]] != -1) continue;
            if (lowT[v[i]] > enterT[x])
                Color[v[i]] = ++ colors;
            else
                Color[v[i]] = Color[x];
            //printf("color(%d) --> %d\n", v[i], Color[v[i]]);
            Q.push(v[i]);
        }
    }
    */

    memset(loops, 0, sizeof(int) * (colors + 1));
    newE = 0;
    memset(newstart, -1, sizeof(int) * (colors + 1));

    for (int u = 1; u <= N; ++ u)
        for (int i = start[u]; i != -1; i = nexte[i]) {
            if (Color[u] == Color[v[i]]) ++ loops[Color[u]];
            else {
                newv[newE] = Color[v[i]]; newnexte[newE] = newstart[Color[u]]; newstart[Color[u]] = newE; ++ newE;
            }
        }

/*
    printf("colors = %d\n", colors);
    for (int i = 1; i <= N; ++ i)
        printf("color(%d) = %d\n", i, Color[i]);
*/
}

int SGvalue[MAXN];

/*
int SG(int x, int parent) {
    if (SGvalue[x] != -1) return SGvalue[x];
    SGvalue[x] = (loops[x] >> 1) & 1;
    for (int i = 0; i < Graph[x].size(); ++ i)
        if (Graph[x][i] != parent) SGvalue[x] ^= 1 + SG(Graph[x][i], x);
    return SGvalue[x];
}
*/

inline void SG() {
    memset(SGvalue, -1, sizeof(int) * (colors + 1));
    int ESP = 1; Stack[0] = root;
    Ptrs[root] = -1;
    while (ESP) {
        int x = Stack[ESP - 1];
        if (SGvalue[x] == -1) {
            SGvalue[x] = -1000;
            for (int i = newstart[x]; i != -1; i = newnexte[i])
                if (newv[i] != Ptrs[x]) {
                    Stack[ESP] = newv[i]; ++ ESP;
                    Ptrs[newv[i]] = x;
                }
        }
        else {
            if (SGvalue[x] == -1000) {
                SGvalue[x] = (loops[x] >> 1) & 1;
                for (int i = newstart[x]; i != -1; i = newnexte[i])
                    if (newv[i] != Ptrs[x])
                        SGvalue[x] ^= 1 + SGvalue[newv[i]];
            }
            -- ESP;
        }
    }
}

int mapping[MAXN];

inline void solve() {
    int n;
    scanf("%d", &n);
    //printf("n = %d\n", n);
    N = 1;

    bool ground = false;
    // 1 --> ground
    for (int i = 1; i <= n; ++ i) {
        int k;
        scanf("%d", &k);
        if (k == 1) {
            mapping[i] = 1;
            ground = true;
        }
        else
            mapping[i] = ++ N;
    }

/*
    for (int i = 1; i <= n; ++ i)
        printf("mapping(%d) = %d\n", i, mapping[i]);
*/

    E = 0;
    memset(start + 1, -1, sizeof(int) * N);
    for (int i = 0; i < n - 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        //printf("%d %d --> ", x, y);
        x = mapping[x]; y = mapping[y];
        //printf("%d %d\n", x, y);
        v[E] = y; nexte[E] = start[x]; start[x] = E; ++ E;
        v[E] = x; nexte[E] = start[y]; start[y] = E; ++ E;
    }
    /*
    for (int i = start[13]; i != -1; i = nexte[i])
        printf("EEEE 13 %d\n", v[i]);
    */

    if (!ground) {
        printf("0\n"); return;
    }

/*
    DFSTime = 0;
    root = 1;
    memset(visited, false, sizeof(visited));
    dfs(root, -1);
*/
    root = 1;
    dfs();

    ContractGraph();
//    printf("here\n");

    root = 0;
    //memset(SGvalue, -1, sizeof(SGvalue));
    //int ans = SG(root, -1);
    SG();


/*
    for (int i = 0; i <= colors; ++ i)
        printf("SG(%d) = %d\n", i, SGvalue[i]);
    printf("SG = %d\n", SGvalue[root]);
*/

    //printf("SG = %d\n", SGvalue[root]);
    if (SGvalue[root]) printf("1\n"); else printf("0\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T --) solve();
    return 0;
}