#include "threads.h"
#include <iostream>
#include <algorithm>

DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    std::vector<int>& array = *(data->array);

    if (array.empty()) {
        return 0;
    }

    data->min_value = array[0];
    data->max_value = array[0];
    data->min_index = 0;
    data->max_index = 0;

    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] < data->min_value) {
            data->min_value = array[i];
            data->min_index = i;
        }
        Sleep(7);

        if (array[i] > data->max_value) {
            data->max_value = array[i];
            data->max_index = i;
        }
        Sleep(7);
    }

    std::cout << "Min element: " << data->min_value << " at index " << data->min_index << std::endl;
    std::cout << "Max element: " << data->max_value << " at index " << data->max_index << std::endl;

    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    std::vector<int>& array = *(data->array);

    if (array.empty()) {
        data->avg_value = 0;
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array[i];
        Sleep(12);
    }

    data->avg_value = static_cast<double>(sum) / array.size();
    std::cout << "Average value: " << data->avg_value << std::endl;

    return 0;
}