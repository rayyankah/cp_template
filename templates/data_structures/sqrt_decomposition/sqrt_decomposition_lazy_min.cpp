// update buckets with min value, 2 types query - sqrt decompostion
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class SquareRootDecomposition {
private:
    vector<int> arr;       // Original array
    vector<vector<int>> blocks; // Blocks array to store the elements of blocks (sorted)
    vector<int> lazy;      // Lazy propagation array
    int n;                 // Size of the array
    int block_size;        // Size of each block (approximately sqrt(n))

public:
    // Constructor to initialize the array and blocks
    SquareRootDecomposition(int n, vector<int>& input_arr) {
        this->n = n;
        this->arr = input_arr;
        block_size = (int)sqrt(n);  // Block size is sqrt(n)
        blocks = vector<vector<int>>((n + block_size - 1) / block_size);
        lazy = vector<int>((n + block_size - 1) / block_size, -1);  // Initialize lazy array to -1 (no updates yet)

        // Precompute blocks and sort each block
        for (int i = 0; i < n; i++) {
            blocks[i / block_size].push_back(arr[i]);
        }

        for (int i = 0; i < blocks.size(); i++) {
            sort(blocks[i].begin(), blocks[i].end());  // Sort each block
        }
    }

    // Helper function to apply lazy propagation to the block
    void applyLazy(int block_idx) {
        if (lazy[block_idx] == -1) return;

        // Apply the pending lazy update to the block
        int start = block_idx * block_size;
        int end = min(start + block_size, n);
        for (int i = start; i < end; i++) {
            arr[i] = min(arr[i], lazy[block_idx]);  // Update each element in the block
        }

        // Recompute the block after applying the update
        blocks[block_idx].clear();
        for (int i = start; i < end; i++) {
            blocks[block_idx].push_back(arr[i]);
        }

        // Sort the block after update
        sort(blocks[block_idx].begin(), blocks[block_idx].end());

        // Clear the lazy value for this block (no more pending updates)
        lazy[block_idx] = -1;
    }

    // Update the range [L, R] by applying min(A[i], X) for each i
    void update(int L, int R, int X) {
        int start_block = L / block_size;
        int end_block = R / block_size;

        // If the update range is within the same block
        if (start_block == end_block) {
            applyLazy(start_block);  // Apply any pending lazy updates
            for (int i = L; i <= R; i++) {
                arr[i] = min(arr[i], X);
                blocks[start_block][i % block_size] = arr[i];
            }
            sort(blocks[start_block].begin(), blocks[start_block].end());  // Re-sort the block
        }
        else {
            // Update the first partial block (L to the end of the block)
            applyLazy(start_block);
            for (int i = L; i < (start_block + 1) * block_size; i++) {
                arr[i] = min(arr[i], X);
                blocks[start_block][i % block_size] = arr[i];
            }
            sort(blocks[start_block].begin(), blocks[start_block].end());  // Re-sort the block

            // Update the full blocks in the middle
            for (int b = start_block + 1; b < end_block; b++) {
                lazy[b] = min(lazy[b], X);  // Mark the block for lazy update
            }

            // Update the last partial block (start of the block to R)
            applyLazy(end_block);
            for (int i = end_block * block_size; i <= R; i++) {
                arr[i] = min(arr[i], X);
                blocks[end_block][i % block_size] = arr[i];
            }
            sort(blocks[end_block].begin(), blocks[end_block].end());  // Re-sort the block
        }
    }

    // Query the sum of the range [L, R]
    int query(int L, int R) {
        int sum = 0;
        int start_block = L / block_size;
        int end_block = R / block_size;

        // If the query range is within the same block
        if (start_block == end_block) {
            applyLazy(start_block);  // Apply any pending lazy updates
            for (int i = L; i <= R; i++) {
                sum += arr[i];
            }
        }
        else {
            // Sum the first partial block
            applyLazy(start_block);
            for (int i = L; i < (start_block + 1) * block_size; i++) {
                sum += arr[i];
            }

            // Sum the full blocks in the middle
            for (int b = start_block + 1; b < end_block; b++) {
                applyLazy(b);
                sum += accumulate(blocks[b].begin(), blocks[b].end(), 0);
            }

            // Sum the last partial block
            applyLazy(end_block);
            for (int i = end_block * block_size; i <= R; i++) {
                sum += arr[i];
            }
        }
        return sum;
    }
};

int main() {
    int n = 10;
    vector<int> arr = {1, 3, 2, 7, 5, 6, 3, 8, 9, 4};

    SquareRootDecomposition sqd(n, arr);

    // Query sum from index 2 to 8
    cout << "Initial sum from 2 to 8: " << sqd.query(2, 8) << endl;

    // Update range [3, 7] with min(A[i], 4)
    sqd.update(3, 7, 4);

    // Query sum again after update
    cout << "Sum from 2 to 8 after update: " << sqd.query(2, 8) << endl;

    return 0;
}
