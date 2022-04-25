#include "histogram.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() != 0) {
        min = numbers[0];
        max = numbers[0];
        for (double number : numbers)
        {
            if (min > number)
            {
                min = number;
            }
            if (max < number)
            {
                max = number;
            }
        }

    }
}
vector <double> input_intervals()
{
    size_t interval;
    cerr << " enter interval - ";
    cin >> interval;
    if ((interval < 4) || (interval > 9))
    {
        cout << "ERROR";
        exit(0);
    }
}