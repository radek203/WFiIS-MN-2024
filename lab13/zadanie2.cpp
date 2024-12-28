#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main(void) {
    int i, n = 10;
    double xi, yi, x[n], y[n];

    printf("\n*** Dane: węzły interpolacji ***\n");
    for (i = 0; i < n; i++) {
        x[i] = i + 0.5 * sin(i);
        y[i] = pow(i, 0.5) + 0.9 * cos(i * i);
        printf("%g %g\n", x[i], y[i]);
    }
    // Tworzenie splinu sześciennego (m=3): gsl_interp_cspline
    // Implementowany jest warunek brzegowy: s''(x[0])=0, s''(x[n-1])=0
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, n);
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline_init(spline, x, y, n);

    printf("\n*** Wyniki: wartości obliczonego splinu sześciennego (m=3) ***\n");
    for (xi = x[0]; xi < x[n - 1]; xi += 0.1) {
        yi = gsl_spline_eval(spline, xi, acc);
        printf("%g %g\n", xi, yi);
    }

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return 0;
}
