#include "Primes.h"
#include <iostream>
#include <vector>

using namespace std;

const int MIN_BORDER = 2;
const int MAX_BORDER = 100000000;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    set<int> primes{};
    if (upperBound < MIN_BORDER || upperBound > MAX_BORDER)
    {
        return primes;
    }

    //плюс 1 добавляется так как в векторе numbers счет элементов идет от нуля до upperBound включительно
    vector<bool> numbers((upperBound) / 2 + 1, true);

    //увеличить шаг
    for (int i = 2; i * i <= upperBound/2; i++) 
    {
        if (numbers[i])
        {
            for (int j = i * i; j <= upperBound/2; j += i) 
            {
                numbers[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound/2; i++) 
    {
        if (numbers[i])
        {
            primes.insert(i*2-1);
        }
    }
    return primes;
}
