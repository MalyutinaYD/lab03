// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;
vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

vector <size_t> make_histogram(vector <double> numbers, double min, double max, size_t bin_count, size_t number_count)
{
    double bin_size = (max - min) / bin_count;
    vector <size_t> bins(bin_count, 0);

    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto  lo = min + j * bin_size;
            auto  hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }

    }
    return bins;
}

int main()
{
    //ввод данных
    size_t number_count;
    cerr << " enter number count: ";
    cin >> number_count;

    cerr << " enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << " enter bin count: ";
    cin >> bin_count;
    size_t interval;
    cerr << " enter interval - ";
    cin >> interval;
    if ((interval < 4) || (interval > 9))
    {
        cout << "ERROR";
        exit(0);
    }
    //расчет гистограммы

    double min, max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, min, max, bin_count, number_count);
    //вывод данных
    
    show_histogram_svg(bins);
    
    




    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
