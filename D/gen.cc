#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N1 = 1000000000;
const int N2 = 1000;
const int P = 9973;
const int M = 10000;

int main() {
    srand(time(NULL));
    for (int i = 0; i < M; ++ i) {
        int k = rand() % 4 + 1;
        int x;
        if (k <= 2)
            x = rand() % N1 + 1;
        else
            x = rand() % N2 + 1;

        printf("%d %d %d\n", k, x, P);
    }

    return 0;
}