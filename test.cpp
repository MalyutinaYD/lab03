#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({ -15, -2, -33 }, min, max);
    assert(min == -33);
    assert(max == -2);
}
void
test_same() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 1, 1 }, min, max);
    assert(min == 1);
    assert(max == 1);
}
void
test_onenumber() {
    double min = 0;
    double max = 0;
    find_minmax({ 7 }, min, max);
    assert(min == 7);
    assert(max == 7);
}
void
test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({ }, min, max);
    assert(min == 0);
    assert(max == 0);
}
int
main() {
    test_positive();
    test_negative();
    test_same();
    test_onenumber();
    test_empty();
}