#include <vector>
#include <algorithm>

struct Job {
    int start_time;
    int end_time;
    int profit;
    bool operator<(const Job& other) const
    {
        return start_time < other.start_time;
    }
};

/* Problem:
Given a list of N jobs, each with a start time, end time and profit,
determine the maximum profit achievable by processing some jobs under
the constraint that none overlap.

Assume start and end times within the range {0..50000} and half-open
interval for start and end times, i.e. a job can start at the end
time of a previous job.
*/

// Your solution:
int most_profit(std::vector<Job> jobs) {
    std::sort(jobs.begin(), jobs.end());
    std::vector<int> profits(jobs.size(), 0);
    for (int i = 0; i < int(jobs.size()); ++i)
    {
        profits[i] = jobs[i].profit;
        for (int j = 0; j < i; ++j)
        {
            if (jobs[j].end_time <= jobs[i].start_time)
            {
                profits[i] = std::max(profits[i], jobs[i].profit + profits[j]);
            }
        }
    }
    int maxProfit = 0;
    for (const int profit: profits)
    {
        maxProfit = std::max(profit, maxProfit);
    }
    return maxProfit;
}

#include <cassert>

int main() {
    assert(most_profit({ {0,1,10},{0,2,20},{0,3,30} }) == 30);
    assert(most_profit({ {0,1,1},{1,2,1},{2,3,1} }) == 3);
    assert(most_profit({ {0,2,1},{2,4,1},{4,6,1},{1,5,4} }) == 4);
    assert(most_profit({ {0,2,1},{2,4,1},{4,6,1},{1,3,2},{3,5,2} }) == 4);
    assert(most_profit({}) == 0);
    assert(most_profit({ {0,10,20} }) == 20);
    assert(most_profit({ {1,3,10},{2,4,20},{3,5,30},{6,8,40},{7,9,50} }) == 90);
}