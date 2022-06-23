#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <thread>
#include <numeric>

const int MIN_MAX_MS_TO_SLEEP = 7;
const int AVERAGE_MS_TO_SLEEP = 12;

struct MinMax
{
    int min;
    int max;
};

void min_max(std::vector<int>& vec, MinMax& result)
{
    result.min = vec[0];
    result.max = vec[0];
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] > result.max)
        {
            result.max = vec[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(MIN_MAX_MS_TO_SLEEP));

        if (vec[i] < result.min)
        {
            result.min = vec[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(MIN_MAX_MS_TO_SLEEP));
    }
}

void average(std::vector<int>& vec, int& result)
{
    result = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        result += vec[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(AVERAGE_MS_TO_SLEEP));
    }
    result /= vec.size();
}

int main()
{
    std::cout << "Input array size: ";

    int size;
    std::cin >> size;
    std::vector<int> vec(size);

    std::cout << "Input array numbers:\n";

    for (int i = 0; i != size; i++)
    {
        std::cin >> vec[i];
    }

    MinMax minMax;
    std::thread minMaxThr(min_max, std::ref(vec), std::ref(minMax));
    int averageResult = 0;
    std::thread averageThr(average, std::ref(vec), std::ref(averageResult));
    minMaxThr.join();
    averageThr.join();

    std::replace(vec.begin(), vec.end(), minMax.min, averageResult);
    std::replace(vec.begin(), vec.end(), minMax.max, averageResult);


    for (auto num : vec)
    {
        std::cout << num << std::endl;
    }
}