/* test of fft*g.c */

#include <math.h>
#include <stdio.h>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

/* random number generator, 0 <= RND < 1 */
#define RND(p) ((*(p) = (*(p) * 7141 + 54773) % 259200) * (1.0 / 259200.0))

#ifndef NMAX
#define NMAX 8192
#define NMAXSQRT 64
#endif

void cdft(int, int, double *, int *, double *);
void rdft(int, int, double *, int *, double *);
void ddct(int, int, double *, int *, double *);
void ddst(int, int, double *, int *, double *);
void dfct(int, double *, double *, int *, double *);
void dfst(int, double *, double *, int *, double *);
void putdata(int nini, int nend, double *a);
double errorcheck(int nini, int nend, double scale, double *a);


int main()
{
    int n, ip[NMAXSQRT + 2];
    double a[NMAX + 1], w[NMAX * 5 / 4], err;
    int i;

    printf("data length n=? (must be 2^m)\n");
    scanf("%d", &n);
    for (i=0;i<sqrt(n)+2;i++) ip[i] = 0;
    ip[0] = 0;

    /* check of CDFT */
    putdata(0, n - 1, a);
    cdft(n, 1, a, ip, w);
    for (i=0;i<sqrt(n)+2;i++) {
        if (ip[i] != 0) 
          printf("%3d %08x\n", i, ip[i]);
    }
    cdft(n, -1, a, ip, w);
    err = errorcheck(0, n - 1, 2.0 / n, a);
    printf("cdft err= %g \n", err);

    /* check of RDFT */
    //putdata(0, n - 1, a);
    //rdft(n, 1, a, ip, w);
    //rdft(n, -1, a, ip, w);
    //err = errorcheck(0, n - 1, 2.0 / n, a);
    //printf("rdft err= %g \n", err);

    return 0;
}


void putdata(int nini, int nend, double *a)
{
    int j, seed = 0;

    for (j = nini; j <= nend; j++) {
        a[j] = RND(&seed);
    }
}


double errorcheck(int nini, int nend, double scale, double *a)
{
    int j, seed = 0;
    double err = 0, e;

    for (j = nini; j <= nend; j++) {
        e = RND(&seed) - a[j] * scale;
        err = MAX(err, fabs(e));
    }
    return err;
}

