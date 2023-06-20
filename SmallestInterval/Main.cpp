#include <vector>

/* Problem:
Given k sequences of sorted integers, determine the smallest closed interval
that covers at least one element from each list.

For intervals of the same size should be ordered based
on their lower bound value (i.e. [0,2]<[1,3]).
*/

// Your solution:
std::pair<int, int> smallest_interval(const std::vector<std::vector<int>>& nums) {
    std::vector<int> starts;
    for (const auto& seq : nums)
    {
        for (const int num : seq)
        {
            starts.push_back(num);
        }
    }
    int start = -1, length = -1;
    for (int cStart : starts)
    {
        int cLength = 0;
        for (const auto& seq : nums)
        {
            if (cStart > seq.back())
            {
                cLength = -1;
                break;
            }
            for (const int num : seq)
            {
                if (num >= cStart)
                {
                    cLength = std::max(num - cStart, cLength);
                    break;
                }
            }
        }
        if (cLength == -1)
        {
            continue;
        }
        if (start == -1)
        {
            start = cStart;
            length = cLength;
        }
        else if (length > cLength || (length == cLength && start > cStart))
        {
            start = cStart;
            length = cLength;
        }
    }
    return { start, start + length };
}

#include <cassert>
#include <iostream>

int main() {
    assert(smallest_interval({ {1,2,3}, {1,2,3}, {1,2,3} }) == std::make_pair(1, 1));
    assert(smallest_interval({ {4,10,15,24,26}, {0,9,12,20}, {5,18,22,30} }) == std::make_pair(20, 24));
    assert(smallest_interval({ {1,2,3} }) == std::make_pair(1, 1));
    assert(smallest_interval({ {1,2,3}, {4,5,6,7}, {8,9,10,11,12} }) == std::make_pair(3, 8));
    assert(smallest_interval({ {-1, 2, 3}, {-4, -3, -2, 1}, {-7, -6, -5, 4} }) == std::make_pair(1, 4));
    assert(smallest_interval({ {7, 7, 7, 7}, {7, 7, 7, 7}, {7, 7, 7, 7} }) == std::make_pair(7, 7));
    assert(smallest_interval({ {1}, {2}, {3} }) == std::make_pair(1, 3));
}