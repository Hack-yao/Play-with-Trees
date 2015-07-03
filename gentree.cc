#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

//#define MAXN 27 
#define N 100000 
//#define M 100000

//#define N 10
//#define M 5

int f[N + 1];

int main() {
    srand(time(NULL));
    //int M = 100000;
    int T = 20;

    printf("%d\n", T);
    while (T --) {
        //int N = rand() % MAXN + 1;
        //printf("\n1\n");


        //printf("%d %d\n", N, N - 1);

        printf("%d\n", N);

        /*
        printf("1");
        for (int i = 0; i < N - 1; ++ i)
            printf(" 0");
        printf("\n");
        */
        for (int i = 0; i < N - 1; ++ i)
            if (rand() % 100 < 10)
                printf("%d ", 1);
            else
                printf("%d ", 0);
        if (rand() % 100 < 10)
            printf("%d\n", 1);
        else
            printf("%d\n", 0);

        int all = N;
        /*
        for (int i = 1; i < N; ++ i)
            printf("%d %d %d\n", i, i + 1, rand() % 1000 + 1);
        */
        for (int i = 1; i <= N; ++ i)
            f[i] = i;
        while (all > 1) {
            int x = (rand() % all) + 1;
            int y = (rand() % all) + 1;
            if (x == y) continue;
            printf("%d %d\n", f[x], f[y]);
            //printf("%d %d %d\n", f[x], f[y], rand() % 20000 + 1);
            int k = rand() & 1;
            if (k == 0) {
                int temp = f[x]; f[x] = f[all]; f[all] = temp;
            }
            else {
                int temp = f[y]; f[y] = f[all]; f[all] = temp;
            }
            -- all;
        }
        /*
        M = M - N + 1;
        while (M) {
            int x = (rand() % N) + 1;
            int y = (rand() % N) + 1;
            if (x == y) continue;
            -- M;
            printf("%d %d %d\n", x, y, rand() % 20000 + 1);
        }
        */
        /*
        printf("%d\n", M);
        for (int i = 0; i < M; ++ i) {
            int x = (rand() % N) + 1;
            int y = (rand() % N) + 1;
            int v = rand() % 100 + 1;
            printf("%d %d %d\n", x, y, v);
        }
        */
    }
    return 0; 
}
