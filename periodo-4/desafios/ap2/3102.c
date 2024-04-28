#include <stdio.h>
#include <math.h>

float dAB(int *a, int *b) {
    int dx, dy;

    dx = b[0] - a[0];
    dy = b[1] - a[1];

    return sqrt((dx * dx + dy * dy));
}

float areaHeron(float a, float b, float c) {
    float p = (a + b + c) / 2;
    float ar = p * (p - a) * (p - b)  * (p - c);
    return sqrt(ar);
}

int main() {
    int n, c1[2], c2[2], c3[2];

    scanf("%d", &n);
    while (n--) {
        scanf("%d%d", &c1[0], &c1[1]);
        scanf("%d%d", &c2[0], &c2[1]);
        scanf("%d%d", &c3[0], &c3[1]);
        printf("%.3lf\n", areaHeron(dAB(c1, c2), dAB(c1, c3), dAB(c2, c3)));
    }

    return 0;
}
