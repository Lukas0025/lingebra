#include "../parts/vector.h"
#include <cstdio>



int main() {
    auto v = lingebra::vector<float>(10, lingebra_const, 2);
    auto u = lingebra::vector<float>(10, lingebra_ones);

    printf("sum of V is %f\n", v.sum());
    printf("first element of V is %f", v[0]);

    return 0;
}