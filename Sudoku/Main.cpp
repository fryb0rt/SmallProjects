/* Problem:
Given a 9x9 Sudoku puzzle as a std::vector<std::vector<char>> with unfilled spaces represented by a space.
Solve the puzzle.

Sudoku rules:
- each nine rows, columns and 3x3 boxes have to contain all digits 1..9
*/

// Your solution:


#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

// We keep here which symbols are allowed
using Mask = std::vector<std::vector<bool>>;

// From two 0..8 indices to 0..80 index
int index(int x, int y)
{
    return x + 9 * y;
}
// We modify allowed symbols based on newly added symbol
void markMask(const int x, const int y, char symbol, Mask& mask)
{
    const int symbolIndex = symbol - '1';
    // Check row/column
    for (int i = 0; i < 9; ++i) {
        mask[index(i, y)][symbolIndex] = false;
        mask[index(x, i)][symbolIndex] = false;
    }
    // Check box
    for (int ix = 0; ix < 3; ++ix) {
        for (int iy = 0; iy < 3; ++iy) {
            const int xx = ix + (x / 3) * 3;
            const int yy = iy + (y / 3) * 3;
            mask[index(xx, yy)][symbolIndex] = false;
        }
    }
}

// Solver, requires prefilled mask
bool solve(std::vector<std::vector<char>>& puzzle, const Mask& mask, const int startIndex)
{
    // Find first non-solved entry
    for (int i = startIndex; i < mask.size(); ++i) {
        const int x = i % 9;
        const int y = i / 9;
        if (puzzle[y][x] == ' ') // Found ?
        {
            // Go through all possible symbols
            for (int symbolIndex = 0; symbolIndex < 9; ++symbolIndex)
            {
                if (mask[i][symbolIndex])
                {
                    // Set the symbol and modify the mask with allowed symbols
                    puzzle[y][x] = symbolIndex + '1';
                    Mask localMask = mask;
                    markMask(x, y, puzzle[y][x], localMask);
                    if (solve(puzzle, localMask, i + 1))
                    {
                        // Fully solved!
                        return true;
                    }
                    // Revert
                }
            }
            // Not found - something was wrong before this method was called
            puzzle[y][x] = ' ';
            return false;
        }
    }
    // Everything is already solved
    return true;
}

bool solve(std::vector<std::vector<char>>& puzzle) {
    Mask mask(81);
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            mask[index(x, y)].resize(9, puzzle[y][x] == ' ');
        }
    }
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            if (puzzle[y][x] != ' ') {
                markMask(x, y, puzzle[y][x], mask);
            }
        }
    }
    return solve(puzzle, mask, 0);
}


int main() {
    std::vector<std::vector<char>> puzzle1{
        {'1',' ',' ',' ','7','2',' ',' ',' '},
        {'7','8','5',' ','6','9','4','3',' '},
        {' ','3','2',' ','8','4','1','6','7'},
        {' ',' ',' ','8','1',' ','3','2',' '},
        {' ',' ','8','4',' ',' ',' ','7','9'},
        {'5',' ',' ',' ','3',' ',' ',' ',' '},
        {' ','9','3',' ','4',' ',' ',' ',' '},
        {' ',' ',' ','7',' ',' ','9',' ',' '},
        {'4','5',' ',' ',' ',' ',' ','1','3'}
    };

    std::vector<std::vector<char>> puzzle2{
        {'7','3','4',' ','9',' ',' ',' ',' '},
        {' ',' ','5',' ','3','1','4',' ',' '},
        {' ',' ',' ',' ',' ','7',' ','3','8'},
        {' ','4','2',' ','1','9',' ','8','7'},
        {'5',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','9','7',' ',' ',' ',' ',' ',' '},
        {'9',' ','6','1','7',' ','3','4',' '},
        {'8','5',' ',' ',' ',' ',' ','2',' '},
        {' ',' ',' ','6',' ',' ',' ',' ',' '}
    };
    std::vector<std::vector<char>> puzzle3{
        {'7','3','4','8','9','5','1','6','2'},
        {'6','8','5','2','3','1','4','7','9'},
        {'2','1','9','4','6','7','5','3','8'},
        {'3','4','2','5','1','9','6','8','7'},
        {'5','6','8','7','2','4','9','1','3'},
        {'1','9','7','3','8','6','2','5','4'},
        {'9','2','6','1','7','8','3','4','5'},
        {'8','5','1','9','4','3','7','2','6'},
        {'4','7','3','6','5','2','9',' ',' '}
    };


    assert(solve(puzzle1));
    assert(solve(puzzle2));
    assert(!solve(puzzle3));

    for (auto& line : puzzle1) {
        for (auto c : line)
            std::cout << " " << c << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    for (auto& line : puzzle2) {
        for (auto c : line)
            std::cout << " " << c << " ";
        std::cout << "\n";
    }

    std::vector<std::vector<char>> solution1{
        {'1','4','6','3','7','2','8','9','5'},
        {'7','8','5','1','6','9','4','3','2'},
        {'9','3','2','5','8','4','1','6','7'},
        {'6','7','9','8','1','5','3','2','4'},
        {'3','1','8','4','2','6','5','7','9'},
        {'5','2','4','9','3','7','6','8','1'},
        {'8','9','3','2','4','1','7','5','6'},
        {'2','6','1','7','5','3','9','4','8'},
        {'4','5','7','6','9','8','2','1','3'}
    };
    std::vector<std::vector<char>> solution2{
        {'7','3','4','8','9','5','1','6','2'},
        {'6','8','5','2','3','1','4','7','9'},
        {'2','1','9','4','6','7','5','3','8'},
        {'3','4','2','5','1','9','6','8','7'},
        {'5','6','8','7','2','4','9','1','3'},
        {'1','9','7','3','8','6','2','5','4'},
        {'9','2','6','1','7','8','3','4','5'},
        {'8','5','1','9','4','3','7','2','6'},
        {'4','7','3','6','5','2','8','9','1'}
    };

    assert(std::ranges::equal(puzzle1, solution1));
    assert(std::ranges::equal(puzzle2, solution2));
}