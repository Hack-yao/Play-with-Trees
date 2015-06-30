#include <cstring>
#include <cstdio>

using namespace std;

#define FOR(i, a, b) for (int i=int(a);i<int(b);++i)
#define REP_1(i, n) for (int i=1;i<=int(n);++i)

int MOD;

inline void INC(int &a, int b) { a += b; if (a >= MOD) a -= MOD; }
inline int ADD(int a, int b) { a += b; if (a >= MOD) a -= MOD; return a; }
inline void DEC(int &a, int b) { a -= b; if (a < 0) a += MOD; }
inline void MUL(int &a, int b) { a = a * b % MOD; }
inline int MULTIPLY(int a, int b) { return a * b % MOD; }

inline int POW(int a, int b) {
    if (b <= 0) return 1;
    a %= MOD;
    int ret = 1;
    while (b) {
       if (b & 1) MUL(ret, a); 
       MUL(a, a), b >>= 1;
    }
    return ret;
}
inline int _inverse(int b){
    int a = MOD, x1 = 0, x2 = 1, q;
    while (1){
        q = a / b, a %= b;
        if (!a) return (x2 + MOD) % MOD;
        DEC(x1, MULTIPLY(q, x2));

        q = b / a, b %= a;
        if (!b) return (x1 + MOD) % MOD;
        DEC(x2, MULTIPLY(q, x1));
    }
}
inline void DIV(int &a, int b) { MUL(a, _inverse(b)); }
inline int DIVIDE(int a, int b) { return MULTIPLY(a, _inverse(b)); }

const int MAXN = 1001;

int A[MAXN];

int f[MAXN][MAXN];
int N, K;

int main() {
    while (scanf("%d%d%d", &K, &N, &MOD) != EOF) {
        if (K == 1) {
            printf("%d\n", POW(N, N - 2));
        }
        else if (K == 2) {
            printf("%d\n", POW(N, N - 1));
        }
        else if (K == 3) {
            memset(A, 0, sizeof(A)); A[1] = 1;
            FOR(i, 1, N) {
                REP_1(j, i) {
                    f[i][j] = ADD(f[i - j][j], A[i + 1 - j]);
                    INC(A[i + 1], MULTIPLY(MULTIPLY(j, A[j]), f[i][j]));
                }
                DIV(A[i + 1], i);
            }
            printf("%d\n", A[N]);
        }
        else {
            memset(A, 0, sizeof(A)); A[1] = 1;
            FOR(i, 1, N) {
                REP_1(j, i){
                    f[i][j] = ADD(f[i - j][j], A[i + 1 - j]);
                    INC(A[i + 1], MULTIPLY(MULTIPLY(j, A[j]), f[i][j]));
                }
                DIV(A[i + 1], i);
            }
            int ans = A[N];
            REP_1(i, N >> 1)
                DEC(ans, MULTIPLY(A[i], A[N - i]));
            if (!(N & 1))
                INC(ans, (((A[N / 2] + 1) * A[N / 2]) / 2) % MOD);
            printf("%d\n", ans);
        }
    }
}