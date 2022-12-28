#include <stdio.h>

int main()
{
    int c1, c2, c3;
    float r1, r2, r3, triangle_perimeter, trapeze_area;

    scanf("%f%f%f", &r1, &r2, &r3);

    c1 = r1 < (r2 + r3);
    c2 = r2 < (r1 + r3);
    c3 = r3 < (r1 + r2);
    if (c1 && c2 && c3)
    {
        triangle_perimeter = r1 + r2 + r3;
        printf("Perimetro = %.1f\n", triangle_perimeter);
    }
    else
    {
        trapeze_area = ((r1 + r2) * r3) / 2;
        printf("Area = %.1f\n", trapeze_area);
    }
    return 0;
}