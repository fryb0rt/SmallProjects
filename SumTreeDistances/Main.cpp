#include <unordered_map>
#include <vector>

/* Problem:
Given a tree with n nodes, represented as a graph using neighbourhood map,
calculate the sum of distances to all other nodes for each of nodes.

The node ids are in the range [0,n).
*/

// Your solution:

struct Node {
    int nodeDistances = 0;
    int nodeCount = 1;
};

// Computes sub-nodes count and distances considering only nodes that lower in the tree hierarchy
void processLowerNodes(const int nodeIndex, const std::unordered_multimap<int, int>& neighbours, std::vector<Node>& nodes)
{
    auto range = neighbours.equal_range(nodeIndex);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second > nodeIndex) {
            processLowerNodes(it->second, neighbours, nodes);
            nodes[nodeIndex].nodeCount += nodes[it->second].nodeCount;
            nodes[nodeIndex].nodeDistances += nodes[it->second].nodeDistances + nodes[it->second].nodeCount;
        }
    }
}

// Computes sub-nodes count and distances considering all nodes
void processRemainingNodes(const int nodeIndex, const Node& parent, const std::unordered_multimap<int, int>& neighbours, std::vector<Node>& nodes)
{
    // We reconsider the parent node to be child node and compute the final node distances from that.
    const int subNodeCount = parent.nodeCount - nodes[nodeIndex].nodeCount;
    const int subNodeDistances = parent.nodeDistances - (nodes[nodeIndex].nodeDistances + nodes[nodeIndex].nodeCount);
    nodes[nodeIndex].nodeCount += subNodeCount;
    nodes[nodeIndex].nodeDistances += subNodeCount + subNodeDistances;
    auto range = neighbours.equal_range(nodeIndex);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second > nodeIndex) {
            processRemainingNodes(it->second, nodes[nodeIndex], neighbours, nodes);
        }
    }
}

std::vector<int> distances_in_tree(const int n, const std::unordered_multimap<int, int>& neighbours) {
    std::vector<Node> nodes(n);
    processLowerNodes(0, neighbours, nodes);
    processRemainingNodes(0, Node{ .nodeDistances = nodes[0].nodeCount + nodes[0].nodeDistances, .nodeCount = nodes[0].nodeCount }, neighbours, nodes);
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = nodes[i].nodeDistances;
    }
    return result;
}

#include <cassert>
#include <iostream>

int main() {
    {
        std::unordered_multimap<int, int> neighbours;
        std::vector<int> expected_result = { 0 };
        assert(distances_in_tree(1, neighbours) == expected_result);
    }
    {
        std::unordered_multimap<int, int> neighbours = { {0,1}, {1,0} };
        std::vector<int> expected_result = { 1, 1 };
        assert(distances_in_tree(2, neighbours) == expected_result);
    }
    {
        std::unordered_multimap<int, int> neighbours = { {0,1}, {1,0}, {1,2}, {2,1} };
        std::vector<int> expected_result = { 3, 2, 3 };
        assert(distances_in_tree(3, neighbours) == expected_result);
    }
    {
        std::unordered_multimap<int, int> neighbours = { {0,1}, {1,0}, {0,2}, {2,0}, {0,3}, {3,0} };
        std::vector<int> expected_result = { 3, 5, 5, 5 };
        assert(distances_in_tree(4, neighbours) == expected_result);
    }
    {
        std::unordered_multimap<int, int> neighbours = { {0,1}, {1,0}, {1,2}, {2,1}, {2,3}, {3,2}, {3,4}, {4,3} };
        std::vector<int> expected_result = { 10, 7, 6, 7, 10 };
        assert(distances_in_tree(5, neighbours) == expected_result);
    }
    {
        std::unordered_multimap<int, int> neighbours = { {0,1}, {1,0}, {0,2}, {2,0}, {1,3}, {3,1}, {1,4}, {4,1} };
        std::vector<int> expected_result = { 6, 5, 9, 8, 8 };
        assert(distances_in_tree(5, neighbours) == expected_result);
    }
}