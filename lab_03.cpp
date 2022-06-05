// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <curl/curl.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <sstream>
#include <string>

using namespace std;
 
vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
Input
read_input(istream& in, bool prompt) {
    Input data;
    if (true)
    {
        cerr << "Enter number count: ";
        size_t number_count;
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter bin count: ";
        size_t bin_count;
        in >> bin_count;

        size_t interval;
        cerr << "enter size of interval - ";
        in >> interval;
    }
    else
    {
        size_t number_count;
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        size_t bin_count;
        in >> bin_count;
        size_t interval;
        in >> interval;
    }


    return data;
}
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input
download(const string& address, int argc, char* argv[]) {
    stringstream buffer;
    if (argc > 1)
    {
        CURL* curl = curl_easy_init();
        if (curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
           

            if (res != CURLE_OK)
            {
                cerr << curl_easy_strerror(res);
                exit(1);
            }
        }
        
    }
    curl_global_init(CURL_GLOBAL_ALL);

    return read_input(buffer, false);
}


int main(int argc, char* argv[])
{
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    printf("n = %08x\n", 0x1234567);
    return 0;
    Input input;
    if (argc > 1) {
        input = download(argv[1], argc, argv);
    }
    else {
        input = read_input(cin, true);
    }
    //ввод данных
    
   
   
    if (proverka_intervals(input.interval) == false)
    {
        cerr << "ERROR";
        return 1;
    }
    //расчет гиcтограммы
    double min, max;
    find_minmax(input.numbers, min, max);

     const auto bins = make_histogram(input.numbers, min, max, input.bin_count, input.number_count);
    //вывод данных
    
    
    show_histogram_svg(bins, input.interval);
    
   




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
