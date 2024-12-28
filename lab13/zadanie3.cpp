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
        x[i] = i * 2.0 * M_PI / (n - 1);
        y[i] = (1.2 * sin(x[i]) * sin(x[i]) + 0.5 * sin(x[i])) * (x[i] * x[i] - 2 * x[i] + 1);
        printf("%g %g\n", x[i], y[i]);
    }
    // Tworzenie splinu: gsl_interp_cspline_periodic implementuje warunki:
    // s'(x[0])=s'(x[n-1]), s''(x[0])=s''(x[n-1])
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline_periodic, n);
    gsl_spline_init(spline, x, y, n);

    printf("\n*** Wyniki: wartości obliczonego splajnu w wybranych punktach ***\n");
    for (xi = x[0]; xi < x[n - 1]; xi += 0.1) {
        yi = gsl_spline_eval(spline, xi, acc);
        printf("%g %g\n", xi, yi);
    }

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);

    return 0;
}
