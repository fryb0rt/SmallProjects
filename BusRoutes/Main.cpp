#include <vector>

/* Problem:
Given a list of bus routes, where route[i] = {b1,b2,b3} means that
bus i stops at stops b1, b2 and b3, determine the smallest number
of buses you need to reach the target bus stop starting at source.

Return -1 if the target is unreachable.
*/

// Your solution:

bool hasSameStop(const std::vector<int>& route1, const std::vector<int>& route2) {
    for (const int i : route1) {
        for (const int j : route2) {
            if (i == j) {
                return true;
            }
        }
    }
    return false;
}

int min_tickets(const std::vector<std::vector<int>>& routes, const int source, const int target) {
    if (source == target)
    {
        return 0;
    }
    std::vector<std::vector<int>> connections(routes.size());
    std::vector<int> busSource, busTarget;
    for (size_t i = 0; i < routes.size(); ++i) {
        connections[i].resize(routes.size(), -1);
        connections[i][i] = 0;
        for (const int stop : routes[i]) {
            if (stop == source) {
                busSource.push_back(int(i));
            }
            if (stop == target) {
                busTarget.push_back(int(i));
            }
        }
    }
    for (size_t i = 0; i < routes.size(); ++i) {
        for (size_t j = 1; j < routes.size(); ++j) {
            if (hasSameStop(routes[i], routes[j]) && i != j) {
                connections[i][j] = 1;
                connections[j][i] = 1;
            }
        }
    }
    for (size_t step = 0; step < routes.size(); ++step) {
        for (size_t i = 0; i < routes.size(); ++i) {
            for (size_t j = 1; j < routes.size(); ++j) {
                for (size_t k = 0; k < routes.size(); ++k) {
                    const int sum = connections[i][k] + connections[j][k];
                    if (connections[i][k] != -1 && connections[j][k] != -1 && (connections[i][j] == -1 ||
                        sum < connections[i][j])) {
                        connections[i][j] = sum;
                        connections[j][i] = sum;
                    }
                }
            }
        }
    }
    int minimum = -1;
    for (const int i : busSource)
    {
        for (const int j : busTarget)
        {
            if (connections[i][j] != -1)
            {
                minimum = minimum == -1 ? connections[i][j] + 1 : std::min(minimum, connections[i][j] + 1);
            }
        }
    }
    return minimum;
}

#include <cassert>

int main() {
    std::vector<std::vector<int>> routes1 = { {1, 2, 3}, {3, 4, 5}, {5, 6, 7} };
    assert(min_tickets(routes1, 3, 3) == 0);
    assert(min_tickets(routes1, 1, 3) == 1);
    assert(min_tickets(routes1, 1, 5) == 2);
    assert(min_tickets(routes1, 1, 9) == -1);
    assert(min_tickets(routes1, 1, 10) == -1);

    std::vector<std::vector<int>> routes2 = {};
    assert(min_tickets(routes2, 1, 2) == -1);

    std::vector<std::vector<int>> routes3 = { {1,2,3,4},{2,6,10,14},{3,6,13},{4,8,12,16},{5,9,13},{7,11,15},{14,15} };
    assert(min_tickets(routes3, 1, 7) == 4);
    assert(min_tickets(routes3, 1, 16) == 2);
    assert(min_tickets(routes3, 5, 7) == 5);
    return 0;
}