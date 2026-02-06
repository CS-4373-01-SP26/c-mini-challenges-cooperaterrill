#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
// from https://en.wikipedia.org/wiki/Approximations_of_pi#Development_of_efficient_formulae
void approxPi(int max)
{
    int k = 3; // begin with a 3-gon
    // from https://en.wikipedia.org/wiki/Equilateral_triangle#Relationship_with_circles
    //  know: sqrt(3)R = s = (1/3)pk
    //  know: 6r/sqrt(3) = s = (1/3)Pk
    //  so p3 = 3sqrt(3) * R
    //  and P3 = 18/sqrt(3) * r
    // letting R = r = 1/2,

    double pk = sqrt(3) * 3 / 2;    // perimeter of inscribed kgon
    double Pk = 18.0 / sqrt(3) / 2; // perimeter of circumscribed kgon

    while (k < max)
    {
        double P2k = 2 * pk * Pk / (pk + Pk);
        double p2k = sqrt(pk * P2k);
        pk = p2k;
        Pk = P2k;
        k *= 2;
    }
    printf("pi is in the range [%.8f, %.8f]\n", pk, Pk);
}
int main()
{
    time_t start, end;
    time(&start);
    approxPi(100);
    time(&end);
    double execTime = difftime(end, start);
    printf("took %f to compute\n", execTime);
    return 0;
}