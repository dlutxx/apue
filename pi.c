#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(long n)
{
    double pi = 0;
    char sign = 1;
    double c=1.0;
    while (n-->0) {
        pi += sign/c;
        //printf("sign=%d, c=%f, pi=%f\n", sign, c, pi);
        sign *= -1;
        c += 2;
    }
    return pi*4;
}

double pitoprecision(int digits)
{
    double pi = 0, pi0 = 0, denom = 1.0, diff;
    double dec = pow(10, digits+1) * 4;
    char sign = 1;
    while (1) {
        pi += sign/denom;
        diff = dec * (pi - pi0);
        if ( diff < 1 && diff > -1) {
            break;
        }
        sign *= -1;
        denom += 2;
        pi0 = pi;
    }
    return pi * 4;
}

int main(int argc, char* argv[])
{
    int n = 5;
    if (argc>1) {
        n = strtol(argv[1], NULL, 10);
    }
    double pi = pitoprecision(n);
    printf("10**3=%f, pi(%d) is %1.20f\n", pow(10,3), n, pi);
    return 0;
}

