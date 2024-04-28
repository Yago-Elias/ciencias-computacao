#include <math.h>
#include "bhaskara.h"

int bhaskara(float a, float b, float c, float *x1, float *x2) {
    float delta = 0;
    
    delta = b*b - 4 * a * c;
    //delta = pow(b, 2) - 4 * a * c;

    if (delta > 0) {
        *x1 = (-b + sqrt(delta)) / (2*a);
        *x2 = (-b - sqrt(delta)) / (2*a);
        return 2;
    }
    else if (delta == 0) {
        *x1 = (-b + sqrt(delta)) / (2*a);
        return 1;
    }
    
    return 0;
}





