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
#define Base    1000000000
#define Capacity    100

struct BigInt {
    int len;
    int data[Capacity];

    BigInt() : len(0) {}
    BigInt(int key) {
        for (len = 0; key; key /= Base)
            data[len ++] = key % Base;
    }

    BigInt & operator = (int key) {
        for (len = 0; key; key /= Base)
            data[len ++] = key % Base;
        return *this;
    }

    BigInt & operator = (const BigInt &key) {
        len = key.len;
        memcpy(data, key.data, len * sizeof(int));
        return *this;
    }

    void print() {
        if (len == 0) {
            printf("0");
            return;
        }
        printf("%d", data[len - 1]);
        for (int i = len - 2; i >= 0; -- i)
            for (int j = Base / 10; j; j /= 10)
                printf("%d", data[i] / j % 10);
    }

    int & operator [] (int index) { return data[index]; }
    int operator [] (int index) const { return data[index]; }
};

BigInt operator + (const BigInt &A, const BigInt &B) {
    BigInt ret;
    int i;
    int carry = 0;
    for (i = 0; i < A.len || i < B.len || carry; ++ i) {
        if (i < A.len) carry += A[i];
        if (i < B.len) carry += B[i]; 
        ret[i] = carry % Base;
        carry /= Base;
    }
    ret.len = i;
    return ret;
}

BigInt operator - (const BigInt &A, const BigInt &B) {
    BigInt ret;
    int carry = 0;
    ret.len = A.len;
    for (int i = 0; i < ret.len; ++ i) {
        ret[i] = A[i] - carry;
        if (i < B.len) ret[i] -= B[i];
        if (ret[i] < 0) carry = 1, ret[i] += Base;
        else carry = 0;
    }
    while (ret.len && ret[ret.len] == 0) -- ret.len;
    return ret;
}

BigInt operator * (const BigInt &A, const int B) {
    if (B == 0) return 0;
    BigInt ret;
    long long carry = 0;
    int i;
    for (i = 0; i < A.len || carry; ++ i) {
        if (i < A.len) carry += (long long)(A[i]) * B;
        ret[i] = carry % Base;
        carry /= Base;
    }
    ret.len = i;
    return ret;
}

BigInt operator * (const BigInt &A, const BigInt &B) {
    if (B.len == 0 || A.len == 0) return 0;
    BigInt ret;
    for (int i = 0; i < A.len; ++ i) {
        long long carry = 0;
        for (int j = 0; j < B.len || carry; ++ j) {
            if (j < B.len) carry += (long long)A[i] * B[j];
            if (i + j < ret.len) carry += ret[i + j];
            if (i + j >= ret.len) ret[ret.len ++] = carry % Base;
            else ret[i + j] = carry % Base;
            carry /= Base;
        }
    }
    return ret;
}

BigInt operator / (const BigInt &A, const int B) {
    BigInt ret;
    long long C = 0;
    for (int i = A.len - 1; i >= 0; -- i) {
        C = (C * Base) + A[i];
        ret[i] = C / B;
        C %= B;
    }
    ret.len = A.len;
    while (ret.len && ret[ret.len - 1] == 0) -- ret.len;
    return ret;
}

BigInt operator % (const BigInt &A, const int B) {
    long long C = 0;
    for (int i = A.len - 1; i >= 0; -- i) {
        C = (C * Base) + A[i];
        C %= B;
    }
    return C;
}

/*
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
*/

#define MAXN 1000+1

//int A[MAXN];

//int f[MAXN][MAXN];

BigInt A[MAXN];

void preprocess() {
    int n = 1000;
    A[0] = 1; A[1] = 1;
    for (int i = 1; i < n; ++ i) {
        A[i + 1] = 0;
        for (int j = 1; j <= i; ++ j) {
            BigInt sum = 0;
            for (int k = 1; k <= i / j; ++ k)
                sum = sum + A[i + 1 - j * k];
            sum = sum * A[j];
            sum = sum * j;
            A[i + 1] = A[i + 1] + sum;
        }
        A[i + 1] = A[i + 1] / i;
    }

    for (int i = 1; i <= 1000; ++ i) {
        A[i].print(); printf("\n");
    }
}

int main() {
    preprocess();
    /*
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
    */
    return 0;
}