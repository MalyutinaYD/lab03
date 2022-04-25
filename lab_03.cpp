// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "histogram.h"

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
void show_histogram_text(vector<size_t> bins, size_t interval)
{
    const size_t SCREEN_WIDHT = 80;
    const size_t MASK_ASTERISK = SCREEN_WIDHT - 3 - 1;
    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
            max_bin = bin;
    }

    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bin > MASK_ASTERISK)// если требуется масштабирование
        {
            height = MASK_ASTERISK * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
            cout << " ";
        if (bin < 10)
            cout << " ";
        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
    size_t max_interval = interval;
    while (max_interval < max_bin)
    {
        max_interval = max_interval + interval;
    }
    cout << "   " << "|";
    size_t amount_intervals = max_interval / interval;
    for (size_t i = 0; i < amount_intervals; i++)
    {
        for (size_t j = 0; j < (interval - 1); j++)
        {
            cout << "-";
        }
        cout << "|";
    }
    cout << endl;
    cout << "   " << 0;
    for (size_t i = 0; i < amount_intervals; i++)
    {
        for (size_t j = 0; j < (interval - 1); j++)
        {
            cout << " ";
        }
        if (i == 0)
            cout << interval;
        else
        {
            if (i == (amount_intervals - 1) && (amount_intervals != 1))
            {
                cout << max_interval;
            }
            else
                cout << " ";
        }
    }
    return;
}
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "#FF69B4", string fill = "#FFC0CB") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    double MAX = (IMAGE_WIDTH - TEXT_WIDTH) / BLOCK_WIDTH;
    size_t max_bin = bins[0];
    for (size_t bin : bins) {
        if (bin > max_bin) {
            max_bin = bin;
        }
    }
    for (size_t bin : bins) {
        double height = bin;
        if (max_bin > MAX) {
            height = MAX * (static_cast<double>(bin) / max_bin);
        }
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
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
