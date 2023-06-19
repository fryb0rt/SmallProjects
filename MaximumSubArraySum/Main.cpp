#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    int count;
    std::cout << " Count of numbers in array: ";
    std::cin >> count;
    std::cout << " Numbers: ";
    int sum = 0, maximum = 0;
    for (int i = 0; i < count; ++i)
    {
        int number;
        std::cin >> number;
        if (sum > 0)
        {
            sum += number;
        }
        else
        {
            sum = number;
        }
        maximum = std::max(sum, maximum);
    }
    std::cout << " Maximum sum: " << maximum << std::endl;
    return 0;
}