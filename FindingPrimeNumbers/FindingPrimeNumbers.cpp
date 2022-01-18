#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#include <vector>


bool IsPrime(unsigned int num)
{
    if (num <= 1)
        return false;

    if (num == 2 || num == 3)
        return true;

    for (int i = 2; i < num; ++i)
    {
        if ((num % i) == 0)
            return false;
    }

    return true;
}

int CountPrime(int start, int end)
{
    int count = 0;

    for (int i = start; i <= end; ++i)
    {
        if (IsPrime(i))
            count++;
    }

    return count;
}

int main()
{
    const int MAX_NUMBER = 100'0000;

    std::vector<std::thread> threads;

    int coreCount = std::thread::hardware_concurrency();

    int interval = (MAX_NUMBER / coreCount) + 1;

    std::atomic<int> countSum = 0;

    int start = 0;
    int end = interval;
    for (int i = 0; i < coreCount; ++i)
    {
        threads.emplace_back([start, end, &countSum]
            {
                countSum += CountPrime(start, end);
            });

        start = end + 1;
        end = std::min(MAX_NUMBER, start + interval);
    }

    for (std::thread& t : threads)
    {
        t.join();
    }

    std::cout << countSum << std::endl;

    std::cout << CountPrime(0, MAX_NUMBER) << std::endl;

    
}

