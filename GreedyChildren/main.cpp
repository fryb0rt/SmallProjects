#include <vector>

/* Problem:
Given a line of children with different levels of greediness
(represented by an array of integers), determine the minimum
number of candies you need to use to satisfy every child.

Each child must receive at least one candy, and each child
must receive more candy than their less greedy neighbours.
*/

// Your solution:
void process(const std::vector<int>& ratings, std::vector<int>& newRatings, const int start) {
    for (int i = start; i < int(ratings.size()); ++i) {
        int newRating = 1;
        if (i > 0 && ratings[i - 1] < ratings[i]) {
            newRating = newRatings[i - 1] + 1;
        }
        if (i < int(ratings.size() - 1) && ratings[i + 1] < ratings[i]) {
            process(ratings, newRatings, i + 1);
            newRating = std::max(newRatings[i + 1] + 1, newRating);
            newRatings[i] = newRating;
            return;
        }
        newRatings[i] = newRating;
    }
}
int candy(std::vector<int> ratings) {
    std::vector<int> newRatings = ratings;
    process(ratings, newRatings, 0);
    int cnt = 0;
    for (const int r : newRatings) {
        cnt += r;
    }
    return cnt;
}


#include <cassert>

int main() {
    assert(candy({ 1, 1, 1, 1, 1 }) == 5);
    assert(candy({ 1, 2, 3, 4, 5 }) == 15);
    assert(candy({ 5, 4, 3, 2, 1 }) == 15);
    assert(candy({ 1, 2, 1, 2, 1 }) == 7);
    assert(candy({ 1 }) == 1);
    assert(candy({ 1, 5, 2, 1 }) == 7);
    assert(candy({ 1, 2, 3, 4, 2, 1, 2, 3, 4, 5, 5, 5, 6, 7, 8 }) == 38);
    assert(candy({ 1,3,5,2,99,99,1 }) == 12);
}