#include <vector>

/* Problem:
Given an ice cream shop inventory as an array of positive integers
representing costs, return the maximum number of items you can buy,
given an amount of money.

Assume that the range of costs is comparable to or less than the total
number of items, and implement an O(n) solution.
*/

// Your solution:
int max_ice_cream(const std::vector<int>& costs, int money) {
    int maxCost = 0;
    for (const int cost : costs) {
        maxCost = std::max(cost, maxCost);
    }
    std::vector<int> items(maxCost + 1, 0);
    for (const int cost : costs) {
        ++items[cost];
    }
    int itemCount = 0;
    for (int i = 0; i < int(items.size()); ++i) {
        while (items[i] > 0 && money >= i) {
            --items[i];
            ++itemCount;
            money -= i;
        }
    }
    return itemCount;
}

#include <cassert> 

int main() {
    assert(max_ice_cream({ 1, 2, 3, 4, 5 }, 7) == 3);
    assert(max_ice_cream({ 1, 6, 3, 2, 5, 4 }, 10) == 4);
    assert(max_ice_cream({ 10, 6, 8, 7, 5 }, 9) == 1);
    assert(max_ice_cream({ 1, 1, 1, 1, 1 }, 5) == 5);
    assert(max_ice_cream({ 1, 2, 3, 4, 5 }, 0) == 0);
    assert(max_ice_cream({}, 100) == 0);
}