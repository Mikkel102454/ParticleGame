#include <cstdlib>

int random_val_int(int lower, int upper)
{
    if (upper < lower) {
        int tmp = lower;
        lower = upper;
        upper = tmp;
    }
    return (rand() % (upper - lower + 1) + lower);
}
