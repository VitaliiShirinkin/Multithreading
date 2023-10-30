
#include <iostream>
#include "Functions.h"
#include <thread>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <execution>
#include <random>

int main()
{
    (LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    int min_thread = 1;
    int max_thread = 16;
    int min_num = 1000;
    int max_num = 1000000;

    std::vector<int> vec1(max_num);
    std::vector<int> vec2(max_num);

    fill_vec(vec1);
    fill_vec(vec2);

    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << '\n' << '\n';
    std::cout << "\t\t" << "1000\t\t" << "10000\t\t" << "100000\t\t" << "1000000\t\t" << '\n';
    for (int t = min_thread; t <= max_thread; t *= 2) {

        std::cout << '\n' << t << " потоков:\t";
        for (int n = min_num; n <= max_num; n *= 10) {

            sum_vec(vec1, vec2, n, t);
        }
    }
    return 0;
}
