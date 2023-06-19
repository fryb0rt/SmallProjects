#include <vector>

/* Problem:
Given an array of n locked rooms, each room containing 0..n distinct keys,
determine whether you can visit each room.

You are given the key to room zero.
Assume that you can freely move between rooms.
*/

// Your solution:
bool locked_rooms(const std::vector<std::vector<int>>& rooms) {
    std::vector<bool> oldKeys(rooms.size());
    int keyCount = 1;
    std::vector<int> keys;
    keys.push_back(0);
    oldKeys[0] = true;
    while (!keys.empty()) {
        const int room = keys.back();
        keys.pop_back();
        for (const int key : rooms[room]) {
            if (oldKeys[key] == false) {
                ++keyCount;
                oldKeys[key] = true;
                keys.push_back(key);
            }
        }
    }
    return keyCount == int(rooms.size());
}

#include <cassert>

int main() {
    assert(locked_rooms({ {1},{2},{3},{} }));
    assert(not locked_rooms({ {1},{3,1},{2},{0} }));
    assert(locked_rooms({ {} }));
    assert(not locked_rooms({ {},{},{} }));
    assert(locked_rooms({ {0,1,2,3,4},{0,1,2,3,4},{0,1,2,3,4},{0,1,2,3,4},{0,1,2,3,4} }));
}