#include "svg.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include <windows.h>
DWORD WINAPI GetVersion(void);
string make_info_text() {
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto R = GetVersion();
    printf("n = %lu\n", R);
    printf("n = %lx\n", R);
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = R & mask;
    printf("ver = %lu\n", version);
    DWORD platform = R >> 16;
    printf("ver2 = %lu\n", platform);
    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    printf("version_major = %lu\n", version_major);
    DWORD version_minor = version >> 8;
    printf("version_minor = %lu\n", version_minor);
    DWORD build;
    if ((R & 0x80000000) == 0)
    {
        build = platform;
        printf("build = %lu\n", build);

    }
    buffer << "Windows" << " " << "v" << " " << version_major << "." << version_minor << " " << "(build" << " " << build << ")" << endl;
    TCHAR storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(LPSTR(storage), &bufCharCount);
    buffer << "Computer name:" << " " << storage;
    return buffer.str();
}
void show_intervals(size_t interval, vector<size_t> bins)
{
    size_t max_bin = bins[0];

    for (size_t bin : bins)
    {
        if (bin > max_bin)
            max_bin = bin;
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
void svg_rect(double x, double y, double width, double height, string stroke , string fill){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
void
show_histogram_svg(const vector<size_t>& bins, size_t interval) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT + 30);
    double top = 0;
    double MAX = (IMAGE_WIDTH - TEXT_WIDTH) / BLOCK_WIDTH; //масштабирование
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
   
    size_t max_interval = interval;
    while (max_interval < max_bin)
    {
        max_interval = max_interval + interval;
    }

    size_t amount_intervals = max_interval / interval;

    for (size_t i = 0; i < amount_intervals; i++)
    {
        svg_text(TEXT_WIDTH + TEXT_LEFT + (interval * (i)*BLOCK_WIDTH), (IMAGE_HEIGHT - TEXT_BASELINE), to_string(interval * (i)));
    }
    svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE + 30, make_info_text());
    svg_end();
}

