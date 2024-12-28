#include <iostream>

void showbits(unsigned long x, int n) {
    if (--n) showbits(x >> 1, n);
    putchar("01"[x & 1]);
}

int main() {
    long unsigned lu;
    float x = 37.0681;
    lu = *(long *) &x;

    printf("%f -> ", x);
    showbits(lu, 32);
    printf("\n");


    long unsigned y;
    float z = 1.0;
    while (z > 0) {
        y = *(long *) &z;
        z = z / 2;
    }
    //Liczba na tyle mala ze juz nie ma mniejszej pomiedzy ta a zerem
    showbits(y, 32);
    printf("\n");

    return 0;
}
