#pragma once

#include <vector>
#include <Windows.h>

struct ThreadData {
    std::vector<int>* array;
    int min_value;
    int max_value;
    double avg_value;
    int min_index;
    int max_index;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam);

DWORD WINAPI AverageThread(LPVOID lpParam);