#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <execution>
#include <random>

void fill_vec(std::vector<int>& vec) {

    std::random_device rd;
    std::mt19937 gen;//из библиотеки random генератор случ.чисел
    std::uniform_int_distribution<int> dist(0, 9);//равномерно распределяем его
    std::generate(std::execution::par, vec.begin(), vec.end(), [&]()
        {
            return dist(gen);
        });
}

void sum_vec(std::vector<int>& vec1, std::vector<int>& vec2, int size, int threads)
{
    std::vector<int> res(size);
    auto sum([&]()
        {
            for (int i = 0; i < size; ++i)
            {
                res[i] = vec1[i] + vec2[i];
            }
        });

    std::vector<std::thread> th;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threads; ++i)
    {
        th.push_back(std::thread(sum));
    }
    for(auto& t:th)
    {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << time.count() << "s" "\t";
}