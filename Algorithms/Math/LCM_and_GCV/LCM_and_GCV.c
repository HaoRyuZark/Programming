#include <stdio.h>

int gcd(int x, int y) {
    int res = 0;

    for (int i = 0; i <= x && i <= y; i++) {
        if (x % i == 0 && x % i == 0) {
            res = i;
        }
    }

    return res;
}

int gcd_euclid(int x, int y) {

    while (y != 0) {
        int res = y;
        y = x % y;
        x = res;
    }

    return x;
}

int lcm(int x, int y) {
    int fac = 1;
    int res = (x > y)? x : y;

    while (fac) {
      if (res % x == 0 && res % y == 0) {
          fac = 0;
          break;
      }
      res++;
    }
    return res;
}

int main(int argc, char* argv[]) {
    printf("Hello World\n");
    return 0;
}
