#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

#define N 100000
#define M 1000

//#define N 10
//#define M 5

int f[N + 1];

int main() {
    srand(time(NULL));
    int T = 20;

    printf("%d\n", T);
    while (T --) {
        printf("%d\n", N);
        int all = N;
        for (int i = 1; i <= N; ++ i)
            f[i] = i;
        while (all > 1) {
            int x = (rand() % all) + 1;
            int y = (rand() % all) + 1;
            if (x == y) continue;
            printf("%d %d %d\n", f[x], f[y], rand() % 1000 + 1);
            int k = rand() & 1;
            if (k == 0) {
                int temp = f[x]; f[x] = f[all]; f[all] = temp;
            }
            else {
                int temp = f[y]; f[y] = f[all]; f[all] = temp;
            }
            -- all;
        }
        printf("%d\n", M);
        for (int i = 0; i < M; ++ i) {
            int x = (rand() % N) + 1;
            int y = (rand() % N) + 1;
            int v = rand() % 100 + 1;
            printf("%d %d %d\n", x, y, v);
        }
    }
    return 0; 
}
