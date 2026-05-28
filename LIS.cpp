#include <bits/stdc++.h>
using namespace std;

// Longest Increasing Subsequence - two classic methods

// Method 1: DP O(n^2)
int LIS_DP(const vector<int>& a) {
    int n = (int)a.size();
    if (n == 0) return 0;
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j]) dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// Method 2: DP + binary search O(n log n)
int LIS_Optimal(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x); // first >= x
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS (DP O(n^2)): " << LIS_DP(a) << '\n';
    cout << "LIS (Optimal O(nlogn)): " << LIS_Optimal(a) << '\n';
    return 0;
}
