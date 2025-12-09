#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief Computes the length of the LCS and reconstructs the sequence.
 * * @param X The first input string.
 * @param Y The second input string.
 * @return The longest common subsequence string.
 */
string findLCS(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    // Create a 2D vector (DP table) to store the length of LCS.
    // L[i][j] stores the length of LCS of X[0..i-1] and Y[0..j-1].
    // We use (m+1) x (n+1) to handle the empty string case (index 0).
    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    // --- 1. Fill the DP Table (Calculating Length) ---
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                // LCS of an empty string with any other string is 0
                L[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                // If characters match, the LCS length increases by 1
                // plus the LCS of the preceding prefixes.
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                // If characters don't match, take the maximum LCS length
                // from either skipping X[i-1] or skipping Y[j-1].
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // The length of the LCS is stored in the bottom-right cell: L[m][n]
    int lcs_length = L[m][n];

    // --- 2. Reconstruct the LCS String (Backtracking) ---

    // Start from the bottom-right corner of the DP table
    int i = m;
    int j = n;
    string lcs_string(lcs_length, ' '); // Initialize string with correct size

    // Index for the LCS string
    int index = lcs_length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            // If characters match, this character is part of the LCS.
            // Move diagonally up-left and place the character in the result.
            lcs_string[index] = X[i - 1];
            index--;
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            // If the value came from the cell above (skipping Y[j-1]), move up.
            i--;
        } else {
            // If the value came from the cell to the left (skipping X[i-1]), move left.
            j--;
        }
    }

    return lcs_string;
}

// --- Main function to demonstrate the usage ---
int main() {
    string S1 = "AGGTAB";
    string S2 = "GXTXAYB";

    cout << "String 1: " << S1 << endl;
    cout << "String 2: " << S2 << endl;

    string lcs = findLCS(S1, S2);

    cout << "\nLongest Common Subsequence (LCS): " << lcs << endl;
    cout << "Length of LCS: " << lcs.length() << endl;

    return 0;
}

// Output for the example strings:
// LCS: GTAB
// Length: 4
