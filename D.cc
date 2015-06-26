#include <cstring>
#include <cstdio>

using namespace std;

//int X, Y;

//void extended_euclidean(int, int) __attribute__((optimize("-O2")));
/*
void extended_euclidean(int a, int b) {
    if (b == 0) {
        X = 1; Y = 0;
        return;
    }
    extended_euclidean(b, a % b);
    int k = X; X = Y; Y = k;
    Y = Y - (a / b) * X;
} 
*/


inline int inverse(int b, int MOD){
    int a = MOD, x1 = 0, x2 = 1, q;
    while (1){
        q = a / b, a %= b;
        if (!a) return (x2 + MOD) % MOD;
        x1 -= (q * x2) % MOD;
        if (x1 < 0) x1 += MOD;

        q = b / a, b %= a;
        if (!b) return (x1 + MOD) % MOD;
        x2 -= (q * x1) % MOD;
        if (x2 < 0) x2 += MOD;
    }
}

#define MAXN 1000+1

int A[MAXN];

int f[MAXN][MAXN];

int main() {
    int k, n, p;
    //memset(f[0], 0, sizeof(f[0]));
    A[0] = A[1] = 1;
    while (scanf("%d%d%d", &k, &n, &p) != EOF) {
        int ans;
        int base;
        if (k == 1) {
            ans = 1;
            int y = n - 2;
            for (base = n % p; y; base = (base * base) % p, y >>= 1)
                if (y & 1) ans = (ans * base) % p;
        }
        else if (k == 2) {
            ans = 1;
            int y = n - 1;
            for (base = n % p; y; base = (base * base) % p, y >>= 1)
                if (y & 1) ans = (ans * base) % p;
        }
        else {
            int i, j;
            for (i = 1; i < n; ++ i) {
                long long total = 0;
                for (j = 1; j <= i; ++ j) {
                    f[i][j] = f[i - j][j] + A[i + 1 - j];
                    total = total + (long long)j * f[i][j] * A[j];
                }
                if (total % i == 0) {
                    total = total / i;
                }
                else
                    total = total * inverse(i, p);

                A[i + 1] = total % p;
            }
            ans = A[n];
            if (k == 4) {
                long long tempA = 0;
                int mid = n >> 1;
                for (i = 1; i <= mid; ++ i)
                    tempA = tempA + A[i] * A[n - i];
                tempA = tempA % p;
                ans = ans - (int)tempA;
                if (ans < 0) ans += p;
                if ((n & 1) == 0) {
                    int tempB = ((A[mid] + 1) * A[mid]) >> 1;
                    ans = (ans + tempB) % p;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}