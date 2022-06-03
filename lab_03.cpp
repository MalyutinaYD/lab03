// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;
 
vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    size_t bin_count;
    in >> bin_count;


    return data;
}


int main()
{
    //ввод данных
    size_t number_count;
    cerr << " enter number count: ";
    cin >> number_count;
    

    cerr << " enter numbers: ";
    const auto input = read_input(cin);
   
    size_t bin_count;
    cerr << " enter bin count: ";
    cin >> bin_count;
    size_t interval;
    cerr << "enter size of interval - ";
    cin >> interval;
   
    if (proverka_intervals(interval) == false)
    {
        cerr << "ERROR";
        return 1;
    }
    //расчет гиcтограммы
    double min, max;
    find_minmax(input.numbers, min, max);

     const auto bins = make_histogram(input.numbers, min, max, input.bin_count, number_count);
    //вывод данных
    
    
    show_histogram_svg(bins, interval);
    
   




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
