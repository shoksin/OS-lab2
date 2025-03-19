#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include "threads.h"

int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    if (size <= 0) {
        std::cerr << "Array size must be positive" << std::endl;
        return 1;
    }

    std::vector<int> array(size);
    std::cout << "Enter " << size << " integers:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    std::cout << "Original array: ";
    for (int value : array) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    ThreadData threadData;
    threadData.array = &array;

    HANDLE hMinMax = CreateThread(
        NULL,                   // Атрибуты безопасности по умолчанию
        0,                      // Размер стека по умолчанию
        MinMaxThread,           // Функция потока
        &threadData,            // Аргумент функции потока
        0,                      // Флаги создания по умолчанию
        NULL                    // ID потока не нужен
    );

    if (hMinMax == NULL) {
        std::cerr << "Failed to create min_max thread" << std::endl;
        return 1;
    }

    HANDLE hAverage = CreateThread(
        NULL,                   // Атрибуты безопасности по умолчанию
        0,                      // Размер стека по умолчанию
        AverageThread,          // Функция потока
        &threadData,            // Аргумент функции потока
        0,                      // Флаги создания по умолчанию
        NULL                    // ID потока не нужен
    );

    if (hAverage == NULL) {
        std::cerr << "Failed to create average thread" << std::endl;
        CloseHandle(hMinMax);
        return 1;
    }

    //Ожидание завершения потоков min_max и average
    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    // Закрытие дескрипторов потоков
    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    std::vector<double> result(size);

    for (size_t i = 0;i<array.size();i++){
        result[i] = array[i];
        if (i == threadData.min_index || i == threadData.max_index) {
            result[i] = threadData.avg_value;
        }
    }

    std::cout << "Modified array: ";
    for (double value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}