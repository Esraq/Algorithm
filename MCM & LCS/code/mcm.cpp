#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // Required for LLONG_MAX

using namespace std;

// --- Function Prototypes ---
// Declare the helper function before it's called by matrixChainOrder_4x4
void printOptimalParenthesization(const vector<vector<int>>& S, int i, int j);

// --- Core MCM Function ---
void matrixChainOrder_4x4(const vector<int>& p) {
    // p is an array of dimensions. For 4 matrices (A1, A2, A3, A4),
    // it should have 5 elements: p[0]xp[1], p[1]xp[2], p[2]xp[3], p[3]xp[4]
    int n = 4; // Number of matrices

    // M[i][j] stores the minimum number of scalar multiplications
    // needed to compute the matrix product A_i * ... * A_j.
    vector<vector<long long>> M(n + 1, vector<long long>(n + 1, 0));

    // S[i][j] stores the optimal split index k for A_i...A_j.
    vector<vector<int>> S(n + 1, vector<int>(n + 1, 0));

    // Loop for chain length (l) from 2 to n
    for (int l = 2; l <= n; l++) {
        // Loop for the starting index (i)
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1; // Ending index (j)

            // Initialize cost to a maximum value
            M[i][j] = LLONG_MAX;

            // Loop for the split point (k)
            for (int k = i; k <= j - 1; k++) {
                // Calculation: M[i][k] + M[k+1][j] + (p[i-1] * p[k] * p[j])
                long long cost = M[i][k] + M[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];

                if (cost < M[i][j]) {
                    M[i][j] = cost; // Update minimum cost
                    S[i][j] = k;    // Store the optimal split point
                }
            }
        }
    }

    cout << "--- MCM Result ---" << endl;
    cout << "**Minimum number of scalar multiplications:** " << M[1][n] << endl;

    cout << "\nOptimal Parenthesization Structure:" << endl;
    // The previously problematic line is now correct due to the prototype
    printOptimalParenthesization(S, 1, n);
    cout << endl;
}

// --- Helper Function Definition ---
void printOptimalParenthesization(const vector<vector<int>>& S, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        // Recursively print the left subchain, split at S[i][j]
        printOptimalParenthesization(S, i, S[i][j]);
        cout << " * ";
        // Recursively print the right subchain, starting after S[i][j]
        printOptimalParenthesization(S, S[i][j] + 1, j);
        cout << ")";
    }
}

// --- Main function to demonstrate the usage ---
int main() {
    // Example: Four matrices A1, A2, A3, A4 with dimensions:
    // A1: 30x35, A2: 35x15, A3: 15x5, A4: 5x10
    // The dimension array p is: {r1, c1/r2, c2/r3, c3/r4, c4}
    vector<int> p = {30, 35, 15, 5, 10};

    cout << "Calculating Matrix Chain Order for 4 matrices with dimensions:\n";
    cout << "A1 (30x35), A2 (35x15), A3 (15x5), A4 (5x10)\n" << endl;

    // Check if the input size is correct for 4 matrices (must have 5 dimensions)
    if (p.size() != 5) {
        cerr << "Error: The dimension array must have 5 elements for 4 matrices." << endl;
        return 1;
    }

    matrixChainOrder_4x4(p);

    return 0;
}
