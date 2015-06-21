#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

#define N 10

int f[N + 1];

int main() {
    srand(time(NULL));
    printf("1\n");
    printf("\n");
    printf("%d\n", N);
    /*
    for (int i = 1; i <= N - 1; ++ i)
        printf("%d %d\n", i, i + 1);
    */
    int all = N;
    for (int i = 1; i <= N; ++ i)
        f[i] = i;
    while (all > 1) {
        int x = (rand() % all) + 1;
        int y = (rand() % all) + 1;
        if (x == y) continue;
        printf("%d %d\n", f[x], f[y]);
        int k = rand() & 1;
        if (k == 0) {
            int temp = f[x]; f[x] = f[all]; f[all] = temp;
        }
        else {
            int temp = f[y]; f[y] = f[all]; f[all] = temp;
        }
        -- all;
    }
    return 0; 
}